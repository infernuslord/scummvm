/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "ring/graphics/movie.h"

#include "ring/base/application.h"
#include "ring/base/art.h"
#include "ring/base/dialog.h"
#include "ring/base/preferences.h"

#include "ring/graphics/image.h"
#include "ring/graphics/imageLoader.h"
#include "ring/graphics/screen.h"

#include "ring/sound/soundentry.h"
#include "ring/sound/soundhandler.h"
#include "ring/sound/soundmanager.h"

#include "ring/ring.h"
#include "ring/helpers.h"

#include "common/file.h"

namespace Ring {

#define CINEMATIC_BUFFER_SIZE          1024
#define CINEMATIC_BACKBUFFER_SIZE      1200000
#define CINEMATIC_TCONTROLBUFFER_SIZE  8192
#define CINEMATIC_CACHEBUFFER_SIZE     512

#pragma region Cinematic

Cinematic::Cinematic() {
	_stream = NULL;
	_buffer = NULL;
	_buffer2 = NULL;
	_field_10 = false;
	_backBuffer = NULL;
	_tControlBuffer = NULL;
	_cacheBuffer = NULL;
	_compressedData = NULL;
	_compressedDataEnd = NULL;
	_compressedBuffer = NULL;
	_compressedBufferEnd = NULL;
	_field_46 = 0;
	_isStreaming = false;
}

Cinematic::~Cinematic() {
	SAFE_DELETE(_stream);

	// Free buffers
	free(_buffer);
	_buffer2 = NULL;

	free(_backBuffer);
	free(_tControlBuffer);
	free(_cacheBuffer);
	free(_compressedData);
}

bool Cinematic::init(Common::String filename) {
	_stream = SearchMan.createReadStreamForMember(filename);
	if (!_stream || _stream->err()) {
		warning("[Cinematic::init] Error opening file (%s)", filename.c_str());
		return false;
	}

	// Create buffers
	_buffer = (byte *)calloc(CINEMATIC_BUFFER_SIZE, 1);
	if (!_buffer)
		error("[Cinematic::init] Error creating main buffer!");

	_buffer2 = _buffer;
	_field_10 = false;

	_backBuffer = (byte *)calloc(CINEMATIC_BACKBUFFER_SIZE, 1);
	if (!_backBuffer)
		error("[Cinematic::init] Error creating back buffer!");

	_tControlBuffer = (TControl *)calloc(CINEMATIC_TCONTROLBUFFER_SIZE, sizeof(TControl));
	if (!_tControlBuffer)
		error("[Cinematic::init] Error creating control buffer!");

	_cacheBuffer = (byte *)calloc(CINEMATIC_CACHEBUFFER_SIZE, 1);
	if (!_cacheBuffer)
		error("[Cinematic::init] Error creating cache buffer!");

	_compressedData = NULL;
	_compressedDataEnd = NULL;
	_compressedBuffer = NULL;
	_compressedBufferEnd = NULL;
	_field_46 = 0;

	return true;
}

void Cinematic::deinit() {
	SAFE_DELETE(_stream);

	// Free buffers
	free(_buffer);
	_buffer2 = NULL;

	free(_backBuffer);
	free(_tControlBuffer);
	free(_cacheBuffer);
	free(_compressedData);
	_compressedDataEnd = NULL;
	_compressedBuffer = NULL;
	_compressedBufferEnd = NULL;
	_field_46 = 0;
}

void Cinematic::skipFrame() {
	if (!_tControlBuffer)
		error("[Cinematic::skipFrame] Control buffer not initialized");

	// Reset tControl buffer
	memset(_tControlBuffer, 0, CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(TControl));

	// Read frame header
	FrameHeader header;
	header.read(_stream);

	debugC(kRingDebugMovie, "    Reading Frame header (size: %d, field_4: %d, field_8: %d, field_A: %d, width: %d, height: %d)",
	       header.size, header.field_4, header.field_8, header.field_A, header.width, header.height);
	debugC(kRingDebugMovie, "    Skipping frame data (size: %d)", header.size);

	// Skip frame
	seek(header.size, SEEK_CUR);
}

bool Cinematic::tControl() {
	if (!_tControlBuffer)
		error("[Cinematic::tControl] Control buffer not initialized");

	if (!_stream)
		error("[Cinematic::tControl] Stream not initialized");

	// Reset tControl buffer
	memset(_tControlBuffer, 0, CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(TControl));

	// Read tControl header
	_tControlHeader.load(_stream);

	debugC(kRingDebugMovie, "    Reading T control header (size: %d, field_4: %d, field_8: %d, field_A: %d, field_C: %d)",
	       _tControlHeader.size, _tControlHeader.field_4, _tControlHeader.field_8, _tControlHeader.field_A, _tControlHeader.field_C);

	// Read data
	uint32 dataSize = 2 * _tControlHeader.field_C + 2;

	free(_compressedData);
	_compressedData = (byte *)malloc(dataSize + _tControlHeader.size);
	if (!_compressedData)
		error("[Cinematic::tControl] Cannot allocate memory for control data");

	_stream->read(_compressedData, dataSize + _tControlHeader.size);

	// Process
	_compressedDataEnd   = _compressedData + dataSize;
	_field_46            = _tControlHeader.field_8;
	_compressedBuffer    = _compressedData + 2 * (_tControlHeader.field_8 * _tControlHeader.field_A) + dataSize;
	_compressedBufferEnd = _compressedData + 1 * (_tControlHeader.size    - _tControlHeader.field_4) + dataSize;

	// Decompress data
	uint32 decompressedSize = decompress(_compressedBuffer, _backBuffer, _compressedBufferEnd - _compressedBuffer);
	if (decompressedSize > CINEMATIC_BACKBUFFER_SIZE) {
		warning("[Cinematic::tControl] Back buffer overrun");
		return false;
	}

	debugC(kRingDebugMovie, "    Decompressed %d bytes of data", decompressedSize);

	return true;
}

bool Cinematic::sControl(byte* buffer) {
	if (!_tControlBuffer)
		error("[Cinematic::readFrameHeader] Control buffer not initialized");

	// Reset tControl buffer
	memset(_tControlBuffer, 0, CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(TControl));

	// Read frame header
	FrameHeader header;
	header.read(_stream);

	debugC(kRingDebugMovie, "    Reading Frame header (size: %d, field_4: %d, field_8: %d, field_A: %d, width: %d, height: %d)",
	       header.size, header.field_4, header.field_8, header.field_A, header.width, header.height);

	// FIXME This is broken (crashes scummvm), so disable for now
	seek(header.size, SEEK_CUR);
	return true;

	// Read stream
	uint32 dataSize = 2 * _tControlHeader.field_C + 2;

	free(_compressedData);
	_compressedData = (byte *)malloc(dataSize + header.size);
	if (!_compressedData)
		error("[Cinematic::sControl] Cannot allocate memory for control data");

	_stream->read(_compressedData, dataSize + header.size);

	// Process
	_compressedDataEnd   = _compressedData + dataSize;
	_field_46            = header.field_8;
	_compressedBuffer    = _compressedData + 2 * (header.field_8 * header.field_A) + dataSize;
	_compressedBufferEnd = _compressedData + 1 * (header.size    - header.field_4) + dataSize;

	// Update control buffer
	if (!_tControlBuffer[1920].count) {
		byte *compressedData = _compressedData;
		byte *backBuffer     = _backBuffer;

		if (compressedData < _compressedDataEnd) {
			int index = 1920;
			do {
				uint32 offset = *compressedData * 8;

				_tControlBuffer[index].pBuffer = (int *)backBuffer;
				_tControlBuffer[index].count   = offset;

				compressedData += 2;
				backBuffer += offset;
				++index;
			} while (compressedData < _compressedDataEnd);
		}
	}

	// Decompress data
	uint32 decompressedSize = decompress(_compressedBuffer, buffer, _compressedBufferEnd - _compressedBuffer);
	if (decompressedSize >= 577536) {
		warning("[Cinematic::sControl] Buffer overrun");
		return false;
	}

	debugC(kRingDebugMovie, "    Decompressed %d bytes of data", decompressedSize);

	return true;
}

uint32 Cinematic::decompress(byte *data, byte *output, uint32 dataSize) {
	// TODO: Reduce code duplication

#define UPDATE_BUFFER_CONTROL(index) updateBufferControl(index, &buffer);
#define UPDATE_BUFFER(index) updateBuffer(index, compressedDataEnd, &buffer);

	// Get start and end of buffer
	byte *start = data;
	byte *end   = &data[dataSize];

	// Store buffers position
	int *buffer            = (int *)output;
	int *bufferStart       = buffer;
	int *cacheBuffer       = (int *)_cacheBuffer;
	int *cacheBufferStart  = (int *)_cacheBuffer;
	int *compressedDataEnd = (int *)_compressedDataEnd;

	bool check = false;

	while (end > start) {

		// Get id value
		byte val = *start++;

		if (check) {

			// Get state
			byte state = val & 0xF;

			if (state < 8) {

				*cacheBuffer = *start++ + (state << 8);

				if (*cacheBuffer > _field_46) {
					if (*cacheBuffer >= 1920) {
						UPDATE_BUFFER_CONTROL(2 * *cacheBuffer);
					} else {

						uint32 total = *cacheBuffer - _field_46 - 1;
						byte *offset;
						for (offset = _compressedBufferEnd; ; offset += *offset + 1) {
							if (total-- < 1)
								break;
						}
						total = *offset >> 1;

						// Setup control buffer
						_tControlBuffer[2 * *cacheBuffer].pBuffer = buffer;
						_tControlBuffer[2 * *cacheBuffer].count   = 8 * total;

						int16 *index2 = (int16 *)(offset + 1);
						while (true) {
							if (total-- < 1)
								break;

							UPDATE_BUFFER(2 * *index2);

							index2++;
						}

					}
				} else {
					if (_tControlBuffer[*cacheBuffer].count) {
						UPDATE_BUFFER_CONTROL(2 * *cacheBuffer);
					} else {
						UPDATE_BUFFER(2 * *cacheBuffer);

						// Setup control buffer
						_tControlBuffer[2 * *cacheBuffer].pBuffer = &compressedDataEnd[*cacheBuffer];
						_tControlBuffer[2 * *cacheBuffer].count   = 8;
					}
				}

				// Advance cache (and loop if necessary)
				++cacheBuffer;

				if ((cacheBuffer - cacheBufferStart) >= 128)
					cacheBuffer = cacheBufferStart;

				check = false;

			} else {
				UPDATE_BUFFER_CONTROL(2 * cacheBufferStart[(*start >> 4) + 16 * state - 128]);
			}

		} else {
			if (val < 128) {

				*cacheBuffer = 16 * val + (*start >> 4);

				if (*cacheBuffer > _field_46) {
					if (*cacheBuffer >= 1920) {
						UPDATE_BUFFER_CONTROL(2 * *cacheBuffer);
					} else {

						uint32 total = *cacheBuffer - _field_46 - 1;
						byte *offset;
						for (offset = _compressedBufferEnd; ; offset += *offset + 1) {
							if (total-- < 1)
								break;
						}
						total = *offset >> 1;

						// Setup control buffer
						_tControlBuffer[*cacheBuffer].pBuffer = buffer;
						_tControlBuffer[*cacheBuffer].count   = 8 * total;

						int16 *index2 = (int16 *)(offset + 1);
						while (true) {
							if (total-- < 1)
								break;

							UPDATE_BUFFER(2 * *index2);

							index2++;
						}
					}
				} else {
					if (_tControlBuffer[*cacheBuffer].count) {
						UPDATE_BUFFER_CONTROL(2 * *cacheBuffer);
					} else {
						UPDATE_BUFFER(2 * *cacheBuffer);

						// Setup control buffer
						_tControlBuffer[2 * *cacheBuffer].pBuffer = &compressedDataEnd[*cacheBuffer];
						_tControlBuffer[2 * *cacheBuffer].count = 8;
					}
				}

				// Advance cache (and loop if necessary)
				++cacheBuffer;

				if ((cacheBuffer - cacheBufferStart) >= 128)
					cacheBuffer = cacheBufferStart;

				check = true;

			} else {
				UPDATE_BUFFER_CONTROL(2 * cacheBufferStart[val - 128]);
			}
		}
	}

	return (uint32)(buffer - bufferStart);
}

void Cinematic::updateBuffer(int index, int *compressedDataEnd, int **buffer) {
	int *control = &compressedDataEnd[index];
	uint32 count = 2;

	do {
		**buffer = *control;
		++control;
		++*buffer;
		--count;
	} while (count);
}

void Cinematic::updateBufferControl(int index, int **buffer) {
	int    *pBuffer = _tControlBuffer[index].pBuffer;
	uint32  count   = _tControlBuffer[index].count >> 2;

	if (count == 0)
		return;

	if (pBuffer == NULL)
		error("[Cinematic::updateBufferControl] Invalid control buffer");

	do {
		**buffer = *pBuffer;
		++pBuffer;
		++*buffer;
		--count;
	} while (count);
}

#pragma region ReadStream

bool Cinematic::eos() const {
	if (!_stream)
		error("[Cinematic::eos] Not initialized properly!");

	return _stream->eos();
}

uint32 Cinematic::read(void *dataPtr, uint32 dataSize) {
	if (!_stream)
		error("[Cinematic::read] Not initialized properly!");

	return _stream->read(dataPtr, dataSize);
}

#pragma endregion

#pragma region SeekableReadStream

int32 Cinematic::pos() const {
	if (!_stream)
		error("[Cinematic::pos] Not initialized properly!");

	return _stream->pos();
}

int32 Cinematic::size() const {
	if (!_stream)
		error("[Cinematic::size] Not initialized properly!");

	return _stream->size();
}

bool Cinematic::seek(int32 offset, int whence) {
	if (!_stream)
		error("[Cinematic::seek] Not initialized properly!");

	return _stream->seek(offset, whence);
}

#pragma endregion

#pragma endregion

#pragma region Cinematic2

Cinematic2::Cinematic2() {
	_stream = NULL;
	_seqBuffer = NULL;

	_field_5404C = false;

	_frameBuffer = NULL;
	_tControlBuffer = NULL;
}

Cinematic2::~Cinematic2() {
	SAFE_DELETE(_stream);

	free(_seqBuffer);
	_seqBuffer = NULL;

	free(_frameBuffer);
	_frameBuffer = 0;

	free(_tControlBuffer);
	_tControlBuffer = 0;
}

bool Cinematic2::init(Common::String filename, ArchiveType type, ZoneId zone, LoadFrom loadFrom) {
	// Initialize stream
	switch (type) {
	default:
		warning("[Cinematic2::init] Invalid archive type (%d)!", type);
		return false;

	case kArchiveFile:
		_stream = SearchMan.createReadStreamForMember(filename);
		break;

	case kArchiveArt:
		_stream = getApp()->getArtHandler()->get(filename, zone, loadFrom);
		break;
	}

	if (_stream == NULL)
		return false;

	_field_5404C = false;
	_seqBuffer = NULL;

	return true;
}

bool Cinematic2::allocBuffer(size_t bufferSize) {
	_seqBuffer = malloc(bufferSize);

	return _seqBuffer != NULL;
}

void Cinematic2::skipFrame() {
	// Read frame header
	if (!_frameHeader.read(_stream))
		error("[Cinematic2::skipFrame] Cannot read frame header");

	// Skip frame
	seek(_frameHeader.size, SEEK_CUR);
}

bool Cinematic2::tControl() {
	if (!_stream)
		error("[Cinematic2::tControl] Stream not initialized");

	// Read tControl header
	if (!_tControlHeader.read(_stream)) {
		error("[Cinematic2::tControl] Cannot read tControl header");
		return false;
	}

	// Reset buffer
	if (_tControlBuffer)
		free(_tControlBuffer);

	_tControlBuffer = (byte *)malloc(_tControlHeader.size);
	if (!_tControlBuffer) {
		warning("[Cinematic2::tControl] Cannot allocate tControl buffer");
		return false;
	}

	// Read buffer
	_stream->read(_tControlBuffer, _tControlHeader.size);
	if (_stream->eos() || _stream->err()) {
		warning("[Cinematic2::tControl] Cannot read tControl data");
		return false;
	}

	// Decompress
	decompressTControl(_tControlBuffer, 4 * _tControlHeader.bufferSize, _tControlHeader.decompressedSize);

	return true;
}

bool Cinematic2::sControl(byte* buffer, uint32 bitdepth) {
	if (!_stream)
		error("[Cinematic2::sControl] Stream not initialized");

	// Read frame header
	if (!_frameHeader.read(_stream)) {
		warning("[Cinematic2::sControl] Cannot read frame header");
		return false;
	}

	// Reset buffer
	if (_frameBuffer)
		free(_frameBuffer);

	_frameBuffer = (byte *)malloc(_frameHeader.size);
	if (!_frameBuffer) {
		warning("[Cinematic2::sControl] Cannot allocate frame buffer");
		return false;
	}

	// Read buffer
	_stream->read(_frameBuffer, _frameHeader.size);
	if (_stream->eos() || _stream->err()) {
		warning("[Cinematic2::sControl] Cannot read frame data");
		return false;
	}

	if (_frameHeader.offset < _frameHeader.size)
		decompressTControl(_frameBuffer + _frameHeader.offset, 4 * _frameHeader.bufferSize, _frameHeader.decompressedSize);

	if (bitdepth == 32)
		decompressSeq(buffer);

	return true;
}

void Cinematic2::decompressTControl(byte *buffer, uint32 bufferSize, uint16 decompressedSize) {

	memcpy(_buffer1, buffer, bufferSize);

	if (bufferSize == 16) {
		int *pBuffer = (int *)&_buffer1[16];

		// Iterate over buffer
		for (uint32 i = 0; i < decompressedSize; i++) {
			for (uint32 j = 0; j < 9; j++) {


				//warning("[Cinematic2::decompressTControl] Not implemented");

				++pBuffer;
			}

			pBuffer += 12;
		}

	} else {
		warning("[Cinematic2::decompressTControl] Not implemented");
	}

	if (_field_5404C) {
		for (uint32 i = 0; i < (uint32)decompressedSize * 4; i += 4) {
			_buffer1[i]     = _buffer1[i]     * 2;
			_buffer1[i + 1] = _buffer1[i + 1] * 2;
			_buffer1[i + 2] = _buffer1[i + 2] * 2;
			_buffer1[i + 3] = _buffer1[i + 3] * 2;
		}
	}


}

void Cinematic2::decompressSeq(byte *buffer) {
	warning("[Cinematic2::decompressSeq] Not implemented");
}

#pragma region ReadStream

bool Cinematic2::eos() const {
	if (!_stream)
		error("[Cinematic2::eos] Not initialized properly");

	return _stream->eos();
}

uint32 Cinematic2::read(void *dataPtr, uint32 dataSize) {
	if (!_stream)
		error("[Cinematic2::read] Not initialized properly");

	return _stream->read(dataPtr, dataSize);
}

#pragma endregion

#pragma region SeekableReadStream

int32 Cinematic2::pos() const {
	if (!_stream)
		error("[Cinematic2::pos] Not initialized properly");

	return _stream->pos();
}

int32 Cinematic2::size() const {
	if (!_stream)
		error("[Cinematic2::size] Not initialized properly");

	return _stream->size();
}

bool Cinematic2::seek(int32 offset, int whence) {
	if (!_stream)
		error("[Cinematic2::seek] Not initialized properly");

	return _stream->seek(offset, whence);
}

#pragma endregion

#pragma endregion

#pragma region CinematicSound

CinematicSound::CinematicSound() {
	_field_0     = 0;
	_field_2     = 0;
	_field_4     = 0;
	_field_8     = 0;
	_field_C     = 0;
	_field_E     = 0;
	_field_10    = 0;
	_audioStream = NULL;
	_bufferSize  = 0;
	_bufferSize2 = 0;
	_field_22    = 0;
	_field_26    = 0;
	_field_2A    = 0;
	_field_2E    = 0;
	_isPlaying   = false;
	_shouldPlay  = false;
	_volume      = 1.0f;
}

CinematicSound::~CinematicSound() {
	deinit();
}

void CinematicSound::init(uint32 a1, uint32 a2, uint32 a3, int32 bufferOffset) {
	deinit();

	_field_2 = a1;
	_field_E = a2;
	_field_C = a2 * a1 / 8;
	_shouldPlay = false;
	_field_10 = 1;
	_field_4 = a3;
	_field_0 = 1;
	_field_8 = a3 * _field_C;

	if (bufferOffset <= 0)
		_bufferSize2 = -bufferOffset;
	else
		_bufferSize2 = bufferOffset * _field_8;

	_bufferSize2 >>= 2;

	if (_bufferSize2 % _field_C)
		_bufferSize2 += _field_C - (_bufferSize2 % _field_C);

	_bufferSize = _bufferSize2 * 4;

	// Original setups the sound buffer
	_field_22 = 0;
}

void CinematicSound::deinit() {
	if (!_audioStream)
		return;

	if (_isPlaying) {
		play();
		_isPlaying = false;

		// Stop sound
		getSound()->getMixer()->stopHandle(_handle);
	}

	// TODO wait until the sound thread is done processing the buffer

	// Close the audio stream and cleanup buffers
	SAFE_DELETE(_audioStream);

	CLEAR_ARRAY(Common::SeekableReadStream, _buffers);
}

void CinematicSound::play() {
	if (!_audioStream || _isPlaying)
		return;

	int32 vol = (int32)(_volume * -10000.0f);
	SoundEntry::convertVolumeFrom(vol);

	_field_2A = 0;
	_field_26 = _bufferSize;

	// Lock buffer and copy data
	copyToBuffer();

	// Setup buffer filling thread
	createTimer();

	// Play sound
	_audioStream->rewind();
	getSound()->getMixer()->setChannelVolume(_handle, (byte)vol);

	// TODO Reset thread event

	_field_2E = 0;
	_isPlaying = true;
	_shouldPlay = false;

	getSound()->getMixer()->playStream(Audio::Mixer::kPlainSoundType, &_handle, makeLoopingAudioStream(_audioStream, 1));
}

void CinematicSound::setVolume(int32 volume) {
	_volume = volume * 0.01f;

	if (_volume < 0.0f)
		_volume = 0.0f;

	if (_volume > 1.0f)
		_volume = 1.0f;

	int32 vol = (int32)(_volume * -10000.0f);
	SoundEntry::convertVolumeFrom(vol);

	getSound()->getMixer()->setChannelVolume(_handle, (byte)vol);
}

void CinematicSound::addBuffer(Common::SeekableReadStream *stream) {
	_buffers.push_back(stream);
}

void CinematicSound::copyToBuffer() {
	Common::StackLock stackLock(_mutex);

	error("[CinematicSound::copyToBuffer] Not implemented!");
}

void CinematicSound::createTimer() {
	error("[CinematicSound::createTimer] Not implemented!");
}

void CinematicSound::handle() {
	error("[CinematicSound::soundTimer] Not implemented!");
}

void CinematicSound::handler(void *refCon) {
	((CinematicSound *)refCon)->handle();
}

#pragma endregion

#pragma region Movie

Movie::Movie(ScreenManager *screen) : _screen(screen) {
	_imageCIN = NULL;
	_isSoundInitialized = false;
	_field_5B = false;
	_framerate = 0.0f;
	_hasDialog = false;
	_channel = 0;

	_sound = new CinematicSound();
}

Movie::~Movie() {
	SAFE_DELETE(_imageCIN);
	SAFE_DELETE(_sound);

	// Zero-out passed pointers
	_screen = NULL;
}

bool Movie::init(Common::String path, Common::String filename, uint32, uint32 channel) {
	debugC(kRingDebugMovie, "Loading movie %s%s with channel %d", path.c_str(), filename.c_str(), channel);

	// Compute and check path
	Common::String filePath = path + filename;
	if (!Common::File::exists(filePath)) {
		warning("[Movie::init] Cannot find movie file: %s", filePath.c_str());
		return false;
	}

	// Initialize movie stream
	_imageCIN = new ImageLoaderCIN();
	if (!_imageCIN->init(filePath))
		error("[Movie::init] Cannot read cinematic frame size");

	// Set channel and sound state
	_channel = channel;
	_isSoundInitialized = true;

	// Setup sound
	_sound->init(_imageCIN->getHeader()->field_8 + 1, _imageCIN->getHeader()->field_9, _imageCIN->getHeader()->field_A, -(int32)(CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(Cinematic::TControl)));
	_sound->setVolume(getApp()->getPreferenceHandler()->getVolume());

	// Setup framerate
	_field_5B = true;
	_framerate = 1000.0f / (_imageCIN->getHeader()->field_12 * 0.01f);

	// Setup sound handler
	SoundHandler *soundHandler = getApp()->getSoundHandler();
	if (soundHandler->getField0()) {
		soundHandler->turnOffItems1();

		if (!soundHandler->updateItems(_imageCIN->getHeader()->chunkCount)) {
			soundHandler->turnOffSounds1(true);
			soundHandler->setField0(false);
		}
	}

	// Init dialog
	Common::String dialogPath = Common::String::format("DATA/%s/DIA/%s/%s", getApp()->getCurrentZoneFolder().c_str(), getApp()->getLanguageFolder().c_str(), filename.c_str());
	if (!Common::File::exists(dialogPath)) {
		_hasDialog = false;
		return true;
	}

	getApp()->getDialogHandler()->addDialog(new Dialog(500001, filename));
	_hasDialog = true;

	return true;
}

void Movie::deinit() {
	SAFE_DELETE(_imageCIN);

	_screen = NULL;
	_field_5B = true;
}

void Movie::play(const Common::Point &point) {
	debugC(kRingDebugMovie, "Playing movie at coordinates (%d, %d)", point.x, point.y);

	if (!_sound)
		error("[Movie::play] sound not initialized properly");

	if (!_imageCIN)
		error("[Movie::play] image not initialized properly");

	SoundHandler *soundHandler = getApp()->getSoundHandler();
	ScreenManager *screen = getApp()->getScreenManager();

	// Setup
	Cinematic *cinematic = _imageCIN->getCinematic();
	Image *image = new Image();
	bool setupSound = true;
	bool readFrame = false;
	uint32 chunkIndex = 0;
	uint32 waitChunk = 0;
	uint32 ticks = g_system->getMillis();

	// Setup header and state
	cinematic->setField10(false);
	uint32 chunkCount = _imageCIN->getHeader()->chunkCount;

	// Parse cinematic
	if (chunkCount) {
		while (!cinematic->eos() && !cinematic->err()) {

			// Interrupt playing on escape
			if (checkEscape()) {
				if (soundHandler->getField0()) {
					soundHandler->updateItems2(chunkCount);
					soundHandler->updateItems3(chunkCount);
				}
				break;
			}

			// Read chunk type
			ChunkType chunkType = (ChunkType)cinematic->readByte();
			if (cinematic->eos() || cinematic->err())
				error("[Movie::play] Cannot read chunk type");

			debugC(kRingDebugMovie, " Reading chunk %c", chunkType);

			switch (chunkType) {
			default:
				error("[Movie::play] Invalid chunk type %d (index: %d)", chunkType, chunkIndex);

			case kChunkA:
				switch (_channel) {
				default:
					if (!skipSound())
						error("[Movie::play] Chunk 65: Cannot skip sound (index: %d)", chunkIndex);
					break;

				case 2:
					if (!readSound())
						error("[Movie::play] Chunk 65: Cannot read sound (index: %d)", chunkIndex);

					if (setupSound) {
						if (_isSoundInitialized)
							_sound->play();

						setupSound = false;
					}
					break;
				}
				break;

			case kChunkB:
				switch (_channel) {
				default:
					if (!skipSound())
						error("[Movie::play] Chunk 66: Cannot skip sound (index: %d)", chunkIndex);
					break;

				case 3:
					if (!readSound())
						error("[Movie::play] Chunk 66: Cannot read sound (index: %d)", chunkIndex);

					if (setupSound) {
						if (_isSoundInitialized)
							_sound->play();

						setupSound = false;
					}
					break;
				}
				break;

			case kChunkS:
				if (_field_5B) {
					uint32 tickInterval = (g_system->getMillis() - ticks);

					if (((chunkIndex + 1) * _framerate) < tickInterval) {
						if (readFrame) {
							cinematic->skipFrame();

							// Process sound
							if (soundHandler->getField0()) {
								soundHandler->updateItems2(chunkCount);
								soundHandler->updateItems3(chunkCount);
							}

							++chunkIndex;
							waitChunk = chunkIndex;
							break;
						}

						readFrame = true;
						ticks = g_system->getMillis();

					} else {
						if (!readFrame) {
							readFrame = true;
							ticks = g_system->getMillis();
						} else {
							// Wait for tick interval
							while ((waitChunk * _framerate) > (tickInterval + 50)) {
								checkEvents();
								tickInterval = (g_system->getMillis() - ticks);
							}
						}
					}
				}

				if (!_imageCIN->readImage(image))
					error("[Movie::play] Chunk 83: Error reading image (index: %d)", chunkIndex);

				if (_hasDialog) {
					screen->draw(image, point, kDrawType1);
					getApp()->getDialogHandler()->play();

					screen->updateScreen();
				} else {
					screen->drawAndUpdate(image, point);
				}

				// Process sound
				if (soundHandler->getField0()) {
					soundHandler->updateItems2(chunkCount);
					soundHandler->updateItems3(chunkCount);
				}

				++chunkIndex;
				waitChunk = chunkIndex;
				break;

			case kChunkT:
				if (!cinematic->tControl())
					error("[Movie::play] Chunk 84: Error reading T control (index: %d)", chunkIndex);
				break;

			case kChunkZ:
				switch (_channel) {
				default:
					if (!skipSound())
						error("[Movie::play] Chunk Z: Cannot skip sound (index: %d)", chunkIndex);
					break;

				case 0:
				case 1:
					if (!readSound())
						error("[Movie::play] Chunk Z: Cannot read sound (index: %d)", chunkIndex);

					if (setupSound) {
						if (_isSoundInitialized)
							_sound->play();

						setupSound = false;
					}
					break;
				}
				break;
			}

			// Stop after processing all chunks
			if (chunkIndex >= chunkCount)
				break;
		}
	}

	// Cleanup
	delete image;

	if (_isSoundInitialized)
		_sound->deinit();

	if (_hasDialog)
		getApp()->getDialogHandler()->removeDialog(500001);
}

#pragma region Sound

bool Movie::readSound() {
	Cinematic *cinematic = _imageCIN->getCinematic();
	if (!cinematic)
		error("[Movie::readSound] Cinematic not initialized properly");

	// Read sound data offset
	uint32 offset = cinematic->readUint32LE();
	if (cinematic->err() || cinematic->eos()) {
		warning("[Movie::readSound] Error reading from file");
		deinit();
		return false;
	}

	debugC(kRingDebugMovie, "    Reading sound data (size: %d)", offset);

	// Check if there is any sound data
	if (!offset)
		return true;

	if (offset > 10000000) {
		warning("[Movie::readSound] Invalid sound offset (was: %d, max: 10000000)", offset);
		return false;
	}

	// Check remaining file size
	if (((uint32)cinematic->pos() + offset) >= (uint32)cinematic->size()) {
		warning("[Movie::readSound] Invalid sound offset (would read after end of file: %d)", offset);
		deinit();
		return false;
	}

	// Add buffer to queue
	if (!_isSoundInitialized)
		return true;

	_sound->addBuffer(new Common::SeekableSubReadStream(cinematic, (uint32)cinematic->pos(), (uint32)cinematic->pos() + offset));

	cinematic->seek(offset, SEEK_CUR);

	return true;
}

bool Movie::skipSound() {
	Cinematic *cinematic = _imageCIN->getCinematic();
	if (!cinematic)
		error("[Movie::skipSound] Cinematic not initialized properly");

	// Read sound data offset
	uint32 offset = cinematic->readUint32LE();
	if (cinematic->err() || cinematic->eos()) {
		warning("[Movie::skipSound] Error reading from file");
		deinit();
		return false;
	}

	debugC(kRingDebugMovie, "    Skipping sound data (size: %d)", offset);

	// Check if there is any sound data
	if (!offset)
		return true;

	// Skip sound data
	cinematic->seek(offset, SEEK_CUR);
	if (cinematic->err() || cinematic->eos()) {
		warning("[Movie::skipSound] Error reading from file");
		deinit();
		return false;
	}

	return true;
}

#pragma endregion

#pragma endregion

#pragma region Movie2

Movie2::Movie2(ScreenManager *screen) : _screen(screen) {
	_imageCI2 = NULL;
}

Movie2::~Movie2() {
	SAFE_DELETE(_imageCI2);
	SAFE_DELETE(_cinematic2);

	// Zero-out passed pointers
	_screen = NULL;
}

bool Movie2::init(const Common::String &folder, const Common::String &filename) {
	error("[Movie2::init] Not implemented!");
}

uint32  Movie2::playNextFrame(const Common::Point &point, DrawType drawType) {
	error("[Movie2::playNextFrame] Not implemented!");
}

uint32  Movie2::getNumberOfFrames() {
	error("[Movie2::getNumberOfFrames] Not implemented!");
}

void  Movie2::setSynchroOff() {
	error("[Movie2::setSynchroOff] Not implemented!");
}


#pragma endregion


} // End of namespace Ring
