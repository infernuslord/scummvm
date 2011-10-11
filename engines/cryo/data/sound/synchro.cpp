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

#include "cryo/data/sound/synchro.h"

#include "common/file.h"

namespace Cryo {

void Synchro::Header::load(Common::SeekableReadStream *stream) {
	stream->read(&signature, sizeof(signature));
}

Synchro::Synchro(const Common::String &filename) {
	load(filename);
}

Synchro::~Synchro() {
}

Common::String Synchro::toString() {
	Common::String info;


	return info;
}

void Synchro::load(const Common::String &filename) {
	// Open a stream to the data file
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(filename);
	if (!archive)
		error("[Synchro::load] Error opening file (%s)", filename.c_str());

	// Read header
	_header.load(archive);

	if (archive->err() || archive->eos())
		error("[Synchro::load] Error loading header (%s)", filename.c_str());


	delete archive;
}

} // End of namespace Cryo
