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

#include "cryo/data/sound/zik.h"

#include "cryo/helpers.h"

#include "audio/decoders/wave.h"
#include "audio/decoders/raw.h"

#include "common/file.h"
#include "common/system.h"

namespace Cryo {

Zik::Zik(const Common::String &filename, bool dispose) : _stream (NULL), _dispose(dispose) {
	load(filename);
}

Zik::~Zik() {
	if (!_dispose)
		SAFE_DELETE(_stream);
}

void Zik::load(const Common::String &filename) {
	// Open a stream to the zik file
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(filename);
	if (!archive)
		error("[Zik::load] Error opening file (%s)", filename.c_str());

	// Try loading as wav file
	_stream = Audio::makeWAVStream(archive, DisposeAfterUse::YES);
	if (_stream)
		return;

	// This isn't a wav file, we need to reopen the archive
	archive = SearchMan.createReadStreamForMember(filename);
	if (!archive)
		error("[Zik::load] Error opening file (%s)", filename.c_str());

	// Load raw stream
	_stream = Audio::makeRawStream(archive, 22050, Audio::FLAG_STEREO|Audio::FLAG_16BITS|Audio::FLAG_LITTLE_ENDIAN, DisposeAfterUse::YES);

	// archive stream will be disposed when the stream is deleted
}

void Zik::play() {
	g_system->getMixer()->playStream(Audio::Mixer::kPlainSoundType, &_soundHandle, _stream, -1, Audio::Mixer::kMaxChannelVolume, 0, _dispose ? DisposeAfterUse::YES : DisposeAfterUse::NO);
}

} // End of namespace Cryo
