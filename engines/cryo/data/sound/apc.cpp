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

#include "cryo/data/sound/apc.h"

#include "cryo/helpers.h"

#include "audio/decoders/adpcm.h"

#include "common/file.h"
#include "common/system.h"

namespace Cryo {

void Apc::Header::load(Common::SeekableReadStream *stream) {
	stream->read(&id, sizeof(id));
	stream->read(&version, sizeof(version));
	outSize     = stream->readUint32LE();
	sampleRate  = stream->readUint32LE();
	sampleLeft  = stream->readUint32LE();
	sampleRight = stream->readUint32LE();
	stereo      = stream->readUint32LE();
}

Apc::Apc(const Common::String &filename, bool dispose) : _stream (NULL), _dispose(dispose) {
	load(filename);
}

Apc::~Apc() {
	if (!_dispose)
		SAFE_DELETE(_stream);
}

void Apc::load(const Common::String &filename) {
	// Open a stream to the apc file
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(filename);
	if (!archive)
		error("[Apc::load] Error opening file (%s)", filename.c_str());

	// Read APC header
	_header.load(archive);

	if (archive->err() || archive->eos())
		error("[Apc::load] Error loading header (%s)", filename.c_str());

	// Create ADPCM stream
	_stream = makeADPCMStream(archive, DisposeAfterUse::YES, 0, Audio::kADPCMMSIma, _header.sampleRate, _header.stereo ? 2 : 1, 4);

	// archive stream will be disposed when the stream is deleted
}

void Apc::play() {
	g_system->getMixer()->playStream(Audio::Mixer::kPlainSoundType, &_soundHandle, _stream, -1, Audio::Mixer::kMaxChannelVolume, 0, _dispose ? DisposeAfterUse::YES : DisposeAfterUse::NO);
}

} // End of namespace Cryo
