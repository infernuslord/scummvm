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
 *
 * $URL$
 * $Id$
 *
 */

#include "ring/base/puzzle.h"

#include "ring/base/accessibility.h"
#include "ring/base/application.h"
#include "ring/base/bag.h"
#include "ring/base/movability.h"
#include "ring/base/object.h"
#include "ring/base/sound.h"
#include "ring/base/text.h"

#include "ring/graphics/animation.h"
#include "ring/graphics/image.h"
#include "ring/graphics/visual.h"

#include "ring/ring.h"
#include "ring/helpers.h"

namespace Ring {

Puzzle::Puzzle(Application *application, PuzzleId id) : BaseObject(id), _application(application) {
	_background = NULL;
	_field_24 = 1;
	_field_28 = 0;
	_field_29 = 0;
}

Puzzle::~Puzzle() {
	SAFE_DELETE(_background);

	CLEAR_ARRAY(Movability, _movabilities);
	CLEAR_ARRAY(Accessibility, _accessibilities);
	CLEAR_ARRAY(ImageHandle, _presentationImages);
	CLEAR_ARRAY(ObjectPresentation, _presentationAnimations);
	CLEAR_ARRAY(Text, _texts);
	CLEAR_ARRAY(SoundItem, _soundItems);
	CLEAR_ARRAY(Visual, _visuals);

	// Zero-out passed pointers
	_application = NULL;
}

void Puzzle::alloc() {
	if (_background && !_background->isInitialized()) {
		Common::String path;
		switch (_background->getArchiveType()) {
		default:
			error("[Puzzle::alloc] Invalid archive type!");
			break;

		case kArchiveFile:
			if (_background->getLoadFrom() == kLoadFromCd || _background->getLoadFrom() == kLoadFromDisk)
				path = Common::String::format("DATA/%s/IMAGE/%s", getApp()->getZoneString(_background->getZone()).c_str(), _background->getNameId().c_str());
			else if (_background->getLoadFrom() == kLoadFrom5)
				path = Common::String::format("%s%s", _background->getDirectory().c_str(), _background->getNameId().c_str());
			else
				error("[Puzzle::alloc] Invalid load From!");
			break;

		case kArchiveArt:
			if (_background->getLoadFrom() == kLoadFromCd || _background->getLoadFrom() == kLoadFromDisk)
				path = Common::String::format("/IMAGE/%s", _background->getNameId().c_str());
			else if (_background->getLoadFrom() == kLoadFrom5)
				path = Common::String::format("%s%s", _background->getDirectory().c_str(), _background->getNameId().c_str());
			else
				error("[Puzzle::alloc] Invalid load From!");
			break;
		}

		if (!_background->load(path, _background->getArchiveType(), _background->getZone(), _background->getLoadFrom()))
			error("[Puzzle::alloc] Cannot load background image (%s)!", path.c_str());
	}

	for (Common::Array<ImageHandle *>::iterator it = _presentationImages.begin(); it != _presentationImages.end(); it++) {
		ImageHandle *image = (*it);

		if (!image->getObjectPresentation()
		 || !image->getObjectPresentation()->isShown()
		 || image->isInitialized()
		 || !image->isActive()
		 || image->getField6C() != 1)
			continue;

		Common::String path;
		switch (image->getArchiveType()) {
		default:
			error("[Puzzle::alloc] Invalid archive type!");
			break;

		case kArchiveFile:
			if (image->getLoadFrom() == kLoadFromCd || image->getLoadFrom() == kLoadFromDisk)
				path = Common::String::format("DATA/%s/IMAGE/%s", getApp()->getZoneString(image->getZone()).c_str(), image->getNameId().c_str());
			else if (image->getLoadFrom() == kLoadFrom5)
				path = Common::String::format("%s%s", image->getDirectory().c_str(), image->getNameId().c_str());
			else
				error("[Puzzle::alloc] Invalid load From!");
			break;

		case kArchiveArt:
			if (image->getLoadFrom() == kLoadFromCd || image->getLoadFrom() == kLoadFromDisk)
				path = Common::String::format("/IMAGE/%s", image->getNameId().c_str());
			else if (image->getLoadFrom() == kLoadFrom5)
				path = Common::String::format("%s%s", image->getDirectory().c_str(), image->getNameId().c_str());
			else
				error("[Puzzle::alloc] Invalid load From!");
			break;
		}

		if (!image->load(path, image->getArchiveType(), image->getZone(), image->getLoadFrom()))
			error("[Puzzle::alloc] Cannot load image (%s)!", path.c_str());

	}

	for (Common::Array<Visual *>::iterator it = _visuals.begin(); it != _visuals.end(); it++)
		(*it)->alloc();
}

void Puzzle::dealloc() {
	if (_background) {
		if (_background->isInitialized())
			_background->destroy();
	}

	for (Common::Array<ImageHandle *>::iterator it = _presentationImages.begin(); it != _presentationImages.end(); it++) {
		ImageHandle *image = (*it);

		if (!image->isInitialized())
			continue;

		if (image->getField6C()) {
			image->destroy();
		} else if (image->getAnimation()) {
			image->getAnimation()->dealloc();
		} else {
			error("[Puzzle::dealloc] Invalid animation in ImageHandle (%s)", image->getNameId().c_str());
		}
	}

	for (Common::Array<Visual *>::iterator it = _visuals.begin(); it != _visuals.end(); it++)
		(*it)->dealloc();
}

void Puzzle::update(ScreenManager *screen) {
	warning("[Puzzle::update] Not implemented");
}

void Puzzle::setBackgroundImage(Common::String filename, const Common::Point &point, bool isActive, LoadFrom loadFrom) {
	SAFE_DELETE(_background);

	Zone zone = _application->getCurrentZone();
	ArchiveType archiveType = _application->getReadFrom(zone);

	_background = new ImageHandle(filename, point, isActive, zone, loadFrom, kImageTypeBackground, archiveType);
}

void Puzzle::addPresentationText(Text *text) {
	if (!text)
		error("[Puzzle::addPresentationText] Text is not initialized properly");

	_texts.push_back(text);
}

void Puzzle::addPresentationImage(ImageHandle *image) {
	if (!image)
		error("[Puzzle::addPresentationImage] Image is not initialized properly");

	// Insert image into presentations images, and sort by priority
	_presentationImages.push_back(image);

	Common::sort(_presentationImages.begin(), _presentationImages.end(), &Puzzle::imagePriorityCompare);
}

void Puzzle::addPresentationAnimation(ObjectPresentation *objectPresentation) {
	if (!objectPresentation)
		error("[Puzzle::addPresentationAnimation] Object presentation is not initialized properly");

	_presentationAnimations.push_back(objectPresentation);
}

void Puzzle::addAccessibility(Accessibility *accessibility) {
	if (!accessibility)
		error("[Puzzle::addAccessibility] Accessibility is not initialized properly");

	_accessibilities.push_back(accessibility);
}

#pragma region Movability

void Puzzle::addMovability(Movability *movability) {
	if (!movability)
		error("[Puzzle::addMovability] Movability is not initialized properly");

	_movabilities.push_back(movability);
}

void Puzzle::setMovabilityOnOrOff(bool enableHotspot) {
	for (Common::Array<Movability *>::iterator it = _movabilities.begin(); it != _movabilities.end(); it++) {
		if (enableHotspot)
			(*it)->enableHotspot();
		else
			(*it)->disableHotspot();
	}
}

void Puzzle::setMovabilityOnOrOff(bool enableHotspot, uint32 fromMovability, uint32 toMovability) {
	// Check from/to movability
	if (toMovability < fromMovability)
		error("[Puzzle::setMovabilityOnOrOff] From movability (%d) is greater than To movability (%d)", fromMovability, toMovability);

	if (fromMovability >= _movabilities.size())
		error("[Puzzle::setMovabilityOnOrOff] From acceleration is not in range (was:%d, max:%d)", fromMovability, _movabilities.size() - 1);

	if (toMovability >= _movabilities.size())
		error("[Puzzle::setMovabilityOnOrOff] To acceleration is not in range (was:%d, max:%d)", fromMovability, _movabilities.size() - 1);


	for (uint32 i = fromMovability; i <= toMovability; i++) {
		if (enableHotspot)
			_movabilities[i]->enableHotspot();
		else
			_movabilities[i]->disableHotspot();
	}
}

#pragma endregion

void Puzzle::setMod(uint32 a2, uint32 a3) {
	_field_24 = a2;
	_field_29 = a3;

	switch (a2){
	default:
		break;

	case 1:
		getApp()->setFreOffCurrentRotation();
		break;

	case 2:
		getApp()->setupCurrentRotation();

		if (getApp()->getBag() && getApp()->getBag()->getField94())
			getApp()->getBag()->sub_419350();

		getApp()->cursorDelete();
		break;
	}
}

#pragma region Visual

void Puzzle::addVisual(Visual *visual) {
	if (!visual)
		error("[Puzzle::addVisual] Visual is not initialized properly");

	if (hasVisual(visual->getId()))
		error("[Puzzle::addVisual] Visual Id already exists (%d)", visual->getId());

	_visuals.push_back(visual);
}

#pragma endregion

#pragma region Sound

void Puzzle::addAmbientSound(SoundEntry *entry, uint32 volume, int32 pan, bool isOn, uint32 fadeFrames, uint32 a6, uint32 a7) {
	SoundItem *item = new SoundItem(_id);
	item->init(entry, volume, pan, isOn, fadeFrames, a6, a7);

	_soundItems.push_back(item);
}

void Puzzle::add3DSound(SoundEntry *entry, uint32 volume, bool isOn, uint32 a4, uint32 a5, uint32 fadeFrames, float a7, uint32 a8) {
	SoundItem *item = new SoundItem(_id);
	item->setField1D(a8);
	item->setAngle(a7);
	item->init(entry, volume, item->computePan(0.0), isOn, a4, a5, fadeFrames, a7, a8);

	_soundItems.push_back(item);
}

void Puzzle::setAmbientSoundOn(Id soundId) {
	SoundItem *item = getSoundItem(soundId);
	if (!item)
		error("[Puzzle::setAmbientSoundOff] Wrong sound Id (%d)", soundId);

	item->on();
}

void Puzzle::setAmbientSoundOff(Id soundId) {
	SoundItem *item = getSoundItem(soundId);
	if (!item)
		error("[Puzzle::setAmbientSoundOff] Wrong sound Id (%d)", soundId);

	item->off();
}

void Puzzle::setAmbientSoundVolume(Id soundId, int32 volume) {
	SoundItem *item = getSoundItem(soundId);
	if (!item)
		error("[Puzzle::setAmbientSoundOff] Wrong sound Id (%d)", soundId);

	item->setVolume(volume);
}

void Puzzle::updateSoundItems() {
	for (Common::Array<SoundItem *>::iterator it = _soundItems.begin(); it != _soundItems.end(); it++) {
		SoundItem *item = (*it);

		if (!item->isOn()) {
			item->turnOff();
			continue;
		}

		if (!item->getSoundEntry() || !item->getSoundEntry()->isPlaying())
			item->turnOn();
	}
}

#pragma endregion

#pragma region Accessors

Movability *Puzzle::getMovability(uint32 index) {
	if (index >= _movabilities.size())
		error("[Puzzle::getMovability] Invalid movability index (was: %d, max:%d)", index, _movabilities.size() - 1);

	return _movabilities[index];
}

#pragma endregion

#pragma region Helpers

SoundItem *Puzzle::getSoundItem(Id soundId) {
	for (Common::Array<SoundItem *>::iterator i = _soundItems.begin(); i != _soundItems.end(); i++) {
		if ((*i)->getSoundEntry()->getId() == soundId)
			return *i;
	}

	return NULL;
}

bool Puzzle::imagePriorityCompare(ImageHandle *image1, ImageHandle *image2) {
	return (image1->getPriority() > image2->getPriority());
}

#pragma endregion

#pragma region Serializable

void Puzzle::saveLoadWithSerializer(Common::Serializer &s) {
	error("[Puzzle::saveLoadWithSerializer] Not implemented!");
}

#pragma endregion

} // End of namespace Ring
