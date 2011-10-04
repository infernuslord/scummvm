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

#include "ring/sound/soundhandler.h"

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
	_field_3A = NULL;
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
	if (!_stream) {
		warning("[Cinematic::init] Error opening file (%s)", filename.c_str());
		return false;
	}

	// Create buffers
	_buffer = (byte *)malloc(CINEMATIC_BUFFER_SIZE);
	if (!_buffer)
		error("[Cinematic::init] Error creating main buffer!");

	_buffer2 = _buffer;
	_field_10 = false;

	_backBuffer = (byte *)malloc(CINEMATIC_BACKBUFFER_SIZE);
	if (!_backBuffer)
		error("[Cinematic::init] Error creating back buffer!");

	_tControlBuffer = (TControl *)malloc(CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(TControl));
	if (!_tControlBuffer)
		error("[Cinematic::init] Error creating control buffer!");

	_cacheBuffer = (byte *)malloc(CINEMATIC_CACHEBUFFER_SIZE);
	if (!_cacheBuffer)
		error("[Cinematic::init] Error creating cache buffer!");

	_compressedData = NULL;
	_field_3A = NULL;
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
	_field_3A = NULL;
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

	// Skip frame
	seek(header.size, SEEK_CUR);
}

bool Cinematic::tControl() {
	if (!_tControlBuffer)
		error("[Cinematic::tControl] Control buffer not initialized");

	if (!_stream)
		error("[Cinematic::tControl] Stream not initialized");

	if (!_compressedData)
		error("[Cinematic::tControl] Control data not initialized");

	// Reset tControl buffer
	memset(_tControlBuffer, 0, CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(TControl));

	// Read tControl header
	_tControlHeader.load(_stream);

	// Read data
	uint32 dataSize = 2 * _tControlHeader.field_C + 2;

	free(_compressedData);
	_compressedData = (byte *)malloc(dataSize + _tControlHeader.size);
	if (!_compressedData)
		error("[Cinematic::tControl] Cannot allocated memory for control data");

	_stream->read(_compressedData, dataSize + _tControlHeader.size);

	// Process
	_field_3A = _compressedData + dataSize;
	_field_46 = _tControlHeader.field_8;
	_compressedBufferEnd = _compressedData + 1 * (_tControlHeader.size    - _tControlHeader.field_4) + dataSize;
	_compressedBuffer    = _compressedData + 2 * (_tControlHeader.field_8 * _tControlHeader.field_A) + dataSize;

	// Decompress data
	uint32 decompressedSize = decompress(_compressedBuffer, _backBuffer, _compressedBufferEnd - _compressedBuffer);
	if (decompressedSize > CINEMATIC_BACKBUFFER_SIZE) {
		warning("[Cinematic::tControl] Back buffer overrun");
		return false;
	}

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

	// Read data
	error("[Cinematic::sControl] Not implemented!");


	if (!_tControlBuffer[7682].pBuffer) {
		// TODO update from backbuffer
		error("[Cinematic::sControl] Not implemented!");
	}


	uint32 decompressedSize = decompress(_compressedBuffer, buffer, _compressedBufferEnd - _compressedBuffer);
	if (decompressedSize >= 577536) {
		warning("[Cinematic::sControl] Buffer overrun");
		return false;
	}

	return true;
}

uint32 Cinematic::decompress(byte *data, byte *output, uint32 dataSize) {
	// TODO: Reduce code duplication

#define UPDATE_BUFFER_CONTROL(index) { \
	int    *pBuffer = _tControlBuffer[index].pBuffer; \
	uint32  count   = _tControlBuffer[index].count >> 2; \
	do { \
		*buffer = *pBuffer; \
		++pBuffer; \
		++buffer; \
		--count; \
	} while (count); \
}

#define UPDATE_BUFFER(index) { \
	int *control = &field_3A[index]; \
	uint32 count = 2; \
	do { \
		*buffer = *control; \
		++control; \
		++buffer; \
		--count; \
	} while (count); \
}

	// Get start and end of buffer
	byte *start = data;
	byte *end   = &data[dataSize];

	// Store buffers position
	int *buffer           = (int *)output;
	int *bufferStart      = buffer;
	int *cacheBuffer      = (int *)_cacheBuffer;
	int *cacheBufferStart = (int *)_cacheBuffer;
	int *field_3A         = (int *)_field_3A;

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
						UPDATE_BUFFER(*cacheBuffer);
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
						UPDATE_BUFFER_CONTROL(*cacheBuffer);
					} else {
						UPDATE_BUFFER(2 * *cacheBuffer);

						// Setup control buffer
						_tControlBuffer[*cacheBuffer].pBuffer = &field_3A[*cacheBuffer];
						_tControlBuffer[*cacheBuffer].count   = 8;
					}
				}

				// Advance cache (and loop if necessary)
				++cacheBuffer;

				if ((cacheBuffer - cacheBufferStart) >= 128)
					cacheBuffer = cacheBufferStart;

				check = false;

			} else {
				UPDATE_BUFFER_CONTROL(cacheBufferStart[(*start >> 4) + 16 * state - 128]);
			}

		} else {
			if (val < 128) {

				*cacheBuffer = 16 * val + (*start >> 4);

				if (*cacheBuffer > _field_46) {
					if (*cacheBuffer >= 1920) {
						UPDATE_BUFFER_CONTROL(*cacheBuffer);
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

							UPDATE_BUFFER(*index2);

							index2++;
						}
					}
				} else {
					if (_tControlBuffer[*cacheBuffer].count) {
						UPDATE_BUFFER_CONTROL(*cacheBuffer);
					} else {
						UPDATE_BUFFER(*cacheBuffer);

						// Setup control buffer
						_tControlBuffer[*cacheBuffer].pBuffer = &field_3A[*cacheBuffer];
						_tControlBuffer[*cacheBuffer].count = 8;
					}
				}

				// Advance cache (and loop if necessary)
				++cacheBuffer;

				if ((cacheBuffer - cacheBufferStart) >= 128)
					cacheBuffer = cacheBufferStart;

				check = true;

			} else {
				UPDATE_BUFFER_CONTROL(cacheBufferStart[val - 128]);
			}
		}
	}

	return (uint32)(buffer - bufferStart);
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

#pragma region Movie

Movie::Movie(ScreenManager *screen) : _screen(screen) {
	_imageCIN = NULL;
	_volume = 0.0f;
	_isSoundInitialized = false;
	_field_5B = false;
	_framerate = 0.0f;
	_hasDialog = false;
	_channel = 0;


	_cinematic = new Cinematic();
}

Movie::~Movie() {
	SAFE_DELETE(_imageCIN);
	SAFE_DELETE(_cinematic);

	// Zero-out passed pointers
	_screen = NULL;
}

bool Movie::init(Common::String path, Common::String filename, uint32 a3, uint32 channel) {
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
	sub_46A0E0(_imageCIN->getHeader()->field_8 + 1, _imageCIN->getHeader()->field_9, _imageCIN->getHeader()->field_A, -(int32)(CINEMATIC_TCONTROLBUFFER_SIZE * sizeof(Cinematic::TControl)));
	setVolume(getApp()->getPreferenceHandler()->getVolume());

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
	if (!_cinematic)
		error("[Movie::play] cinematic not initialized properly");

	if (!_imageCIN)
		error("[Movie::play] image not initialized properly");

	SoundHandler *soundHandler = getApp()->getSoundHandler();
	ScreenManager *screen = getApp()->getScreenManager();

	// Setup
	Image *image = new Image();
	bool setupSound = true;
	bool readFrame = false;
	uint32 chunkIndex = 0;
	uint32 waitChunk = 0;
	uint32 ticks = g_system->getMillis();

	// Setup header and state
	_cinematic->setField10(false);
	uint32 chunkCount = _imageCIN->getHeader()->chunkCount;

	// Parse cinematic
	if (chunkCount) {
		while (!_cinematic->eos() && !_cinematic->err()) {

			// Interrupt playing on escape
			if (checkEscape()) {
				if (soundHandler->getField0()) {
					soundHandler->updateItems2(chunkCount);
					soundHandler->updateItems3(chunkCount);
				}
				break;
			}

			// Read chunk type
			byte chunkType = _cinematic->readByte();
			if (_cinematic->eos() || _cinematic->err())
				error("[Movie::play] Cannot read chunk type");

			switch (chunkType) {
			default:
				error("[Movie::play] Invalid chunk type (%d)", chunkType);

			case 65:
				switch (_channel) {
				default:
					if (!skipSound())
						error("[Movie::play] Cannot skip sound (index: %d)", chunkIndex);
					break;

				case 2:
					if (!readSound())
						error("[Movie::play] Cannot read sound (index: %d)", chunkIndex);

					if (setupSound) {
						if (_isSoundInitialized)
							sub_46A4B0();

						setupSound = false;
					}
					break;
				}
				break;

			case 66:
				switch (_channel) {
				default:
					if (!skipSound())
						error("[Movie::play] Cannot skip sound (index: %d)", chunkIndex);
					break;

				case 3:
					if (!readSound())
						error("[Movie::play] Cannot read sound (index: %d)", chunkIndex);

					if (setupSound) {
						if (_isSoundInitialized)
							sub_46A4B0();

						setupSound = false;
					}
					break;
				}
				break;

			case 83:
				if (_field_5B) {
					uint32 tickInterval = (g_system->getMillis() - ticks);

					if (((chunkIndex + 1) * _framerate) < tickInterval) {
						if (readFrame) {
							_cinematic->skipFrame();

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
							while ((waitChunk * _framerate) > (tickInterval + 50))
								checkEvents();
						}
					}
				}

				if (!_imageCIN->readImage(image))
					error("[Movie::play] Error reading image (index: %d)", chunkIndex);

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

			case 84:
				if (!_cinematic->tControl())
					error("[Movie::play] Error reading T control (index: %d)", chunkIndex);
				break;

			case 90:
				switch (_channel) {
				default:
					if (!skipSound())
						error("[Movie::play] Cannot skip sound (index: %d)", chunkIndex);
					break;

				case 0:
				case 1:
					if (!readSound())
						error("[Movie::play] Cannot read sound (index: %d)", chunkIndex);

					if (setupSound) {
						if (_isSoundInitialized)
							sub_46A4B0();

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
		_cinematic->deinit();

	if (_hasDialog)
		getApp()->getDialogHandler()->removeDialog(500001);
}

#pragma region Sound

bool Movie::readSound() {
	if (!_cinematic)
		error("[Movie::readSound] Cinematic not initialized properly");

	// Read sound data offset
	uint32 offset = _cinematic->readUint32LE();
	if (_cinematic->err() || _cinematic->eos()) {
		warning("[Movie::readSound] Error reading from file");
		deinit();
		return false;
	}

	// Check if there is any sound data
	if (!offset)
		return true;

	if (offset > 10000000) {
		warning("[Movie::readSound] Invalid sound offset (was:%d, max:10000000)", offset);
		return false;
	}

	// Check remaining file size
	if (((uint32)_cinematic->pos() + offset) >= (uint32)_cinematic->size()) {
		warning("[Movie::readSound] Invalid sound offset (would read after end of file: %d)", offset);
		deinit();
		return false;
	}

	// Create a substream and initialize cinematic sound buffer
	if (!_isSoundInitialized)
		return true;

	setSoundBuffer(new Common::SeekableSubReadStream(_cinematic, (uint32)_cinematic->pos(), (uint32)_cinematic->pos() + offset), offset);

	return true;
}

bool Movie::skipSound() {
	if (!_cinematic)
		error("[Movie::skipSound] Cinematic not initialized properly");

	// Read sound data offset
	uint32 offset = _cinematic->readUint32LE();
	if (_cinematic->err() || _cinematic->eos()) {
		warning("[Movie::skipSound] Error reading from file");
		deinit();
		return false;
	}

	// Check if there is any sound data
	if (!offset)
		return true;

	// Skip sound data
	_cinematic->seek(offset, SEEK_CUR);
	if (_cinematic->err() || _cinematic->eos()) {
		warning("[Movie::skipSound] Error reading from file");
		deinit();
		return false;
	}

	return true;
}

void Movie::sub_46A0E0(uint32 a1, uint32 a2, uint32 a3, int32 a4) {
	error("[Cinematic::sub_46A0E0] Not implemented!");
}

void Movie::sub_46A4B0() {
	error("[Cinematic::sub_46A4B0] Not implemented!");
}

void Movie::setSoundBuffer(Common::SeekableReadStream *stream, uint32 offset) {
	error("[Cinematic::setSoundBuffer] Not implemented!");
}

void Movie::setVolume(int32 volume) {
	_volume = volume * 0.01f;

	if (_volume < 0.0f)
		_volume = 0.0f;

	if (_volume > 1.0f)
		_volume = 1.0f;

	error("[Movie::setVolume] Not implemented!");
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
