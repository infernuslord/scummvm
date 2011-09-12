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

#include "ring/graphics/visual/visual_box.h"

#include "ring/base/application.h"
#include "ring/base/text.h"

#include "ring/graphics/hotspot.h"
#include "ring/graphics/image.h"
#include "ring/graphics/screen.h"

#include "ring/ring.h"
#include "ring/helpers.h"

namespace Ring {

VisualObjectBox::DialogList::~DialogList() {
	CLEAR_ARRAY(Keyword, keywords);
}

VisualObjectBox::VisualObjectBox(Id id) : Visual(id) {
	_keyword        = NULL;
	_currentKeyword = NULL;
	_field_15       = 0;
	_isLoaded       = false;
	_archiveType    = kArchiveInvalid;
	_name           = NULL;
	_imageKeywords  = NULL;
	_field_37       = 0;
	_dialogId       = 0;
	_isSetup        = false;
	_keywordId1     = 0;
	_keywordId2     = 0;
	_keywordId3     = 0;
	_keywordId4     = 0;
	_keywordId      = 0;
	_showOptions    = true;
}

VisualObjectBox::~VisualObjectBox() {
	SAFE_DELETE(_keyword);

	CLEAR_ARRAY(Hotspot,    _hotspots);
	CLEAR_ARRAY(Text,       _options);
	CLEAR_ARRAY(Keyword,    _keywords);
	CLEAR_ARRAY(uint32,     _field_27);
	CLEAR_ARRAY(DialogList, _dialogs);

	SAFE_DELETE(_name);
	SAFE_DELETE(_imageKeywords);
}

void VisualObjectBox::reset() {
	CLEAR_ARRAY(Hotspot, _hotspots);
	CLEAR_ARRAY(Text,    _options);
	CLEAR_ARRAY(Keyword, _keywords);
	CLEAR_ARRAY(uint32,  _field_27);
}

void VisualObjectBox::draw() {
	if (!_visible || !_isSetup)
		return;

	if (_keywords.empty()) {
		getApp()->onVisualList(_id, 7, Common::Point(_keywordId, 1));
		_visible = false;
		reset();
		return;
	}

	// Draw name
	if (_name)
		getApp()->getScreenManager()->drawText(_name);

	int16 y = _point.y + 4;

	// Draw image
	if (_imageKeywords->isInitialized())
		getApp()->getScreenManager()->draw(_imageKeywords, Common::Point(_point.x, y), _imageKeywords->getDrawType());

	// Draw items
	for (Common::Array<Text *>::iterator it = _options.begin(); it != _options.end(); it++) {
		y += 13;

		if (_imageKeywords->isInitialized())
			getApp()->getScreenManager()->draw(_imageKeywords, Common::Point(_point.x, y), _imageKeywords->getDrawType());

		getApp()->getScreenManager()->drawText(*it);
	}
}

uint32 VisualObjectBox::handleLeftButtonUp(const Common::Point &point) {
	if (_visible)
		return handleUpdate(point);

	return 0;
}

uint32 VisualObjectBox::handleUpdate(const Common::Point &point) {
	if (!_visible || _hotspots.size() == 0)
		return 0;

	for (Common::Array<Hotspot *>::iterator it = _hotspots.begin(); it != _hotspots.end(); it++) {
		Hotspot *hotspot = *it;

		if (!hotspot->contains(point))
			continue;

		switch (hotspot->getTarget()) {
		default:
			return 0;

		case 0:
		case 60:
			getApp()->cursorSelect(kCursorIdle);
			break;

		case 10:
		case 50:
			getApp()->cursorSelect(kCursorMenuActive);
			break;
		}

		return 1;
	}

	return 0;
}

uint32 VisualObjectBox::handleLeftButtonDown(Common::Point point) {
	if (!_visible || !_isSetup || _hotspots.size() == 0)
		return 0;

	for (uint32 i = 0; i < _hotspots.size(); i++) {
		Hotspot *hotspot = _hotspots[i];

		if (!hotspot->contains(point))
			continue;

		switch (hotspot->getTarget()) {
		default:
			return 0;

		case 0:
		case 60:
			break;

		case 10: {
			Keyword *keyword = NULL;
			if (hotspot->getCursorId() < (CursorId)_keywords.size())
				keyword = _keywords[hotspot->getCursorId()];

			_currentKeyword = keyword;

			getApp()->onVisualList(_id, 6, Common::Point(keyword->id, 0));

			playDialog(i, keyword->id);

			}
			break;

		case 50:
			_isSetup = false;
			_visible = false;
			reset();
			break;
		}

		return 1;
	}

	return 0;
}

void VisualObjectBox::alloc() {
	if (_isLoaded)
		return;

	if (!hasImage()) {
		_isLoaded = true;
		return;
	}

	if (_imageKeywords)
		_imageKeywords->loadImage();

	_isLoaded = true;
}

void VisualObjectBox::dealloc() {
	_isLoaded = false;

	if (_imageKeywords)
		_imageKeywords->destroy();
}

void VisualObjectBox::saveLoadWithSerializer(Common::Serializer &s) {
	error("[VisualObjectBox::saveLoadWithSerializer] Not implemented");
}

void VisualObjectBox::init(const Common::String &/*name*/, ArchiveType archiveType) {
	_archiveType = archiveType;

	// Compute image path
	Common::String path;
	if (_archiveType == kArchiveFile)
		path = Common::String::format("DATA/%s/VISUAL/", getApp()->getCurrentZoneFolder().c_str());
	else
		path = "/VISUAL/";

	// Create image
	_imageKeywords = new ImageHandle("keywords.tga", Common::Point(0, 0), true, kDrawType3, 1000, 0, getApp()->getCurrentZone(), kLoadFromDisk, kImageTypeBackground, _archiveType);
	_imageKeywords->setDirectory(path);

	_name = new Text();
}

void VisualObjectBox::setParameters(Id keywordId, const Common::Point &point) {
	if (!_showOptions)
		ignoreKeyword();

	reset();

	_visible = true;

	if (!isKeywordLoaded(keywordId))
		loadKeyword(keywordId);

	_point = point;

	setupOptions();

	_showOptions = false;
	_keywordId = keywordId;
}

void VisualObjectBox::hide() {
	_isSetup = false;
	_visible = false;
}

void VisualObjectBox::setupOptions() {
	int16 y = _point.y + 10;

	_isSetup = true;

	// Setup options
	for (uint32 i = 0; i < _keywords.size(); i++) {
		Keyword *keyword = _keywords[i];

		// Initialize dialog option
		Text *text = new Text();
		text->init(keyword->name, Common::Point(_point.x + 10, y), kFontDefault, Color(255, 255, 255), Color(255, 255, 255));

		// Compute text dimensions
		text->set(keyword->name);
		y += text->getHeight();

		_options.push_back(text);

		// Add hotspot (with cursorId == keywordIndex)
		addHotspot(text, i);
	}
}

void VisualObjectBox::loadKeyword(Id keywordId) {
	error("[VisualObjectBox::loadKeyword] Not implemented");
}

void VisualObjectBox::addHotspot(Text *text, uint32 keywordIndex) {
	_hotspots.push_back(new Hotspot(text->getBoundingBox(), true, 0, (CursorId)keywordIndex, 10));
}

void VisualObjectBox::sub_4830A0(Id keywordId) {
	error("[VisualObjectBox::sub_4830A0] Not implemented");
}

void VisualObjectBox::playDialog(uint32 keywordIndex, Id keywordId) {
	// Remove keyword (it has been used)
	if (keywordIndex < _keywords.size())
		_keywords.remove_at(keywordIndex);

	// Play dialog
	if (_dialogs.empty() || !_dialogs.has(keywordId))
		getApp()->soundPlay(keywordId);

	sub_4830A0(keywordId);
	adjustOptions();
}

void VisualObjectBox::adjustOptions() {
	CLEAR_ARRAY(Hotspot, _hotspots);
	CLEAR_ARRAY(Text,    _options);

	setupOptions();
}

void VisualObjectBox::ignoreKeyword() {
	if (_dialogs.has(_keywordId))
		_dialogs.remove(_keywordId);

	DialogList *dialog = new DialogList(_keywordId);

	for (uint32 i = 0; i < _keywords.size(); i++)
		dialog->keywords.push_back(new Keyword(*_keywords[i]));

	_dialogs.push_back(dialog);
}

bool VisualObjectBox::isKeywordLoaded(Id keywordId) {
	if (_dialogs.empty() || !_dialogs.has(keywordId))
		return false;

	error("[VisualObjectBox::isKeywordLoaded] Not implemented");
}


} // End of namespace Ring
