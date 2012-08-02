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

#ifndef CRYO_BIGFILE_H
#define CRYO_BIGFILE_H

#include "common/archive.h"
#include "common/hash-str.h"
#include "common/hashmap.h"

namespace Cryo {

class BigFile : public Common::Archive {
public:
	BigFile(const Common::String &path);

	bool hasFile(const Common::String &name) const;
	int listMembers(Common::ArchiveMemberList &list) const;
	const Common::ArchiveMemberPtr getMember(const Common::String &name) const;
	Common::SeekableReadStream *createReadStreamForMember(const Common::String &name) const;

	int count() { return _files.size(); }

private:
	struct Header {
		char   signature[16];
		uint32 count;
		uint32 dataSize;
		uint32 headerSize;
		uint32 dummy;

		Header() {
			memset(signature, 0, sizeof(signature));
			count      = 0;
			dataSize   = 0;
			headerSize = 0;
			dummy      = 0;
		}

		void load(Common::SeekableReadStream *stream);
	};

	// File entry
	struct Entry {
		uint32 nameSize;
		uint32 field_4;
		uint32 size;
		uint32 size2;
		uint32 size3;
		uint32 field_20;
		uint32 offset;          ///< Offset
		uint32 field_28;

		Common::String filename;

		Entry() {
			nameSize = 0;
			field_4  = 0;
			size     = 0;
			size2    = 0;
			size3    = 0;
			field_20 = 0;
			offset   = 0;
			field_28 = 0;
		}

		void load(Common::SeekableReadStream *stream);
	};

	typedef Common::HashMap<Common::String, Entry, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> FileMap;

	Header _header;
	FileMap _files;             ///< List of files
	Common::String _filename;   ///< Filename of the archive
};

} // End of namespace Cryo

#endif // CRYO_BIGFILE_H
