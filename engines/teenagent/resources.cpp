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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "teenagent/resources.h"
#include "teenagent/teenagent.h"
#include "common/textconsole.h"
#include "common/zlib.h"

namespace TeenAgent {

Resources::Resources() {}

Resources *Resources::instance() {
	static Resources i;
	return &i;
}

void Resources::deinit() {
	off.close();
	on.close();
	ons.close();
	lan000.close();
	lan500.close();
	mmm.close();
	sam_mmm.close();
	sam_sam.close();
	voices.close();
}

/*
quick note on varia resources:
1: Mark's animations (with head)
2: Mark's idle animation
3: Inventory background
4: Inventory items
5: Metropolis palette
6: TEENAGENT logo (flames)
7: Small font
8: Bigger font
9: Metropolis software house
10: quit registered
11: quit shareware
*/

bool Resources::loadArchives(const ADGameDescription *gd) {
	Common::File *dat_file = new Common::File();
	if (!dat_file->open("teenagent.dat")) {
		delete dat_file;
		Common::String errorMessage = "You're missing the 'teenagent.dat' file. Get it from the ScummVM website";
		GUIErrorMessage(errorMessage);
		warning("%s", errorMessage.c_str());
		return false;
	}
	Common::SeekableReadStream *dat = Common::wrapCompressedReadStream(dat_file);
	cseg.read(dat, 0xb3b0);
	dseg.read(dat, 0xe790);
	eseg.read(dat, 0x8be2);

	delete dat;

	{
		FilePack varia;
		varia.open("varia.res");
		font7.load(varia, 7);
		font7.width_pack = 1;
		font7.height = 11;
		font8.load(varia, 8);
		font8.height = 31;
		varia.close();
	}

	off.open("off.res");
	on.open("on.res");
	ons.open("ons.res");
	lan000.open("lan_000.res");
	lan500.open("lan_500.res");
	mmm.open("mmm.res");
	sam_mmm.open("sam_mmm.res");
	sam_sam.open("sam_sam.res");
	voices.open("voices.res");

	return true;
}

void Resources::loadOff(Graphics::Surface &surface, byte *palette, int id) {
	uint32 size = off.getSize(id);
	if (size == 0) {
		error("invalid background %d", id);
		return;
	}

	const uint bufferSize = 64768;
	byte *buf = (byte *)malloc(bufferSize);
	if (!buf)
		error("[Resources::loadOff] Cannot allocate buffer");

	off.read(id, buf, bufferSize);

	byte *src = buf;
	byte *dst = (byte *)surface.pixels;
	memcpy(dst, src, 64000);
	memcpy(palette, buf + 64000, 768);

	free(buf);
}

Common::SeekableReadStream *Resources::loadLan(uint32 id) const {
	return id <= 500 ? loadLan000(id) : lan500.getStream(id - 500);
}

Common::SeekableReadStream *Resources::loadLan000(uint32 id) const {
	switch (id) {

	case 81:
		if (dseg.get_byte(0xDBAD))
			return lan500.getStream(160);
		break;

	case 137:
		if (dseg.get_byte(0xDBC5) == 1) {
			if (dseg.get_byte(0xDBC6) == 1)
				return lan500.getStream(203);
			else
				return lan500.getStream(202);
		}
		break;

	case 25:
		if (dseg.get_byte(0xDBDF) == 2) {
			return lan500.getStream(332);
		}
		break;

	case 37:
		if (dseg.get_byte(0xdbe2) == 1) {
			return lan500.getStream(351);
		} else if (dseg.get_byte(0xdbe2) == 2) {
			return lan500.getStream(364);
		}
		break;

	case 29:
		if (dseg.get_byte(0xDBE7) == 1) {
			return lan500.getStream(380);
		}

	case 30:
		if (dseg.get_byte(0xDBE7) == 1) {
			return lan500.getStream(381);
		}

	case 42:
		if (dseg.get_byte(0xDBEC) == 1) {
			return lan500.getStream(400);
		}
	}
	return lan000.getStream(id);
}

} // End of namespace TeenAgent
