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

#ifndef CRYO_HNM_H
#define CRYO_HNM_H

#include "common/stream.h"

namespace Cryo {

class Hnm6 {
public:
	Hnm6(const Common::String &filename);
	~Hnm6();


	Common::String toString();

private:
	struct Header {
		char   signature[4];
		uint32 version;
		uint16 width;
		uint16 height;
		uint32 filesize;
		uint32 frames;
		uint32 tabOffset;
		uint16 bits;
		uint16 channels;
		uint32 framesize;
		char   creator[17];
		char   copyright[17];

		Header() {
			memset(signature, 0, sizeof(signature));
			version   = 0;
			width     = 0;
			height    = 0;
			filesize  = 0;
			frames    = 0;
			tabOffset = 0;
			bits      = 0;
			channels  = 0;
			framesize = 0;
			memset(creator, 0, sizeof(creator));
			memset(copyright, 0, sizeof(copyright));
		}

		void load(Common::SeekableReadStream *stream);
	};

	Header  _header;

	void load(const Common::String &filename);
};

} // End of namespace Cryo

#endif // CRYO_HNM_H
