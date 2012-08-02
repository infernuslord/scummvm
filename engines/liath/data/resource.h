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

#ifndef LIATH_RESOURCE_H
#define LIATH_RESOURCE_H

#include "liath/shared.h"

#include "common/archive.h"
#include "common/hashmap.h"
#include "common/hash-str.h"
#include "common/str.h"
#include "common/stream.h"

namespace Liath {

class ResourceManager : public Common::Archive {
public:
	ResourceManager();
	~ResourceManager();

	// Archive
	bool hasFile(const Common::String &name) const;
	int listMembers(Common::ArchiveMemberList &list) const;
	const Common::ArchiveMemberPtr getMember(const Common::String &name) const;
	Common::SeekableReadStream *createReadStreamForMember(const Common::String &name) const;

	// Path data
	void readPathFile();
	void readMultiData();
	CdNumber getCd(const Common::String &filename);

	// Message
	bool readMessage(uint32 *pIndex, Message *message);

private:
	enum MediaType {
		kMediaCd,
		kMediaHd
	};

	struct FilePath {
		MediaType      type;
		Common::String archiveName;
		Common::String folderName;
		CdNumber       cd;

		FilePath() {
			type = kMediaCd;
			cd = kCdNone;
		}

		Common::String toString() {
			return Common::String::format("FilePath:  type=%d, archive=%s, directory=%s, indicator=%d", type, archiveName.c_str(), folderName.c_str(), cd);
		}
	};

	typedef Common::HashMap<Common::String, FilePath, Common::CaseSensitiveString_Hash, Common::CaseSensitiveString_EqualTo> FileMap;
	typedef Common::HashMap<Common::String, Common::Archive *, Common::CaseSensitiveString_Hash, Common::CaseSensitiveString_EqualTo> ArchiveMap;

	ArchiveMap *_archiveCache;
	FileMap    _fileMap;
};

} // End of namespace Liath

#endif // LIATH_RESOURCE_H
