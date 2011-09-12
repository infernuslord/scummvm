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

#include "ring/ring.h"
#include "ring/helpers.h"

namespace Ring {

VisualObjectBox::VisualObjectBox(Id id) : Visual(id) {
	_data           = NULL;
	_field_11       = 0;
	_field_15       = 0;
	_isLoaded       = false;
	_archiveType    = kArchiveInvalid;
	_name           = NULL;
	_imageKeywords  = NULL;
	_field_37       = 0;
	_size           = 0;
	memset(&_filename, 0, sizeof(_filename));
	_field_13E      = 0;
	_field_142      = 0;
	_field_146      = 0;
	_field_14A      = 0;
	_field_14E      = 0;
	_field_152      = 0;
	_field_15E     = true;
}

VisualObjectBox::~VisualObjectBox() {
	SAFE_DELETE(_data);

	CLEAR_ARRAY(Hotspot, _hotspots);
	CLEAR_ARRAY(Text,    _texts);
	CLEAR_ARRAY(uint32,  _field_23);
	CLEAR_ARRAY(uint32,  _field_27);
	CLEAR_ARRAY(uint32,  _field_2B);

	SAFE_DELETE(_name);
	SAFE_DELETE(_imageKeywords);
}

void VisualObjectBox::draw() {
	error("[VisualObjectBox::draw] Not implemented");
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
			break;

		case 0:
		case 60:
			getApp()->cursorSelect(kCursorIdle);
			return 1;

		case 10:
		case 50:
			getApp()->cursorSelect(kCursorMenuActive);
			return 1;
		}
	}

	return 0;
}

uint32 VisualObjectBox::handleLeftButtonDown(Common::Point point) {
	error("[VisualObjectBox::handleLeftButtonDown] Not implemented");
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

void VisualObjectBox::init(const Common::String &name, ArchiveType archiveType) {
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

void VisualObjectBox::setParameters(uint32 a2, uint32 a3, uint32 a4) {
	error("[VisualObjectBox::setParameters] Not implemented");
}

void VisualObjectBox::hide() {
	_field_13E = 0;
	_visible = false;
}

void VisualObjectBox::saveLoadWithSerializer(Common::Serializer &s) {
	error("[VisualObjectBox::saveLoadWithSerializer] Not implemented");
}

} // End of namespace Ring
