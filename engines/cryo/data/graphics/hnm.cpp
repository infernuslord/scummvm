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

#include "cryo/data/graphics/hnm.h"

#include "cryo/helpers.h"

#include "common/file.h"

namespace Cryo {

void Hnm6::Header::load(Common::SeekableReadStream *stream) {
	stream->read(&signature, sizeof(signature));
	version   = stream->readUint32LE();
	width     = stream->readUint16LE();
	height    = stream->readUint16LE();
	filesize  = stream->readUint32LE();
	frames    = stream->readUint32LE();
	tabOffset = stream->readUint32LE();
	bits      = stream->readUint16LE();
	channels  = stream->readUint16LE();
	framesize = stream->readUint32LE();
	stream->read(&creator, sizeof(creator) - 1);
	stream->read(&copyright, sizeof(copyright) - 1);
}

Hnm6::Hnm6(const Common::String &filename) {
	load(filename);
}

Hnm6::~Hnm6() {
}

Common::String Hnm6::toString() {
	Common::String info;

	info += Common::String::format("Version: %.2x - File size: %d\n", _header.version, _header.filesize);
	info += Common::String::format("Frame size: %dx%d - %d frame(s)\n", _header.width, _header.height, _header.frames);
	info += Common::String::format("Sound: %d bits - %d channel(s)\n", _header.bits, _header.channels);
	info += Common::String::format("Info: %s - %s", _header.creator, _header.copyright);

	return info;
}

void Hnm6::load(const Common::String &filename) {
	// Open a stream to the hnm file
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(filename);
	if (!archive)
		error("[Hnm6::load] Error opening file (%s)", filename.c_str());

	// Read sprite header
	_header.load(archive);

	if (archive->err() || archive->eos())
		error("[Hnm6::load] Error loading header (%s)", filename.c_str());



	delete archive;
}

} // End of namespace Cryo
