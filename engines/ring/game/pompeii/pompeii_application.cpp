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

#include "ring/game/pompeii/pompeii_application.h"

#include "ring/base/art.h"
#include "ring/base/bag.h"
#include "ring/base/cursor.h"
#include "ring/base/preferences.h"
#include "ring/base/rotation.h"
#include "ring/base/saveload.h"

#include "ring/game/pompeii/pompeii_shared.h"
#include "ring/game/pompeii/pompeii_zonesystem.h"
#include "ring/game/pompeii/pompeii_zone1.h"
#include "ring/game/pompeii/pompeii_zone2.h"
#include "ring/game/pompeii/pompeii_zone3.h"
#include "ring/game/pompeii/pompeii_zone4.h"
#include "ring/game/pompeii/pompeii_zone5.h"
#include "ring/game/pompeii/pompeii_zone6.h"
#include "ring/game/pompeii/pompeii_zone7.h"
#include "ring/game/pompeii/pompeii_zone8.h"
#include "ring/game/pompeii/pompeii_zone9.h"
#include "ring/game/pompeii/pompeii_zone10.h"
#include "ring/game/pompeii/pompeii_zone11.h"
#include "ring/game/pompeii/pompeii_zone12.h"

#include "ring/graphics/screen.h"

#include "ring/sound/soundhandler.h"

#include "ring/debug.h"
#include "ring/helpers.h"
#include "ring/ring.h"

using namespace PompeiiGame;

namespace Ring {

ApplicationPompeii::ApplicationPompeii(RingEngine *engine) : Application(engine) {
	_systemZone = kZone100;

	// Event handlers
	_zoneSystem = new ZoneSystemPompeii(this);
	_zone1      = new Zone1Pompeii(this);
	_zone2      = new Zone2Pompeii(this);
	_zone3      = new Zone3Pompeii(this);
	_zone4      = new Zone4Pompeii(this);
	_zone5      = new Zone5Pompeii(this);
	_zone6      = new Zone6Pompeii(this);
	_zone7      = new Zone7Pompeii(this);
	_zone8      = new Zone8Pompeii(this);
	_zone9      = new Zone9Pompeii(this);
	_zone10     = new Zone10Pompeii(this);
	_zone11     = new Zone11Pompeii(this);
	_zone12     = new Zone12Pompeii(this);
}

ApplicationPompeii::~ApplicationPompeii() {
	SAFE_DELETE(_zoneSystem);
	SAFE_DELETE(_zone1);
	SAFE_DELETE(_zone2);
	SAFE_DELETE(_zone3);
	SAFE_DELETE(_zone4);
	SAFE_DELETE(_zone5);
	SAFE_DELETE(_zone6);
	SAFE_DELETE(_zone7);
	SAFE_DELETE(_zone8);
	SAFE_DELETE(_zone9);
	SAFE_DELETE(_zone10);
	SAFE_DELETE(_zone11);
	SAFE_DELETE(_zone12);
}

#pragma region Game setup

void ApplicationPompeii::initFont() {
	// Original asks for size 12, but the font only contains size 8
	fontAdd(kFontDefault, "pompei.fon", "Arxel1", 8, true, false, false, false, getCurrentLanguage());
}

void ApplicationPompeii::setup() {
	// Add the list of episodes
	addEpisode(kZone2, "One",   2);
	addEpisode(kZone3, "Two",   1);
	addEpisode(kZone4, "Three", 2);
	addEpisode(kZone5, "Four",  1);
	addEpisode(kZone6, "Five",  1);

	// Add the list of zones
	addZone(kZone1,  "S00", "S00", kArchiveArt, kLoadFromCd);
	addZone(kZone2,  "S01", "S01", kArchiveArt, kLoadFromCd);
	addZone(kZone3,  "S02", "S02", kArchiveArt, kLoadFromCd);
	addZone(kZone4,  "S03", "S03", kArchiveArt, kLoadFromCd);
	addZone(kZone5,  "S04", "S04", kArchiveArt, kLoadFromCd);
	addZone(kZone6,  "S05", "S05", kArchiveArt, kLoadFromCd);
	addZone(kZone7,  "S06", "S06", kArchiveArt, kLoadFromCd);
	addZone(kZone8,  "S07", "S07", kArchiveArt, kLoadFromCd);
	addZone(kZone9,  "S08", "S08", kArchiveArt, kLoadFromCd);
	addZone(kZone10, "S09", "S09", kArchiveArt, kLoadFromCd);
	addZone(kZone11, "S10", "S10", kArchiveArt, kLoadFromCd);
	addZone(kZone12, "S11", "S11", kArchiveArt, kLoadFromCd);

	// Setup system zone
	setupZone(kZoneSY, kSetupTypeNone);
	setSpace(kZone100);

	// Setup cursors
	ArchiveType archiveType = (_configuration.artCURSOR ? kArchiveArt : kArchiveFile);

	cursorAdd(kCursorDefault,               "", kCursorTypeNormal, 1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorBusy,          "cur_busy", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorIdle,          "cur_idle", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorMove,           "cur_muv", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorBack,          "cur_back", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorMenuIdle,      "cur_me-1", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorMenuActive,    "cur_me-2", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorZoom,          "cur_zoom", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorTake,          "cur_take", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorAction,        "cur_ac-1", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorActionObject,  "cur_ac-2", kCursorTypeImage,  1, kLoadFromCursor, archiveType);
	cursorAdd(kCursorDragDrop,         "adrag", kCursorTypeImage,  1, kLoadFromCursor, archiveType);

	cursorSetOffset(kCursorBusy,         Common::Point(8, 8));
	cursorSetOffset(kCursorIdle,         Common::Point(17, 1));
	cursorSetOffset(kCursorMove,         Common::Point(17, 1));
	cursorSetOffset(kCursorBack,         Common::Point(17, 1));
	cursorSetOffset(kCursorMenuIdle,     Common::Point(8, 8));
	cursorSetOffset(kCursorMenuActive,   Common::Point(8, 8));
	cursorSetOffset(kCursorZoom,         Common::Point(17, 1));
	cursorSetOffset(kCursorTake,         Common::Point(17, 1));
	cursorSetOffset(kCursorAction,       Common::Point(17, 1));
	cursorSetOffset(kCursorActionObject, Common::Point(17, 1));
	cursorSetOffset(kCursorDragDrop,     Common::Point(8, 8));

	// Setup subtitles
	subtitleSetColor(Color(255, 255, 255));
	subtitleSetBackgroundColor(Color(50, 50, 50));
}

void ApplicationPompeii::initBag() {
	_bag->setOrigin(Common::Point(0, 0));
	_bag->sub_417D40(15, 26, 40, 61);
	_bag->setBackgroundOffset(Common::Point(0, 0));
	_bag->sub_417DD0(10);
	_bag->sub_417D80(0, 0, 30, 448);
	_bag->sub_417DA0(610, 0, 30, 448);
	_bag->sub_4192A0(6, 12);
	_bag->sub_4192C0(622, 12);
	_bag->sub_417DE0(291, 4);
	_bag->sub_419280(500);
	_bag->loadBackground("bagbgr.tga", "", "", "", "", "", "", "bag_h.bmp", _archiveType);
	_bag->initHotspots();
}

#pragma endregion

#pragma region Startup

void ApplicationPompeii::showStartupScreen() {
	// Original setups zones a second time for no good reason
	setCurrentZone(kZone100);

	playMovie("dclogo");
	playMovie("Rmn");
	playMovie("Logo");
	playMovie("Sur");
	playMovie("Arxel");

	varSetByte(90001, 5);
	showDay();

	playMovie("INTRO_-2");
	varSetByte(90001, 0);
	showDay();

	playMovie("INTRO_-1");
	varSetByte(90001, 1);

	playMovie("INTRO_-3");
	varSetByte(90904, 0);

	displayFade("black.bmp", "menu.bmp", 5, 0, kLoadFromDisk, getConfiguration().artSY ? kArchiveArt : kArchiveFile);
	varSetByte(90904, 16);

	setupUser(1);

	_preferenceHandler->load();
}

void ApplicationPompeii::startMenu(bool savegame) {
	error("[ApplicationPompeii::startMenu] Not implemented");
}

void ApplicationPompeii::showMenu(ZoneId zone, MenuAction menuAction) {
	error("[ApplicationPompeii::showMenu] Not implemented");
}

void ApplicationPompeii::showCredits() {
	error("[ApplicationPompeii::showCredits] Not implemented");
}

void ApplicationPompeii::loadPreferences() {
	error("[ApplicationPompeii::loadPreferences] Not implemented");
}

#pragma endregion

#pragma region Drawing

void ApplicationPompeii::draw() {
	// Update our screen
	_screenManager->updateScreen();

	// Update engine state
	//error("[ApplicationPompeii::draw] Engine state update not implemented!");
}

#pragma endregion

#pragma region Visual

Visual *ApplicationPompeii::createVisual(Id visualId, uint32 a3, uint32 a4, uint32 left, uint32 top, uint32 offsetY, uint32 height, uint32 progressMultiplier, uint32 progressColor) {
	error("[ApplicationPompeii::createVisual] Engine state update not implemented!");
}

#pragma endregion

#pragma region Zone initialization

void ApplicationPompeii::initZones() {
	debugC(kRingDebugLogic, "Init zone data");

	_loadFrom = kLoadFromDisk;

	drawZoneName(kZone100);
	_archiveType = getZoneArchiveType(kZone100);
	_zoneSystem->onInit();

	_loadFrom = kLoadFromCd;

	drawZoneName(kZone1);
	_archiveType = getZoneArchiveType(kZone2);
	_zone1->onInit();

	drawZoneName(kZone2);
	_archiveType = getZoneArchiveType(kZone2);
	_zone2->onInit();

	drawZoneName(kZone2);
	_archiveType = getZoneArchiveType(kZone3);
	_zone3->onInit();

	drawZoneName(kZone4);
	_archiveType = getZoneArchiveType(kZone4);
	_zone4->onInit();

	drawZoneName(kZone5);
	_archiveType = getZoneArchiveType(kZone5);
	_zone5->onInit();

	drawZoneName(kZone6);
	_archiveType = getZoneArchiveType(kZone6);
	_zone6->onInit();

	drawZoneName(kZone7);
	_archiveType = getZoneArchiveType(kZone7);
	_zone7->onInit();

	drawZoneName(kZone8);
	_archiveType = getZoneArchiveType(kZone8);
	_zone8->onInit();

	drawZoneName(kZone9);
	_archiveType = getZoneArchiveType(kZone9);
	_zone9->onInit();

	drawZoneName(kZone10);
	_archiveType = getZoneArchiveType(kZone10);
	_zone10->onInit();

	_loadFrom = kLoadFromDisk;

	drawZoneName(kZone11);
	_archiveType = getZoneArchiveType(kZone11);
	_zone11->onInit();

	drawZoneName(kZone12);
	_archiveType = getZoneArchiveType(kZone12);
	_zone12->onInit();

	_archiveType = getZoneArchiveType(getCurrentZone());

	setState(kStateNone);

	// Clear screen
	_screenManager->clear();
	g_system->updateScreen();
}

#pragma endregion

#pragma region Event handling

void ApplicationPompeii::onMouseLeftButtonUp(const Common::Event &evt, bool isControlPressed) {
	warning("[ApplicationPompeii::onMouseLeftButtonUp] Not implemented (evt: %d, CTRL pressed: %d)", evt.type, isControlPressed);
}

void ApplicationPompeii::onMouseLeftButtonDown(const Common::Event &evt) {
	warning("[ApplicationPompeii::onMouseLeftButtonDown] Not implemented (evt: %d)", evt.type);
}

void ApplicationPompeii::onMouseRightButtonUp(const Common::Event &evt) {
	warning("[ApplicationPompeii::onMouseRightButtonUp] Not implemented (evt: %d)", evt.type);
}

void ApplicationPompeii::onKeyDown(Common::Event &evt) {
	error("[ApplicationPompeii::onKeyDown] Not implemented (evt: %d)", evt.type);
}

void ApplicationPompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	debugC(kRingDebugLogic, "onButtonUp (ObjectId: %d, target: %d, coords: (%d, %d))", id.id(), target, point.x, point.y);

	if (puzzleRotationId == 1 && a4 == 1) {
		_zoneSystem->onButtonUp(id, target, puzzleRotationId, a4, point);
		return;
	}

	switch (getCurrentZone()) {
	default:
		break;

	case kZone100:
		_zoneSystem->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone1:
		_zone1->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone2:
		_zone2->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone3:
		_zone3->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone4:
		_zone4->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone5:
		_zone5->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone6:
		_zone6->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone7:
		_zone7->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone8:
		_zone8->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone9:
		_zone9->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone10:
		_zone10->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone11:
		_zone11->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;

	case kZone12:
		_zone12->onButtonUp(id, target, puzzleRotationId, a4, point);
		break;
	}

	if (!sub_42F7B0()) {
		bagRemove(kObjectItemList);
		bagAdd(kObjectItemListCompleted);
	}
}

void ApplicationPompeii::onTimer(TimerId timerId) {
	debugC(kRingDebugLogic, "onTimer (id: %d)", timerId);

	switch (getCurrentZone()) {
	default:
		break;

	case kZone1:
		_zone1->onTimer(timerId);
		break;

	case kZone2:
		_zone2->onTimer(timerId);
		break;

	case kZone3:
		_zone3->onTimer(timerId);
		break;

	case kZone4:
		_zone4->onTimer(timerId);
		break;

	case kZone5:
		_zone5->onTimer(timerId);
		break;

	case kZone6:
		_zone6->onTimer(timerId);
		break;

	case kZone8:
		_zone8->onTimer(timerId);
		break;

	case kZone9:
		_zone9->onTimer(timerId);
		break;

	case kZone10:
		_zone10->onTimer(timerId);
		break;

	case kZone11:
		_zone11->onTimer(timerId);
		break;

	case kZone12:
		_zone12->onTimer(timerId);
		break;
	}
}

void ApplicationPompeii::onSound(Id id, SoundType type, uint32 a3) {
	debugC(kRingDebugLogic, "onSound (id: %d, type: %d)", id, type);

	bool process = (a3 & 0x1000) != 0;
	a3 &= 239;

	switch (getCurrentZone()) {
	default:
		break;

	case kZone100:
		_zoneSystem->onSound(id, type, a3, process);
		break;

	case kZone1:
		_zone1->onSound(id, type, a3, process);
		break;

	case kZone2:
		_zone2->onSound(id, type, a3, process);
		break;

	case kZone3:
		_zone3->onSound(id, type, a3, process);
		break;

	case kZone4:
		_zone4->onSound(id, type, a3, process);
		break;

	case kZone5:
		_zone5->onSound(id, type, a3, process);
		break;

	case kZone6:
		_zone6->onSound(id, type, a3, process);
		break;

	case kZone7:
		_zone7->onSound(id, type, a3, process);
		break;

	case kZone8:
		_zone8->onSound(id, type, a3, process);
		break;

	case kZone10:
		_zone10->onSound(id, type, a3, process);
		break;

	case kZone11:
		_zone11->onSound(id, type, a3, process);
		break;

	case kZone12:
		_zone12->onSound(id, type, a3, process);
		break;
	}
}

void ApplicationPompeii::onSetup(ZoneId zone, SetupType type) {
	debugC(kRingDebugLogic, "onSetup (zone: %s, type: %d)", getZoneFolder(zone).c_str(), type);

	switch (zone) {
	default:
		break;

	case kZone2:
		_zone2->onSetup(type);
		break;

	case kZone3:
		_zone3->onSetup(type);
		break;

	case kZone4:
		_zone4->onSetup(type);
		break;
	}
}

void ApplicationPompeii::onBag(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, DragControl *dragControl, byte type) {
	if (getCurrentZone() == kZone100)
		_zoneSystem->onBag(id, target, puzzleRotationId, a4, dragControl, type);
}

void ApplicationPompeii::onUpdateBefore(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, const Common::Point &point) {
	if (movabilityIndex == 1 && target == 1) {
		_zoneSystem->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		return;
	}

	if (hasCurrentRotation())
		varSetWord(99028, getCurrentRotationId());

	switch (getCurrentZone()) {
	default:
		break;

	case kZone100:
		_zoneSystem->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone1:
		_zone1->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone2:
		_zone2->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone3:
		_zone3->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone4:
		_zone4->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone6:
		_zone6->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone7:
		_zone7->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone8:
		_zone8->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone9:
		_zone9->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone11:
		_zone11->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;

	case kZone12:
		_zone12->onUpdateBefore(movabilityFrom, movabilityTo, movabilityIndex, target, point);
		break;
	}
}

void ApplicationPompeii::onUpdateAfter(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType, const Common::Point &point) {
	if (movabilityFrom == 1)
		return;

	visualBoxHide(6, kPuzzleMenu);
}

void ApplicationPompeii::onUpdateBag(const Common::Point &point) {
	if (getCurrentZone() == kZone100)
		_cursorHandler->select(kCursorMenuIdle);

	if (_bag->isInitialized()) {
		_cursorHandler->select(kCursorMenuIdle);
		objectPresentationHide(kObjectItemList);
		objectSetAccessibilityOff(kObjectItemList);
	}

	switch (getCurrentZone()) {
	default:
		break;

	case kZone100:
		_zoneSystem->onUpdateBag(point);
		break;

	case kZone1:
		_zone1->onUpdateBag(point);
		break;

	case kZone2:
		_zone2->onUpdateBag(point);
		break;

	case kZone3:
		_zone3->onUpdateBag(point);
		break;

	case kZone4:
		_zone4->onUpdateBag(point);
		break;

	case kZone6:
		_zone6->onUpdateBag(point);
		break;

	case kZone7:
		_zone7->onUpdateBag(point);
		break;

	case kZone8:
		_zone8->onUpdateBag(point);
		break;

	case kZone11:
		_zone11->onUpdateBag(point);
		break;

	case kZone12:
		_zone12->onUpdateBag(point);
		break;
	}
}

void ApplicationPompeii::onBagClickedObject(ObjectId id) {
	if (hasCurrentRotation())
		varSetDword(99028, getCurrentRotationId());

	switch (getCurrentZone()) {
	default:
		break;

	case kZone1:
		_zone1->onBagClickedObject(id);
		break;

	case kZone2:
	case kZone3:
		_zone2->onBagClickedObject(id);
		break;
	}

	// All zones also use the system event
	_zoneSystem->onBagClickedObject(id);
}

void ApplicationPompeii::onBeforeRide(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType) {
	if (movabilityFrom == 1)
		return;

	if (hasCurrentRotation())
		varSetDword(99027, getCurrentRotationId());

	switch (getCurrentZone()) {
	default:
		break;

	case kZone1:
		_zone1->onBeforeRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;

	case kZone2:
		_zone2->onBeforeRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;

	case kZone4:
		_zone4->onBeforeRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;

	case kZone10:
		_zone10->onBeforeRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;
	}
}

void ApplicationPompeii::onAfterRide(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType) {
	if (movabilityFrom == 1)
		return;

	if (!varGetByte(90001))
		return;

	if (!sub_42F7B0()) {
		bagRemove(kObjectItemList);
		bagAdd(kObjectItemListCompleted);
	}

	switch (getCurrentZone()) {
	default:
		break;

	case kZone1:
		_zone1->onAfterRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;

	case kZone2:
		_zone2->onAfterRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;

	case kZone6:
		_zone6->onAfterRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;

	case kZone11:
		_zone11->onAfterRide(movabilityFrom, movabilityTo, movabilityIndex, target, movabilityType);
		break;
	}
}

void ApplicationPompeii::onAnimationNextFrame(Id animationId, const Common::String &name, uint32 frame, uint32 frameCount) {
	switch (getCurrentZone()) {
	default:
		break;

	case kZone1:
		_zone1->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone2:
		_zone2->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone3:
		_zone3->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone4:
		_zone4->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone5:
		_zone5->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone6:
		_zone6->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone7:
		_zone7->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone8:
		_zone8->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone9:
		_zone9->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone10:
		_zone10->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone11:
		_zone11->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;

	case kZone12:
		_zone12->onAnimationNextFrame(animationId, name, frame, frameCount);
		break;
	}
}

void ApplicationPompeii::onVisualList(Id id, uint32 type, const Common::Point &point) {
	error("[ApplicationPompeii::onVisualList] Not implemented");
}

#pragma endregion

#pragma region Helpers

bool ApplicationPompeii::sub_42F7B0() {
	error("[ApplicationPompeii::sub_42F7B0] Not implemented");
}

void ApplicationPompeii::showDay() {
	switch (varGetByte(90001)) {
	default:
		_message = "";
		break;

	case 0:
		messageGet("Day0");
		break;

	case 1:
		messageGet("Day1");
		break;

	case 2:
		messageGet("Day2");
		break;

	case 3:
		messageGet("Day3");
		break;

	case 4:
		messageGet("Day4");
		break;

	case 5:
		messageGet("Day5");
		break;
	}

	objectPresentationSetTextToPuzzle(kObject1, 1, 0, _message);
}

void ApplicationPompeii::setupUser(Id userId) {
	warning("[ApplicationPompeii::setupUser] Not implemented");
}

#pragma endregion

} // End of namespace Ring
