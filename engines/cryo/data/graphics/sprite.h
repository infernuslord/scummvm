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

#ifndef CRYO_SPRITE_H
#define CRYO_SPRITE_H

#include "cryo/shared.h"

#include "common/rect.h"
#include "common/str.h"
#include "common/stream.h"

#include "graphics/surface.h"

namespace Cryo {

class Sprite {
public:
	Sprite(const Common::String &filename);
	~Sprite();

	Common::Rect draw(Graphics::Surface *surface);

private:
	struct Header {
		uint32 field_0;
		uint32 field_1;
		uint32 field_2;
		uint16 width;
		uint16 height;
		byte   version;
		byte   field_11;
		uint32 field_12;
		uint32 field_16;
		uint32 field_1A;

		Header() {
			field_0  = 0;
			field_1  = 0;
			field_2  = 0;
			width    = 0;
			height   = 0;
			version  = 0;
			field_11 = 0;
			field_12 = 0;
			field_16 = 0;
			field_1A = 0;
		}

		void load(Common::SeekableReadStream *stream);
	};

	Header  _header;
	uint16  _bpp;
	byte   *_data;

	void load(const Common::String &filename);
};

} // End of namespace Cryo

#endif // CRYO_SPRITE_H
