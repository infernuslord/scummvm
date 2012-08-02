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

#include "cryo/data/resource/bigfile.h"

#include "cryo/debug.h"

#include "common/debug.h"
#include "common/file.h"
#include "common/substream.h"

namespace Cryo {

void BigFile::Header::load(Common::SeekableReadStream *stream) {
	if (!stream || stream->err() || stream->eos())
		error("[BigFile::Header::load] Invalid stream");

	stream->read(signature, sizeof(signature));
	count      = stream->readUint32LE();
	dataSize   = stream->readUint32LE();
	headerSize = stream->readUint32LE();
	dummy      = stream->readUint32LE();
}

void BigFile::Entry::load(Common::SeekableReadStream *stream) {
	if (!stream || stream->err() || stream->eos())
		error("[BigFile::Header::Entry] Invalid stream");

	nameSize = stream->readUint32LE();
	field_4  = stream->readUint32LE();
	size     = stream->readUint32LE();
	size2    = stream->readUint32LE();
	size3    = stream->readUint32LE();
	field_20 = stream->readUint32LE();
	offset   = stream->readUint32LE();
	field_28 = stream->readUint32LE();

	// Read filename
	char *name = (char *)malloc(nameSize + 1);
	memset(name, 0, nameSize + 1);
	stream->read(name, nameSize);

	filename = name;
	filename.toLowercase();
}

BigFile::BigFile(const Common::String &path) {
	_filename = path;

	// Open a stream to the archive
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(_filename);
	if (!archive) {
		debugC(2, kCryoDebugResource, "Error opening file: %s", _filename.c_str());
		return;
	}

	debugC(2, kCryoDebugResource, "Opened archive: %s", _filename.c_str());

	// Read header
	_header.load(archive);
	if (Common::String(_header.signature) != "BigFile 1.00") {
		debugC(2, kCryoDebugResource, "Invalid file format for file %s: %s", _filename.c_str(), _header.signature);
		return;
	}

	// Read the list of files
	debugC(3, kCryoDebugResource, "Number of files in archive: %u", _header.count);
	for (unsigned int i = 0; i < _header.count; ++i) {
		Entry entry;
		entry.load(archive);

		_files[entry.filename] = entry;

		debugC(9, kCryoDebugResource, "File entry: %s (offset:%d - Size: %d)", entry.filename.c_str(), entry.offset, entry.size);
	}

	delete archive;
}

bool BigFile::hasFile(const Common::String &name) const {
	return (_files.find(name) != _files.end());
}

int BigFile::listMembers(Common::ArchiveMemberList &list) const {
	int numMembers = 0;

	for (FileMap::const_iterator i = _files.begin(); i != _files.end(); ++i) {
		list.push_back(Common::ArchiveMemberList::value_type(new Common::GenericArchiveMember(i->_key, this)));
		numMembers++;
	}

	return numMembers;
}

const Common::ArchiveMemberPtr BigFile::getMember(const Common::String &name) const {
	if (!hasFile(name))
		return Common::ArchiveMemberPtr();

	return Common::ArchiveMemberPtr(new Common::GenericArchiveMember(name, this));
}

Common::SeekableReadStream *BigFile::createReadStreamForMember(const Common::String &name) const {
	FileMap::const_iterator fDesc = _files.find(name);
	if (fDesc == _files.end())
		return NULL;

	Common::File *archive = new Common::File();
	if (!archive->open(_filename)) {
		delete archive;
		return NULL;
	}

	return new Common::SeekableSubReadStream(archive, fDesc->_value.offset + _header.headerSize, fDesc->_value.offset + fDesc->_value.size + _header.headerSize, DisposeAfterUse::YES);
}

} // End of namespace Cryo
