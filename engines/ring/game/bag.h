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
 *
 * $URL$
 * $Id$
 *
 */

#ifndef RING_BAG_H
#define RING_BAG_H

#include "ring/shared.h"

namespace Ring {

class Hotspot;
class Image;
class Object;

class Bag {
public:
	Bag();
	~Bag();

	// Initialization
	void sub_4178C0();

	void sub_417D20(uint32 a1, uint32 a2);
	void sub_417D40(uint32 a1, uint32 a2, uint32 a3, uint32 a4);
	void sub_417D60(uint32 a1, uint32 a2);
	void sub_417D80(uint32 a1, uint32 a2, uint32 a3, uint32 a4);
	void sub_417DA0(uint32 a1, uint32 a2, uint32 a3, uint32 a4);
	void sub_417DD0(uint32 a1);
	void sub_417DE0(uint32 a1, uint32 a2);

	void sub_419280(uint32 a1);
	void sub_4192A0(uint32 a1, uint32 a2);
	void sub_4192C0(uint32 a1, uint32 a2);

	void loadBackground(Common::String filename1, Common::String filename2, Common::String filename3, Common::String filename4, Common::String filename5, Common::String filename6, Common::String filename7, Common::String filename8, ArchiveType filetype);

private:

	// Bag data
	Common::Array<Object *> _objects;
	Common::Array<Hotspot*> _field_4;
	Common::Array<uint32*> _field_8;
	uint32 _field_C;
	uint32 _field_10;
	uint32 _field_14;
	uint32 _field_18;
	uint32 _field_1C;
	uint32 _field_20;
	uint32 _field_24;
	uint32 _field_28;
	uint32 _field_2C;
	uint32 _field_30;
	uint32 _field_34;
	Image *_image1;
	Image *_image2;
	Image *_image3;
	Image *_image4;
	uint32 _field_48;
	uint32 _field_4C;
	uint32 _field_50;
	uint32 _field_54;
	uint32 _field_58;
	uint32 _field_5C;
	uint32 _field_60;
	uint32 _field_64;
	uint32 *_field_68;
	uint32 *_field_6C;
	uint32 *_field_70;
	uint32 _field_74;
	uint32 _field_78;
	uint32 _field_7C;
	uint32 _field_80;
	uint32 *_field_84;
	uint32 _field_88;
	uint32 _field_8C;
	uint32 _field_90;
	byte _field_94;
	uint32 _field_95;
	uint32 _field_99;
	uint32 _field_9D;
	uint32 _ticks;
	uint32 *_field_A5;
	uint32 _field_A9;
	uint32 _field_AD;
	uint32 _field_B1;
	uint32 _field_B5;
	uint32 _field_B9;
	uint32 _field_BD;
	uint32 _field_C1;
	uint32 _field_C5;
	ArchiveType _archiveType;
	uint32 *_field_CA;
	uint32 *_field_CE;
	byte _field_D2;

	void LoadImage(Common::String filename, Image *image, ArchiveType archiveType);
};

} // End of namespace Ring

#endif // RING_BAG_H
