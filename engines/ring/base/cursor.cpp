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

#include "ring/base/cursor.h"

#include "ring/base/application.h"

#include "ring/graphics/image.h"

#include "ring/helpers.h"
#include "ring/ring.h"

#include "graphics/cursorman.h"

namespace Ring {

#pragma region CursorBase

CursorBase::CursorBase() : BaseObject(kCursorInvalid) {
	_type = kCursorTypeInvalid;
	_frameCount = 0;
}

CursorBase::~CursorBase() {
}

void CursorBase::init(CursorId id, Common::String name, CursorType cursorType, byte frameCount) {
	_id	 = id;
	_name = name;
	_type  = cursorType;
	_frameCount = frameCount;
}

#pragma endregion

#pragma region CursorImage

CursorImage::CursorImage() {
	_archiveType = kArchiveInvalid;
	_image = NULL;
}

CursorImage::~CursorImage() {
	SAFE_DELETE(_image);
}

void CursorImage::init(CursorId id, Common::String name, CursorType cursorType, byte imageCount, ArchiveType archiveType) {
	CursorBase::init(id, name, cursorType, imageCount);

	_archiveType = archiveType;
	_image = new Image();

	if (imageCount == 1)
		alloc();
}

void CursorImage::alloc() {
	if (!_image)
		return;

	if (!_image->load(getName(), _archiveType, getZoneSY(), kLoadFromDisk, kDrawType3))
		error("[CursorImage::alloc] Cannot load image (%s)", getName().c_str());

	if (_image->getBPP() != 32) {
		dealloc();
		warning("[CursorImage::alloc] Only 32bpp TGA are supported as cursors images");
	}
}

void CursorImage::dealloc() {
	if (!_image)
		return;

	if (_image->isInitialized())
		_image->destroy();
}

void CursorImage::draw() {
	// TODO Check and do not replace cursor every frame if the data did not change
	if (!_image)
		return;

	if (!_image->isInitialized())
		alloc();

	// Easy case: 16bpp cursors
	if (_image->getBPP() == 16) {
		CursorMan.replaceCursor((byte *)_image->getSurface()->pixels, _image->getWidth(), _image->getHeight(), -_offset.x, -_offset.y, 0, 1, &_image->getSurface()->format);
		CursorMan.disableCursorPalette(true);
		CursorMan.showMouse(true);

		return;
	}

	// 24bpp & 32bpp cases
	if (_image->getBPP() != 24 && _image->getBPP() != 32)
		error("[CursorImage::draw] Cursor conversion is only supported for 24 & 32bpp images");

	//////////////////////////////////////////////////////////////////////////
	// HACK: Convert to 16bpp for display
	Graphics::PixelFormat formatCursor = _image->getSurface()->format;
	Graphics::PixelFormat formatScreen = g_system->getScreenFormat();

	// Prepare buffer to hold new cursor data
	uint32 size = _image->getWidth() * _image->getHeight();
	int16 *buf = (int16 *)malloc(size * 2);
	if (!buf)
		error("[CursorImage::draw] Cannot allocate cursor buffer (size: %d)", size);

	// Copy data (and mirror image)
	byte *src = (byte *)_image->getSurface()->getBasePtr(0, _image->getHeight() - 1);
	int16 *dst = buf;
	for (uint32 j = 0; j < _image->getHeight(); j++) {
		// Read pixel data
		uint8 a = 0, r = 0, g = 0, b = 0;

		for (uint32 i = 0; i < _image->getWidth(); i++) {
			switch (_image->getBPP()) {
			case 24:
				formatCursor.colorToARGB(READ_LE_UINT32(src + i * 3), a, r, g, b);
				break;

			case 32:
				formatCursor.colorToARGB(READ_LE_UINT32(src + i * 4), a, r, g, b);
				break;
			}

			dst[i] = formatScreen.ARGBToColor(a, r, g, b);
		}

		// Advance buffers
		dst += _image->getWidth();        //pitch for 16bpp buffer
		src -= _image->getSurface()->pitch;
	}

	// Replace cursor
	CursorMan.replaceCursor((byte *)buf, _image->getWidth(), _image->getHeight(), -_offset.x, -_offset.y, 0, 1, &formatScreen);
	CursorMan.disableCursorPalette(true);
	CursorMan.showMouse(true);

	// Cleanup
	delete buf;
}

#pragma endregion

#pragma region CursorAnimation

CursorAnimation::CursorAnimation() {
}

CursorAnimation::~CursorAnimation() {
}

void CursorAnimation::init(CursorId id, Common::String name, CursorType cursorType, byte imageCount, uint32 frameCount, float frameRate, byte a7, LoadFrom loadFrom, ArchiveType archiveType) {
	CursorBase::init(id, name, cursorType, imageCount);
	AnimationImage::init(name, kImageTypeTGA, Common::Point(0, 0), 0, kDrawType3, frameCount, frameRate, 1, a7, imageCount, 0, loadFrom, archiveType);
	setTicks(g_system->getMillis());
}

void CursorAnimation::alloc() {
	AnimationImage::alloc();
}

void CursorAnimation::dealloc() {
	AnimationImage::dealloc();
}

void CursorAnimation::draw() {
	// Compute current frame, but do not draw on screen
	playFrame(false);

	// Replace cursor
	Graphics::PixelFormat format = g_system->getScreenFormat();
	CursorMan.replaceCursor((byte *)getCurrentImage()->getSurface()->pixels, getCurrentImage()->getWidth(), getCurrentImage()->getHeight(), _offset.x, _offset.y, 0, 1, &format);
	CursorMan.disableCursorPalette(true);
	CursorMan.showMouse(true);
}

#pragma endregion

#pragma region CursorHandler

CursorHandler::CursorHandler() {
	_index = 0;
}

CursorHandler::~CursorHandler() {
	CLEAR_ARRAY(CursorBase, _cursors);
}

void CursorHandler::add(CursorId id, Common::String name, CursorType cursorType, byte imageCount, uint32 frameCount, float frameRate, byte a6, LoadFrom loadFrom, ArchiveType archiveType) {
	if (_cursors.has(id))
		error("[CursorHandler::add] ID already exists (%d)", id);

	CursorBase *cursor = NULL;
	switch (cursorType) {
	default:
		error("[CursorHandler::add] Invalid cursor type (%d)", cursorType);
		break;

	case kCursorTypeNormal:
	case kCursorType2:
		cursor = new CursorBase();
		cursor->init(id, name, cursorType, imageCount);
		break;

	case kCursorTypeImage: {
		cursor = new CursorImage();

		// Check archive type
		if (archiveType != kArchiveFile && archiveType != kArchiveArt)
			error("[CursorHandler::add] Invalid archive type (archiveType: %d)", archiveType);

		Common::String path;
		switch (loadFrom) {
		default:
			error("[CursorHandler::add] Cannot load image cursor (loadFrom: %d)", loadFrom);
			break;

		case kLoadFromCursor:
			path = Common::String::format("%sCURSOR/%s.tga", archiveType == kArchiveFile ? "" : "/", name.c_str());
			break;

		case kLoadFromListIcon:
			path = Common::String::format("%sLSTICON/%s.tga", archiveType == kArchiveFile ? "" : "/", name.c_str());
			break;
		}


		((CursorImage *)cursor)->init(id, path, cursorType, imageCount, archiveType);
		}
		break;

	case kCursorTypeAnimated:
		cursor = new CursorAnimation();
		((CursorAnimation *)cursor)->init(id, name, cursorType, imageCount, frameCount, frameRate, a6, loadFrom, archiveType);
		break;
	}

	_cursors.push_back(cursor);
}

void CursorHandler::removeByType(CursorType cursorType) {
	for (uint i = 0; i < _cursors.size();) {
		if (_cursors[i]->getType() == cursorType) {
			SAFE_DELETE(_cursors[i]);
			_cursors.remove_at(i);
		} else {
			++i;
		}
	}

	select(kCursorIdle);
}

void CursorHandler::draw() {
	if (_cursors.empty())
		error("[CursorHandler::draw] No cursor present");

	_cursors[_index]->draw();
}

void CursorHandler::hide() {

}

void CursorHandler::select(CursorId id) {
	if (!_cursors.has(id))
		error("[CursorHandler::select] ID doesn't exist (%d)", id);

	_index = _cursors.getIndex(id);
}

void CursorHandler::setOffset(CursorId id, const Common::Point &offset) {
	if (!_cursors.has(id))
		error("[CursorHandler::setOffset] ID doesn't exist (%d)", id);

	_cursors.get(id)->setOffset(offset);
}

CursorType CursorHandler::getType() {
	if (_cursors.empty())
		error("[CursorHandler::getType] No cursor present");

	return _cursors[_index]->getType();
}

#pragma endregion

} // End of namespace Ring
