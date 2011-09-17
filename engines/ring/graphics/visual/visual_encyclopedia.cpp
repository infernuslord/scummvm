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

#include "ring/graphics/visual/visual_encyclopedia.h"

#include "ring/base/application.h"
#include "ring/base/text.h"

#include "ring/graphics/hotspot.h"
#include "ring/graphics/image.h"
#include "ring/graphics/movie.h"

#include "ring/helpers.h"
#include "ring/ring.h"

namespace Ring {

#pragma region EncyclopediaEntry

EncyclopediaEntry::EncyclopediaEntry() {
	_target      = 0;
	_field_C     = 0;
	_field_10    = 0;
	_facetype    = kFaceTypeArial;
	_foregroundColor    = 0;
	_backgroundColor    = 0;
	_height      = 0;
	_smallWeight = false;
	_italic      = false;
	_field_2C    = 0;
	_padding     = 0;
}

#define READ_VALUE(name, type) { \
	const char *val = &buffer[offset]; \
	offset += strlen(val) + 1; \
	name = (type)atoi(val); \
}

#define READ_STRING(name) { \
	const char *val = &buffer[offset]; \
	offset += strlen(val) + 1; \
	name = Common::String(val); \
}

uint32 EncyclopediaEntry::load(const char *buffer, uint32 size) {
	uint32 offset = 0;

	READ_VALUE(_target, Id);
	READ_STRING(_label);
	READ_STRING(_filename);
	READ_VALUE(_field_C, uint32);
	READ_VALUE(_field_10, uint32);
	READ_VALUE(_facetype, Facetype);
	READ_VALUE(_foregroundColor, int32);
	READ_VALUE(_backgroundColor, int32);
	READ_VALUE(_height, uint32);
	READ_VALUE(_smallWeight, bool);
	READ_VALUE(_italic, bool);
	READ_VALUE(_field_2C, uint32);
	READ_VALUE(_padding, uint32);
	READ_VALUE(_point.x, int16);
	READ_VALUE(_point.y, int16);

	return offset;
}

Color EncyclopediaEntry::getForegroundColor() {
	if (_foregroundColor == -1)
		return Color(-1, -1, -1);

	if (_foregroundColor == 0) {
		if (_target > 0)
			return Color(255, -7, -48);
		else
			return Color(255, -29, 32);
	}

	return Color(_foregroundColor & 0xFF,
	             (_foregroundColor >> 8) & 0xFF,
	             (_foregroundColor >> 16) & 0xFF);
}

Color EncyclopediaEntry::getBackgroundColor() {
	if (_backgroundColor == -1 || _backgroundColor == 0)
		return Color(-1, -1, -1);

	return Color(_backgroundColor & 0xFF,
	             (_backgroundColor >> 8) & 0xFF,
	             (_backgroundColor >> 16) & 0xFF);
}

#pragma endregion

#pragma region VisualObjectEncyclopedia

VisualObjectEncyclopedia::VisualObjectEncyclopedia(Id id) : Visual(id) {
	_isLoaded           = false;
	_field_17           = 0;
	_imageArrowDown_dis = NULL;
	_imageArrowDown_hlt = NULL;
	_imageArrowDown_nor = NULL;
	_imageArrowUp_dis   = NULL;
	_imageArrowUp_hlt   = NULL;
	_imageArrowUp_nor   = NULL;
	_image7             = NULL;
	_imageSlide         = NULL;
	_imageSlider        = NULL;
	_field_3F           = 0;
	_field_43           = 0;
	_field_47           = 0;
	_field_4B           = 0;
	_field_4F           = 0;
	_field_50           = 455;
	_field_54           = 235;
	_field_58           = 613.0f;
	_top                = 49.0f;
	_field_60           = 0;
	_field_64           = 0;
	_textHeight           = 0;
	_field_6C           = 0;
	_field_70           = 0;
	_field_74           = 0;
	_field_78           = 0;
	_field_7C           = 0;
	_field_80           = 215;
	_field_84           = 0;
	_tickCount          = 0;
	_field_90           = 0;
	_field_94           = 0;
	_movie              = NULL;
	_frameCount           = 0;
	_field_A0           = 0;
	_field_A4           = 0;
	_text               = NULL;
	_hotspot            = NULL;
	_clippingBottom           = 20;
	_field_B8           = 450;
	_point              = Common::Point(10, 30);
	_clippingLeft           = 320;
	_field_C8           = 590;
	_field_CC           = true;
	memset(_fonts, 0, sizeof(_fonts));
	_field_541          = 0;
	_field_545          = 0;
	_field_549          = 0;
	_soundId          = 0;
	_field_551          = 0;
}

VisualObjectEncyclopedia::~VisualObjectEncyclopedia() {
	CLEAR_ARRAY(Hotspot,           _hotspots);
	CLEAR_ARRAY(Text,              _texts);
	CLEAR_ARRAY(EncyclopediaEntry, _entries);

	SAFE_DELETE(_movie);

	SAFE_DELETE(_imageArrowDown_dis);
	SAFE_DELETE(_imageArrowDown_hlt);
	SAFE_DELETE(_imageArrowDown_nor);
	SAFE_DELETE(_imageArrowUp_dis);
	SAFE_DELETE(_imageArrowUp_hlt);
	SAFE_DELETE(_imageArrowUp_nor);
	SAFE_DELETE(_image7);
	SAFE_DELETE(_imageSlide);
	SAFE_DELETE(_imageSlider);

	_hotspot = NULL;
	SAFE_DELETE(_text);
}

void VisualObjectEncyclopedia::draw() {
	error("[VisualObjectEncyclopedia::draw] Not implemented");
}

uint32 VisualObjectEncyclopedia::handleLeftButtonUp(const Common::Point &point) {
	error("[VisualObjectEncyclopedia::handleLeftButtonUp] Not implemented");
}

uint32 VisualObjectEncyclopedia::handleUpdate(const Common::Point &point) {
	error("[VisualObjectEncyclopedia::handleUpdate] Not implemented");
}

uint32 VisualObjectEncyclopedia::handleLeftButtonDown(Common::Point point) {
	error("[VisualObjectEncyclopedia::handleLeftButtonDown] Not implemented");
}

bool VisualObjectEncyclopedia::handleKey(Common::KeyCode key) {
	switch (key) {
	default:
		break;

	case Common::KEYCODE_PAGEUP:
		previous(50);
		setHotspot();
		break;

	case Common::KEYCODE_PAGEDOWN:
		next(50);
		setHotspot();
		break;
	}

	if (_field_4F)
		_field_4F = 0;

	return false;
}

void VisualObjectEncyclopedia::alloc() {
	if (_isLoaded)
		return;

	if (!load()) {
		_isLoaded = true;
		return;
	}

	if (_imageArrowDown_dis)
		_imageArrowDown_dis->loadImage();

	if (_imageArrowDown_hlt)
		_imageArrowDown_hlt->loadImage();

	if (_imageArrowDown_nor)
		_imageArrowDown_nor->loadImage();

	if (_imageArrowUp_dis)
		_imageArrowUp_dis->loadImage();

	if (_imageArrowUp_hlt)
		_imageArrowUp_hlt->loadImage();

	if (_imageArrowUp_nor)
		_imageArrowUp_nor->loadImage();

	if (_imageSlide)
		_imageSlide->loadImage();

	if (_imageSlider)
		_imageSlider->loadImage();

	_isLoaded = true;
}

void VisualObjectEncyclopedia::dealloc() {
	_isLoaded  = false;
	_field_A4 = 0;

	SAFE_DELETE(_movie);

	CLEAR_ARRAY(EncyclopediaEntry, _entries);

	_imageArrowDown_dis->destroy();
	_imageArrowDown_hlt->destroy();
	_imageArrowDown_nor->destroy();
	_imageArrowUp_dis->destroy();
	_imageArrowUp_hlt->destroy();
	_imageArrowUp_nor->destroy();
	_image7->destroy();
	_imageSlide->destroy();
	_imageSlider->destroy();
}

void VisualObjectEncyclopedia::init(const Common::String &name, ArchiveType archiveType) {
	_archiveType = archiveType;

	// Compute image folder
	Common::String path;
	if (_archiveType == kArchiveFile)
		path = Common::String::format("DATA/%s/VISUAL/", getApp()->getCurrentZoneFolder().c_str());
	else
		path = "/VISUAL/";

	// Prepare hotspots
	addHotspots();

	// Create images
	_imageArrowDown_dis = new ImageHandle("ENC_AR-2.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageArrowDown_dis->setDirectory(path);
	_imageArrowDown_hlt = new ImageHandle("ENC_AR-2.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageArrowDown_hlt->setDirectory(path);
	_imageArrowDown_nor = new ImageHandle("ENC_AR-1.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageArrowDown_nor->setDirectory(path);
	_imageArrowUp_dis = new ImageHandle("ENC_AR-1.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageArrowUp_dis->setDirectory(path);
	_imageArrowUp_hlt = new ImageHandle("ENC_AR-3.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageArrowUp_hlt->setDirectory(path);
	_imageArrowUp_nor = new ImageHandle("ENC_AR-4.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageArrowUp_nor->setDirectory(path);

	_imageSlide = new ImageHandle("ENC_SC-1.BMP", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageSlide->setDirectory(path);
	_imageSlider = new ImageHandle("ENC_SC-1.TGA", Common::Point(0, 0), true, kDrawType1, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageSlider->setDirectory(path);

	_text = new Text();

	_filename = name;
}

void VisualObjectEncyclopedia::setParameters(const Common::Point &point, uint32 clippingBottom, uint32 a5, uint32 clippingLeft, uint32 a7, uint32 a8) {
	_point = point;
	_field_B8 = a5;
	_field_CC = a8;
	_clippingBottom = clippingBottom;
	_field_C8 = a7;
	_field_80 = (a5 - clippingBottom) / 2;
	_clippingLeft = clippingLeft;
	_field_50 = clippingLeft + abs((int)(a7 - clippingLeft)) / 2;
	_field_54 = clippingBottom + abs((int)(a5 - clippingBottom)) / 2;
}

void VisualObjectEncyclopedia::showFile(const Common::String &filename) {
	_filename = filename;

	if (!_isLoaded)
		return;

	// Cleanup existing data
	CLEAR_ARRAY(Hotspot,           _hotspots);
	CLEAR_ARRAY(Text,              _texts);
	CLEAR_ARRAY(EncyclopediaEntry, _entries);

	SAFE_DELETE(_movie);

	addHotspots();
	load();
}

void VisualObjectEncyclopedia::saveLoadWithSerializer(Common::Serializer &s) {
	s.syncString(_filename);
}

bool VisualObjectEncyclopedia::load() {
	// Compute full path
	Common::String path = "DATA/ENC/" + _filename;

	if (!loadEntries(path)) {
		warning("[VisualObjectEncyclopedia::load] Cannot load encyclopedia entries");
		return false;
	}

	// Prepare values
	uint32 offset = 0;
	uint32 textHeight = 12;
	uint32 clippingLeft = _clippingLeft;
	uint32 clippingBottom = _clippingBottom;

	// Process entries
	for (uint32 i = 0; i < _entries.size(); i++) {
		EncyclopediaEntry *entry = _entries[i];

		// Padding
		Common::String str;
		for (uint32 i = 0; i < entry->getPadding(); i++)
			str += " ";

		// Label
		str += entry->getLabel();

		// Adjust coordinates
		Common::Point point(clippingLeft, clippingBottom);
		if (entry->getField2C() > offset) {
			clippingBottom += textHeight + (entry->getField2C() <= offset + 1) ? 0 : 12 * (entry->getField2C() - offset);
			textHeight = 0;
			offset = entry->getField2C();
			point.y = clippingBottom;
		}

		// Init contents
		Text *text = new Text();
		text->init(str, point, kFontDefault, Color(255, -1, -1), Color(-1, -1, -1));
		text->set(str);

		// Adjust colors
		text->setForegroundColor(entry->getForegroundColor());
		text->setBackgroundColor(entry->getBackgroundColor());

		// Set font
		FontId fontId = getFontId(entry->getFaceType(), entry->getHeight(), entry->getSmallWeight(), entry->getItalic(), entry->getTarget());
		text->setFontId(fontId);
		text->set(str);

		// Compute text dimensions
		if (i == 0) {
			_field_6C = point.y;
			_field_7C = point.y - _clippingBottom;
		}

		if (text->getHeight() > textHeight)
			textHeight = text->getHeight();

		entry->setPoint(point);

		// Adjust text width
		uint32 spaceWidth = 0;
		if (entry->getTarget()) {
			Common::Point coords(clippingLeft, point.y);

			Text *space = new Text();
			space->init(" ", coords, fontId, Color(255, -1, -1), Color(-1, -1, -1));
			spaceWidth = space->getWidth();
			delete space;

			coords.x += spaceWidth;
			text->setCoordinates(coords);
		}

		if (text->getWidth() + clippingLeft > _field_C8) {
			clippingLeft = _clippingLeft;

			Common::Point coords(clippingLeft, textHeight + point.y);
			text->setCoordinates(coords);

			textHeight = 12;
			clippingBottom = coords.y + ((entry->getField2C() <= offset + 1) ? 0 : 12 * (entry->getField2C() - offset));
			offset = entry->getField2C();
		}

		// Adjust clipping
		clippingLeft += text->getWidth() + spaceWidth;

		_texts.push_back(text);

		// Update hotspot
		if (entry->getTarget())
			addHotspot(entry->getTarget(), text, (CursorId)i);
	}

	_textHeight = textHeight;
	_field_74 = textHeight + clippingBottom;
	_field_78 = _field_B8 - _clippingBottom;

	return true;
}

bool VisualObjectEncyclopedia::loadEntries(const Common::String &filename) {
	// Open a stream to the OUT file
	Common::SeekableReadStream *archive = SearchMan.createReadStreamForMember(filename);
	if (!archive)
		error("[VisualObjectEncyclopedia::loadEntries] Error opening encyclopedia file (%s)", filename.c_str());

	// Clear the existing entries
	CLEAR_ARRAY(EncyclopediaEntry, _entries);

	// Read the archive contents into a buffer
	uint32 size = archive->size();
	if (size <= 1) {
		delete archive;
		return true;
	}

	byte *buffer = (byte *)malloc(size);
	if (!buffer)
		error("[VisualObjectEncyclopedia::loadEntries] Cannot allocate memory for encyclopedia buffer (%d)", size);

	archive->read(buffer, size);
	delete archive;

	// Load entries
	byte *pBuffer = buffer;
	do {
		EncyclopediaEntry *entry = new EncyclopediaEntry();

		uint32 offset = entry->load((const char *)pBuffer, size);
		pBuffer += offset;
		size    -= offset;

		_entries.push_back(entry);

	} while (size > 0);

	delete buffer;

	return true;
}

void VisualObjectEncyclopedia::previous(uint32 y) {
	error("[VisualObjectEncyclopedia::previous] Not implemented");
}

void VisualObjectEncyclopedia::next(uint32 y) {
	error("[VisualObjectEncyclopedia::next] Not implemented");
}

void VisualObjectEncyclopedia::addHotspots() {
	_hotspots.push_back(new Hotspot(Common::Rect(606, 20, 626, 45), true, 0, kCursorInvalid, 0));
	_hotspots.push_back(new Hotspot(Common::Rect(606, 432, 626, 457), true, 0, kCursorInvalid, 1));
	_hotspots.push_back(new Hotspot(Common::Rect(606, 49, 626, 57), true, 0, kCursorInvalid, 2));
}

void VisualObjectEncyclopedia::addHotspot(Id target, Text *text, CursorId cursorId) {
	Id soundId = 0;
	if (target = 4 || target == 7)
		soundId = addSound(cursorId);

	_hotspots.push_back(new Hotspot(text->getBoundingBox(), true, soundId, cursorId, target + 1));
}

void VisualObjectEncyclopedia::setHotspot() {
	if (_texts.empty())
		return;

	Text *text = _texts[0];

	float y = (float)(text->getCoordinates().y - _field_7C - _clippingBottom);
	if (y >= 0) {
		_top = 49.0f;
	} else {
		_top = (text->getHeight() + abs(y)) / (_field_74 - _field_B8) * 386.0f + 49.0f;
		if (_top > 421.0f)
			_top = 421.0f;

		if (_top < 49.0f)
			_top = 49.0f;
	}

	if (_hotspots.size() <= 2)
		return;

	_hotspot = _hotspots[2];

	_hotspot->update(Common::Rect(_hotspot->getRect().left, _top, _hotspot->getRect().right, _top + 10.0f));
}

Id VisualObjectEncyclopedia::addSound(CursorId cursorId) {
	++_soundId;

	getApp()->soundAdd(_soundId + 10000000, kSoundTypeAmbientMusic, _entries[cursorId]->getFilename(), kLoadFromCd);

	return _soundId;
}

void VisualObjectEncyclopedia::playMovie(uint32 entryIndex) {
	if (entryIndex >= _entries.size())
		error("[VisualObjectEncyclopedia::playMovie] Invalid entry index (was: %d, valid:[0-%d])", entryIndex, _entries.size() - 1);

	// Get movie folder
	Common::String folder;
	if (_archiveType == kArchiveFile)
		folder = Common::String::format("DATA/%s/PLA/", getApp()->getCurrentZoneFolder());
	else
		folder = "/PLA/";

	SAFE_DELETE(_movie);

	// Initialize movie
	_movie = new Movie2(getApp()->getScreenManager());

	if (!_movie->init(folder, _entries[entryIndex]->getFilename()))
		error("[VisualObjectEncyclopedia::playMovie] Cannot initialize movie (%s%s)", folder.c_str(), _entries[entryIndex]->getFilename().c_str());

	_frameCount = _movie->getNumberOfFrames();
	_movie->setSynchroOff();
	_field_A0 = 0;
	_field_A4 = 1;
	_field_64 = 0;
}

void VisualObjectEncyclopedia::stopMovie(uint32 soundIndex) {
	SAFE_DELETE(_movie);

	getApp()->soundStopType(kSoundTypeAmbientMusic, 1024);
	getApp()->soundPlay(soundIndex + 1000000);
}

FontId VisualObjectEncyclopedia::getFontId(Facetype faceType, int height, bool smallWeight, bool italic, Id target) {
	// Height
	uint32 height_id = 0;
	switch (height) {
	default:
		height_id = 5;
		break;

	case 6:
		height_id = 1;
		break;

	case 8:
		height_id = 2;
		break;

	case 10:
		height_id = 3;
		break;

	case 11:
		height_id = 4;
		break;

	case 14:
		height_id = 6;
		break;

	case 16:
		height_id = 7;
		break;

	case 18:
		height_id = 8;
		break;

	case 24:
		height_id = 9;
		break;

	case 32:
		height_id = 10;
		break;

	case 64:
		height_id = 11;
		break;

	case 72:
		height_id = 12;
		break;
	}

	if (height == 0)
		height = 12;

	// Facetype
	Common::String facename;
	switch(faceType) {
	default:
		facename = "Arial";
		break;

	case kFaceTypeCourier:
		facename = "Courier";
		break;

	case kFaceTypeImpact:
		facename = "Impact";
		break;
	}

	// Compute font id
	uint32 idPart = 2 * (italic + 2 * smallWeight);
	if (target)
		idPart++;

	uint32 id = 96 * faceType + height_id * (idPart + 1);
	FontId fontId = (FontId)(id + 100);

	if (_fonts[id] == true)
		return fontId;

	// FIXME: We need to get replacement fonts...
	getApp()->fontAdd(fontId, "", facename, height, smallWeight, target != 0, italic, false, getApp()->getCurrentLanguage());

	_fonts[id] = true;

	return fontId;
}

void VisualObjectEncyclopedia::drawText(Text *text) {
	error("[VisualObjectEncyclopedia::drawText] Not implemented");
}

#pragma endregion

} // End of namespace Ring
