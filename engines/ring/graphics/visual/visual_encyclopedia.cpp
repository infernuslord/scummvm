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

#pragma region VisualObjectEncyclopedia

EncyclopediaEntry::EncyclopediaEntry() {
	error("[EncyclopediaEntry::EncyclopediaEntry] Not implemented");
}

EncyclopediaEntry::~EncyclopediaEntry() {
	error("[EncyclopediaEntry::~EncyclopediaEntry] Not implemented");
}

void EncyclopediaEntry::load(byte *buffer) {
	error("[EncyclopediaEntry::load] Not implemented");
}

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
	_field_68           = 0;
	_field_6C           = 0;

	/* missing fields */

	_field_80           = 215;
	_field_84           = 0;
	_tickCount          = 0;
	_field_90           = 0;
	_field_94           = 0;
	_movie              = NULL;
	_field_9C           = 0;
	_field_A0           = 0;
	_field_A4           = 0;
	_text               = NULL;
	_hotspot            = NULL;
	_field_B4           = 20;
	_field_B8           = 450;
	_field_BC           = 10;
	_field_C0           = 30;
	_field_C4           = 320;
	_field_C8           = 590;
	_field_CC           = true;

	/* missing fields */

	_field_54D          = 0;
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
}

void VisualObjectEncyclopedia::setParameters(uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8) {
	_field_BC = a2;
	_field_B8 = a5;
	_field_CC = a8;
	_field_C0 = a3;
	_field_B4 = a4;
	_field_C8 = a7;
	_field_80 = (a5 - a4) / 2;
	_field_C4 = a6;
	_field_50 = a6 + abs((int)(a7 - a6)) / 2;
	_field_54 = a4 + abs((int)(a5 - a4)) / 2;
}

void VisualObjectEncyclopedia::showFile(const Common::String &filename) {
	error("[VisualObjectEncyclopedia::showFile] Not implemented");
}

void VisualObjectEncyclopedia::saveLoadWithSerializer(Common::Serializer &s) {
	s.syncString(_name);
}

void VisualObjectEncyclopedia::addHotspots() {
	_hotspots.push_back(new Hotspot(Common::Rect(606, 20, 626, 45), true, 0, kCursorInvalid, 0));
	_hotspots.push_back(new Hotspot(Common::Rect(606, 432, 626, 457), true, 0, kCursorInvalid, 1));
	_hotspots.push_back(new Hotspot(Common::Rect(606, 49, 626, 57), true, 0, kCursorInvalid, 2));
}

void VisualObjectEncyclopedia::setHotspot() {
	error("[VisualObjectEncyclopedia::setHotspot] Not implemented");
}

bool VisualObjectEncyclopedia::load() {
	error("[VisualObjectEncyclopedia::load] Not implemented");
}

bool VisualObjectEncyclopedia::loadEntries(const Common::String &filename) {
	error("[VisualObjectEncyclopedia::loadEntries] Not implemented");
}

void VisualObjectEncyclopedia::previous(uint32 y) {
	error("[VisualObjectEncyclopedia::previous] Not implemented");
}

void VisualObjectEncyclopedia::next(uint32 y) {
	error("[VisualObjectEncyclopedia::next] Not implemented");
}

void VisualObjectEncyclopedia::playMovie(uint32 entryIndex) {
	error("[VisualObjectEncyclopedia::next] Not implemented");
}

void VisualObjectEncyclopedia::stopMovie(uint32 soundIndex) {
	SAFE_DELETE(_movie);

	getApp()->soundStopType(kSoundTypeAmbientMusic, 1024);
	getApp()->soundPlay(soundIndex + 1000000);
}

FontId VisualObjectEncyclopedia::getFontId(int faceType, int height, bool smallWeight, bool italic, bool underline) {
	error("[VisualObjectEncyclopedia::getFontId] Not implemented");
}

void VisualObjectEncyclopedia::drawText(Text *text) {
	error("[VisualObjectEncyclopedia::drawText] Not implemented");
}

} // End of namespace Ring
