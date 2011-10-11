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

#ifndef CRYO_APC_H
#define CRYO_APC_H

#include "cryo/shared.h"

#include "audio/audiostream.h"
#include "audio/mixer.h"

#include "common/str.h"
#include "common/stream.h"

namespace Cryo {

class Apc {
public:
	Apc(const Common::String &filename, bool dispose = true);
	~Apc();

	void play();

private:
	struct Header {
		char    id[8];
		char    version[4];
		uint32  outSize;
		uint32  sampleRate;
		uint32  sampleLeft;
		uint32  sampleRight;
		uint32  stereo;

		Header() {
			memset(id, 0, sizeof(id));
			memset(version, 0, sizeof(version));
			outSize     = 0;
			sampleRate  = 0;
			sampleLeft  = 0;
			sampleRight = 0;
			stereo      = 0;
		}

		void load(Common::SeekableReadStream *stream);
	};

	Audio::SoundHandle _soundHandle;
	bool _dispose;

	Header  _header;
	Audio::RewindableAudioStream *_stream;

	void load(const Common::String &filename);
};

} // End of namespace Cryo

#endif // CRYO_APC_H
