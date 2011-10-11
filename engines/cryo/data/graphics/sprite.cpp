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

#include "cryo/data/graphics/sprite.h"

#include "cryo/helpers.h"

#include "common/file.h"

namespace Cryo {

void Sprite::Header::load(Common::SeekableReadStream *stream) {
	field_0  = stream->readUint32LE();
	field_1  = stream->readUint32LE();
	field_2  = stream->readUint32LE();
	width    = stream->readUint16LE();
	height   = stream->readUint16LE();
	version  = stream->readByte();
	field_11 = stream->readByte();
	field_12 = stream->readUint32LE();
	field_16 = stream->readUint32LE();
	field_1A = stream->readUint32LE();
}

Sprite::Sprite(const Common::String &filename) {
	_bpp  = 0;
	_data = NULL;

	load(filename);
}

Sprite::~Sprite() {
	SAFE_FREE(_data);
}

void Sprite::load(const Common::String &filename) {
	// Compute full path to sprite
	Common::String path = filename;
	if (Common::File::exists(path))
		goto label_open;

	path = "sprites/curseurs/" + filename;
	if (Common::File::exists(path))
		goto label_open;

	path = "sprites/fontes/" + filename;
	if (Common::File::exists(path))
		goto label_open;

	path = "sprites/interf/" + filename;
	if (Common::File::exists(path))
		goto label_open;

	path = "sprites/objets/" + filename;
	if (Common::File::exists(path))
		goto label_open;

	path = "misc/" + filename;
	if (!Common::File::exists(path))
		error("[Sprite::load] Cannot find sprite file (%s)", filename.c_str());

label_open:
	// Open a stream to the sprite file
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(path);
	if (!archive)
		error("[Sprite::load] Error opening sprite file (%s)", path.c_str());

	// Read sprite header
	_header.load(archive);

	if (archive->err() || archive->eos())
		error("[Sprite::load] Error loading sprite header (%s)", path.c_str());

	// Read sprite data
	_bpp = 2;
	uint32 size = _header.width * _header.height * _bpp;
	_data = (byte *)malloc(size);
	if (!_data)
		error("[Sprite::load] Cannot allocate buffer for sprite data (%s)", path.c_str());

	uint32 readSize = archive->read(_data, size);
	if (readSize != size)
		error("[Sprite::load] Error reading sprite data (expected: %d, read: %d)", size, readSize);

	if (archive->err() || archive->eos())
		error("[Sprite::load] Error loading sprite data (%s)", path.c_str());

	delete archive;
}

} // End of namespace Cryo
