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

#include "cryo/debug.h"
#include "cryo/helpers.h"

#include "common/file.h"
#include "common/rect.h"
#include "common/stream.h"

namespace Cryo {

void Hnm::Header::load(Common::SeekableReadStream *stream) {
	signature = stream->readUint32BE();
	field_4 = stream->readByte();
	field_5 = stream->readByte();
	field_6 = stream->readByte();
	bpp = stream->readByte();
}

Common::String Hnm::Header::toString() const {
	Common::String info;

	info += Common::String::format("Signature: %s\n", tag2str(signature));
	info += Common::String::format("Unknown: %.2x / %.2x / %.2x\n", field_4, field_5, field_6);
	info += Common::String::format("Bpp: %dbpp\n", bpp);

	return info;
}

void Hnm::Headerv4::load(Common::SeekableReadStream *stream) {
	Header::load(stream);

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

Common::String Hnm::Headerv4::toString() const {
	Common::String info;

	info += Header::toString();
	info += Common::String::format("File size: %d\n", filesize);
	info += Common::String::format("Frame size: %dx%d - %d frame(s)\n", width, height, frames);
	info += Common::String::format("Sound: %d bits - %d channel(s)\n", bits, channels);
	info += Common::String::format("Info: %s - %s\n", creator, copyright);

	return info;
}

void Hnm::Headerv6::load(Common::SeekableReadStream *stream) {
	Header::load(stream);

	width     = stream->readUint16LE();
	height    = stream->readUint16LE();
	filesize  = stream->readUint32LE();
	frames    = stream->readUint32LE();
	reserved  = stream->readUint32LE();
	maxBuffer = stream->readUint32LE();
	maxChunk  = stream->readUint32LE();
	stream->read(&creator, sizeof(creator) - 1);
	stream->read(&copyright, sizeof(copyright) - 1);
}

Common::String Hnm::Headerv6::toString() const {
	Common::String info;

	info += Header::toString();
	info += Common::String::format("File size: %d\n", filesize);
	info += Common::String::format("Frame size: %dx%d - %d frame(s)\n", width, height, frames);
	info += Common::String::format("Max buffer/chunk size: 0x%.2x - 0x%.2x\n", maxBuffer, maxChunk);
	info += Common::String::format("Info: %s - %s\n", creator, copyright);

	return info;
}

//////////////////////////////////////////////////////////////////////////
/// HNM video player
Hnm::Hnm() {
	_fileStream = NULL;
	_surface = NULL;
}

Hnm::~Hnm() {
	close();
}

bool Hnm::loadStream(Common::SeekableReadStream *stream) {
	close();

	_fileStream = stream;

	// Check file version and load header
	loadHeader(_fileStream);

	_surface = new Graphics::Surface();
	_surface->create(_header->getWidth(), _header->getHeight(), _header->getPixelFormat());
	_surface->fillRect(Common::Rect(0, 0, 640, 480), 0);

	return true;
}

void Hnm::loadHeader(Common::SeekableReadStream *stream) {
	// Save stream position
	uint32 position = stream->pos();

	// Check header signature and version
	Header header;
	header.load(stream);
	stream->seek(position, SEEK_SET);

	switch (header.signature) {
	default:
		error("[Hnm::loadHeader] Unknown signature: %s", tag2str(header.signature));

	case ID_HNM4:
		_header = new Headerv4();
		break;

	case ID_HNM6:
		_header = new Headerv6();
		break;
	}

	_header->load(stream);
}

const Graphics::Surface *Hnm::decodeNextFrame() {
	switch (_header->signature) {
	default:
		error("[Hnm::loadHeader] Unknown signature: %s", tag2str(_header->signature));

	case ID_HNM4:
		decodeChunkv4();
		break;

	case ID_HNM6:
		decodeChunkv6();
		break;
	}

	return _surface;
}

void Hnm::decodeChunkv4() {
	error("[Hnm::decodeChunkv4] Not implemented");
}

void Hnm::decodeChunkv6() {
	// Read chunk header
	uint32 size = _fileStream->readUint32LE();
	uint32 size2 = _fileStream->readUint32LE();
	uint16 id = _fileStream->readUint16BE();
	uint16 reserved = _fileStream->readUint16LE();

	debugC(6, kCryoDebugGraphics, "Decoding chunk: %s (size: %u, reserved: %u)", twoCC2str(id).c_str(), size, reserved);

	switch (id) {
	default:
		error("[Hnm::decodeChunkv6] Unknown chunk id (%s)", twoCC2str(id).c_str());

	case kChunkAA:
		break;

	case kChunkBB:
		break;

	case kChunkIX:
		break;
	}
}

void Hnm::close() {
	if (!_fileStream)
		return;

	SAFE_DELETE(_fileStream);

	if (_surface != NULL) {
		_surface->free();
		delete _surface;
		_surface = NULL;
	}

	reset();
}

uint32 Hnm::getTimeToNextFrame() const {
	if (endOfVideo() || _curFrame < 0)
		return 0;

	error("[Hnm::getTimeToNextFrame] Not implemented");
}

Common::String Hnm::toString() {
	if (_header == NULL)
		error("[Hnm::toString] Video not loaded");

	return _header->toString();
}

Common::String Hnm::twoCC2str(uint16 tag) {
	char str[3];
	str[0] = (char)(tag >> 8);
	str[1] = (char)tag;
	str[2] = '\0';

	// Replace non-printable chars by dot
	for (int i = 0; i < 2; ++i) {
		if (!isprint((unsigned char)str[i]))
			str[i] = '.';
	}

	return Common::String(str);
}

} // End of namespace Cryo
