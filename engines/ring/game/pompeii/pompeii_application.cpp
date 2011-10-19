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
#include "ring/base/timer.h"

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

#include "ring/graphics/image.h"
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

	// Data
	_savedZone = kZoneNone;
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
	visualBoxHide(6, kPuzzleMenu);

	if (_currentGameZone)
		return;

	if (savegame) {
		cursorSelect(kCursorBusy);
		_vm->setFlag(false);
		_bag->reset();

		if (!_saveManager->loadSave(0, kLoadSaveWrite))
			error("[ApplicationRing::startMenu] Cannot save game in slot 0");

		// Save a copy of the screen surface for savegame
		SAFE_DELETE(_thumbnail);

		_thumbnail = new Image();
		_thumbnail->create(24, 2, 640, 480);

		// Save a copy of the screen to our image
		_screenManager->copySurface(_thumbnail);
	}

	_currentGameZone = getCurrentZone();

	soundStopAll(4);
	timerStopAll();
	setupZone(kZone1, kSetupTypeNone);
	setSpace(kZone100);
	puzzleSetActive(kPuzzleGeneralMenu, true, true);
	puzzleSetMod(kPuzzleMenu, 1, 0);

	for (uint32 i = 1; i < 8; i++) {
		objectSetAccessibilityOff(i);
		objectPresentationHideAndRemove(i);
	}

	Bag *bag = getBag();
	if (bag && bag->isInitialized())
		bag->reset();

	cursorDelete();

	if (savegame)
		objectSetAccessibilityOn(kObject99002);
	else
		objectSetAccessibilityOn(kObject99002);

	// Load user preferences
	setUser("user1");
	_preferenceHandler->load();
}

void ApplicationPompeii::showMenu(ZoneId zone, MenuAction menuAction) {
	error("[ApplicationPompeii::showMenu] Not implemented");
}

void ApplicationPompeii::showCredits() {
	soundStopAll(1024);
	soundPlay(90801, kSoundLoop);
	setCurrentZone(kZone100);

	// Scroll credits
	for (uint i = 0; i < 14; i++) {
		if (scrollImage(Common::String::format("cre%02d", i + 1), 0, kLoadFromDisk, _configuration.artSY ? kArchiveArt : kArchiveFile))
			break;
	}

	soundStop(90801, 1024);
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

#pragma region Messages

void ApplicationPompeii::messageInsertCd(ZoneId zone) {
	setupZone(kZone1, kSetupTypeNone);
	setSpace(kZone100);

	for (uint32 i = 0; i <= 7; i++) {
		objectSetAccessibilityOff(i);
		objectPresentationHideAndRemove(i);
	}

	objectPresentationSetTextToPuzzle(kObject16, 0, 0, _messageType);
	objectPresentationSetTextCoordinatesToPuzzle(kObject16, 0, 0, Common::Point(225, 193));
	objectPresentationSetTextToPuzzle(kObject16, 0, 1, _message);
	objectPresentationSetTextCoordinatesToPuzzle(kObject16, 0, 1, Common::Point(225, 213));
	objectPresentationShow(kObject16, 0);
	objectSetAccessibilityOff(kObject16);

	if (zone == kZone3)
		objectSetAccessibilityOn(kObject16, 1, 2);
	else
		objectSetAccessibilityOn(kObject16, 0, 1);

	puzzleSetActive(kPuzzleInsertCd);
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
	Common::KeyCode keycode = evt.kbd.keycode;

	switch (getCurrentPuzzleId()) {
	default:
		if (keycode == Common::KEYCODE_SPACE
		 && !soundIsPlayingType(kSoundTypeDialog)) {
			objectPresentationHide(kObjectItemList);
			objectSetAccessibilityOff(kObjectItemList);
			visualBoxHide(6, kPuzzleMenu);

			if (!varGetByte(90508)) {
				puzzleSetMod(kPuzzleMenu, 2, 6);
				objectPresentationShow(kObject6, 0);
				objectSetAccessibilityOn(kObject6);
				if (hasCurrentRotation())
					varSetDword(99027, (int16)getCurrentRotationId());

				objectPresentationShow(kObject6, 5);
				setCoordinatesOnPuzzle6();
				objectSetAccessibilityOn(kObject6, 1, 4);
				objectSetAccessibilityOff(kObject6, 6, 18);
				varSetByte(90508, 1);
			}
		}
		break;

	case kPuzzleEncyclopedia:
	case kPuzzle50001:
	case kPuzzlePreferences:
	case kPuzzleStatus:
	case kPuzzle90005:
	case kPuzzleInsertCd:
		break;

	case kPuzzleLoad:
		if (keycode == Common::KEYCODE_DELETE) {
			if (visualListGetObjectIdClicked(4, kPuzzleLoad)) {
				messageGet("DoYouWantToDeleteSavedGame");
				messageShowQuestion(8);
			}
		}
		break;

	case kPuzzleSave:
		if (keycode == Common::KEYCODE_DELETE) {
			if (visualListGetObjectIdClicked(1, kPuzzleSave)) {
				messageGet("DoYouWantToDeleteSavedGame");
				messageShowQuestion(4);
			}

			break;
		}

		visualListResetObjectClicked(1, kPuzzleSave);
		objectSetAccessibilityOn(kObject99025);
		objectPresentationHide(kObject99025, 1);

		switch (keycode) {
		default:
			if (objectPresentationGetTextWidth(kObjectSaveName, 1, 0) >= 235)
				return;

			*getSaveManager()->getName() += (char)evt.kbd.ascii;
			break;

		case Common::KEYCODE_ESCAPE:
			getSaveManager()->getName()->clear();
			break;

		case Common::KEYCODE_BACKSPACE:
			if (getSaveManager()->getName()->size() != 1)
				getSaveManager()->getName()->deleteLastChar();
			break;

		case Common::KEYCODE_RETURN:
			// Do nothing
			return;
		}

		objectPresentationSetTextToPuzzle(kObjectSaveName, 1, 0, *getSaveManager()->getName());
		objectPresentationSetTextCoordinatesToPuzzle(kObjectSaveName, 1, 0, Common::Point(344, 181));
		objectPresentationSetAnimationCoordinatesOnPuzzle(kObjectSaveName, 0, Common::Point((int16)objectPresentationGetTextWidth(kObjectSaveName, 1, 0) + 30, 435));
		break;
	}
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

	if (!checkBag()) {
		bagRemove(kObjectItemList);
		bagAdd(kObjectItemListCompleted);
	}
}

void ApplicationPompeii::onTimer(TimerId timerId) {
	debugC(kRingDebugLogic, "[ApplicationPompeii::onTimer] Timer id: %d", timerId);

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

	if (getState() != kStateShowMenu)
		getTimerHandler()->incrementFiredCount(timerId);
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
		varSetWord(99028, (int16)getCurrentRotationId());

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
		_zone3->onBagClickedObject(id);
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

	if (!checkBag()) {
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
	switch (id) {
	default:
		break;

	case 1:
		if (type == 3) {
			Common::String userFolder = getObject(visualListGetObjectIdClicked(1, kPuzzleLoad))->getName();
			objectPresentationSetTextToPuzzle(99601, 1, 0, userFolder);
			objectPresentationSetAnimationCoordinatesOnPuzzle(99601, 0, Common::Point((int16)objectPresentationGetTextWidth(99601, 1, 0) + 30, 435));
			objectSetAccessibilityOn(kObject99025);
			objectPresentationHide(kObject99025, 1);
			varSetByte(98003, 1);
		}
		break;

	case 4:
		if (type == 3) {
			Common::String userFolder = getObject(visualListGetObjectIdClicked(1, kPuzzlePreferences))->getName();
			objectPresentationSetTextToPuzzle(99601, 1, 1, userFolder);
			objectPresentationShow(kObjectSaveName, 1);
			objectSetAccessibilityOn(kObject99023);
			objectPresentationHide(kObject99023, 1);
		}
		break;

	case 6:
		if (type == 6 || type == 7) {
			int x = point.x;
			if (type == 7 && point.y > 0)
				x += 100000;

			switch (getCurrentZone()) {
			default:
				break;

			case kZone1:
				_zone1->onVisual(x);
				break;

			case kZone2:
				_zone2->onVisual(x);
				break;

			case kZone3:
				_zone3->onVisual(x);
				break;

			case kZone4:
				_zone4->onVisual(x);
				break;

			case kZone6:
				_zone6->onVisual(x);
				break;

			case kZone7:
				_zone7->onVisual(x);
				break;

			case kZone8:
				_zone8->onVisual(x);
				break;

			case kZone11:
				_zone11->onVisual(x);
				break;

			case kZone12:
				_zone12->onVisual(x);
				break;
			}
		}
		break;
	}
}

#pragma endregion

#pragma region Helpers

uint32 ApplicationPompeii::checkBag() {
	uint32 count = 9;

	objectPresentationHide(kObjectItemList);

	for (uint32 i = 0; i < 9; i++) {
		ObjectId object = (ObjectId)(kObjectStones + i);
		if (bagHas(object)) {
			objectPresentationShow(kObjectItemList, 0);
			objectSetAccessibilityOn(kObjectItemList);
			bagRemove(object);

			for (uint32 j = 0; j < 9; j++) {
				if (varGetByte(91200 + j) > 0)
					objectPresentationShow(kObjectItemList, j);
			}

			uint32 startTick = g_system->getMillis();
			while (g_system->getMillis() - startTick < 1000)
				handleEvents();

			varSetByte(object, 1);
			objectPresentationShow(kObjectItemList, i + 1);
			soundPlay(990015);
		}

		if (varGetByte(object) > 0)
			--count;
	}

	return count;
}

static const struct {
	int32 val;
	int16 multiplierX;
	int16 multiplierY;
} _puzzle6Coordinates[] = {
	{10155,    336, 273},
	{10011,    327, 296},
	{1001102,  327, 296},
	{1001103,  327, 296},
	{10012,    305, 283},
	{1001202,  305, 283},
	{10013,    295, 292},
	{10014,    345, 250},
	{1001402,  345, 250},
	{10015,    380, 223},
	{1001502,  380, 223},
	{10016,    417, 193},
	{1001602,  417, 193},
	{10017,    451, 166},
	{1001702,  451, 166},
	{10018,    461, 158},
	{1001802,  461, 158},
	{10019,    484, 197},
	{1001902,  484, 197},
	{100110,   502, 183},
	{10011002, 502, 183},
	{100111,   384, 344},
	{10011102, 384, 344},
	{10011103, 384, 344},
	{100112,   355, 319},
	{10011202, 355, 319},
	{10011203, 355, 319},
	{100113,   329, 302},
	{10011302, 329, 302},
	{10011303, 329, 302},
	{100114,   329, 265},
	{10011402, 329, 265},
	{10021,    205, 334},
	{10022,    199, 354},
	{10023,    201, 328},
	{10024,    172, 325},
	{10025,    176, 304},
	{10026,    158, 274},
	{10027,    222, 327},
	{10028,    209, 349},
	{10029,    194, 355},
	{100210,   186, 349},
	{100211,   179, 333},
	{100212,   166, 312},
	{100213,   191, 340},
	{100214,   184, 325},
	{100215,   178, 314},
	{100216,   172, 307},
	{100217,   172, 296},
	{100218,   203, 334},
	{100219,   198, 335},
	{100220,   190, 316},
	{100221,   186, 307},
	{10031,    325, 306},
	{100312,   325, 306},
	{10032,    302, 324},
	{100322,   302, 324},
	{10041,    538, 164},
	{10042,    554, 191},
	{10043,    538, 164},
	{10044,    554, 191},
	{10045,    554, 191},
	{10046,    569, 204},
	{10047,    569, 191},
	{10048,    554, 191},
	{100410,   538, 164},
	{100411,   538, 164},
	{100412,   538, 164},
	{100413,   585, 196},
	{10051,    309, 358},
	{1005102,  309, 358},
	{10052,    309, 358},
	{1005202,  309, 358},
	{10053,    309, 358},
	{1005302,  309, 358},
	{10054,    309, 358},
	{1005402,  309, 358},
	{10055,    309, 358},
	{1005502,  309, 358},
	{10056,    309, 358},
	{1005602,  309, 358},
	{10057,    309, 358},
	{1005702,  309, 358},
	{10058,    309, 358},
	{1005802,  309, 358},
	{10059,    309, 358},
	{1005902,  309, 358},
	{100510,   309, 358},
	{10051002, 309, 358},
	{100511,   309, 358},
	{10051102, 309, 358},
	{100512,   309, 358},
	{10051202, 309, 358},
	{100513,   309, 358},
	{10051302, 309, 358},
	{100514,   309, 358},
	{10051402, 309, 358},
	{100515,   309, 358},
	{10051502, 309, 358},
	{100516,   309, 358},
	{10051602, 309, 358},
	{100517,   309, 358},
	{10051702, 309, 358},
	{100518,   309, 358},
	{10051802, 309, 358},
	{100519,   309, 358},
	{10051902, 309, 358},
	{100520,   309, 358},
	{10052002, 309, 358},
	{100521,   309, 358},
	{10052102, 309, 358},
	{100522,   309, 358},
	{10052202, 309, 358},
	{10111,    336, 273},
	{10112,    336, 273},
	{10113,    336, 273},
	{10114,    336, 273},
	{10121,    336, 273},
	{10122,    336, 273},
	{10123,    336, 273},
	{10124,    336, 273},
	{10125,    336, 273},
	{10126,    336, 273},
	{10127,    336, 273},
	{10128,    336, 273},
	{10131,    336, 273},
	{10141,    336, 273},
	{10142,    336, 273},
	{10151,    336, 273},
	{10152,    336, 273},
	{10153,    336, 273},
	{10154,    336, 273},
	{10161,    336, 273},
	{10162,    336, 273},
	{10163,    336, 273},
	{10164,    336, 273},
	{10166,    336, 273},
	{10171,    336, 273},
	{10172,    336, 273},
	{10173,    336, 273},
	{10181,    336, 273},
	{10191,    336, 273},
	{10101,    336, 273},
	{20111,    336, 273},
	{20112,    336, 273},
	{20113,    336, 273},
	{20114,    336, 273},
	{20121,    336, 273},
	{20122,    336, 273},
	{20123,    336, 273},
	{20124,    336, 273},
	{20125,    336, 273},
	{20126,    336, 273},
	{20127,    336, 273},
	{20128,    336, 273},
	{20161,    336, 273},
	{20162,    336, 273},
	{20163,    336, 273},
	{20164,    336, 273},
	{20166,    336, 273},
	{20171,    336, 273},
	{20172,    336, 273},
	{20173,    336, 273},
	{10211,    464, 162},
	{102112,   464, 162},
	{10212,    464, 162},
	{10213,    464, 162},
	{10214,    464, 162},
	{10215,    464, 162},
	{10221,    469, 167},
	{10231,    473, 167},
	{10232,    473, 167},
	{10233,    473, 167},
	{10241,    479, 176},
	{10242,    479, 176},
	{10243,    487, 182},
	{10301,    212, 321},
	{10302,    212, 321},
	{10303,    212, 321},
	{10304,    212, 321},
	{10305,    212, 321},
	{10411,    150, 279},
	{10412,    150, 279},
	{10413,    150, 279},
	{10414,    150, 279},
	{10431,    150, 279},
	{10441,    150, 279},
	{10442,    150, 279},
	{10451,    150, 279},
	{10452,    150, 279},
	{10511,    386, 224},
	{10521,    386, 224},
	{10531,    386, 224},
	{10611,    168, 336},
	{10612,    168, 336},
	{10613,    168, 336},
	{10614,    168, 336},
	{10615,    168, 336},
	{10616,    168, 336},
	{10617,    168, 336},
	{10618,    168, 336},
	{10619,    168, 336},
	{106110,   168, 336},
	{10621,    168, 336},
	{10622,    168, 336},
	{10623,    168, 336},
	{10624,    168, 336},
	{10711,    321, 318},
	{10712,    321, 318},
	{10713,    321, 318},
	{10714,    321, 318},
	{10715,    321, 318},
	{10721,    321, 318},
	{10811,    526, 195},
	{10812,    526, 195},
	{10813,    526, 195},
	{10814,    526, 195},
	{10815,    526, 195},
	{10816,    526, 195},
	{10911,    546, 161},
	{10912,    560, 191},
	{10913,    553, 179},
	{10921,    573, 165},
	{10922,    584, 178},
	{10923,    584, 178},
	{10924,    573, 165},
	{10925,    573, 165},
	{10931,    591, 184},
	{10932,    589, 189},
	{11011,    421, 196},
	{11021,    421, 196},
	{11022,    421, 196},
	{11023,    421, 196},
	{11024,    421, 196},
	{11025,    421, 196},
	{11111,    327, 335},
	{11112,    327, 335},
	{11113,    327, 335},
	{11114,    327, 335},
	{11121,    327, 335},
	{11122,    327, 335},
	{11123,    327, 335},
	{11124,    327, 335}
};

void ApplicationPompeii::setCoordinatesOnPuzzle6() {
	for (int i = 0; i < ARRAYSIZE(_puzzle6Coordinates); i++) {
		if (varGetDword(99027) == _puzzle6Coordinates[i].val)
			objectPresentationSetAnimationCoordinatesOnPuzzle(kObject6,
			                                                  5,
			                                                  Common::Point((int16)(_puzzle6Coordinates[i].multiplierX * varGetByte(90509) - varGetWord(99501)),
			                                                                (int16)(_puzzle6Coordinates[i].multiplierY * varGetByte(90509) - varGetWord(99502))));
	}
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

void ApplicationPompeii::onCall(Id callType) {
	error("[ApplicationPompeii::onCall] Not implemented");
}

bool ApplicationPompeii::giveMoney(int16 amount) {
	if (varGetWord(99500) - amount < 0) {
		// Not enough money
		messageFormat("NotEnoughMoney", varGetWord(99500), amount);
		messageShowWarning(0);

		return false;
	}

	varSetWord(99500, varGetWord(99500) - amount);
	if (!varGetWord(99500))
		bagRemove(kObjectSesterces);

	return true;
}

void ApplicationPompeii::takeMoney(int16 amount) {
	varSetWord(99500, varGetWord(99500) + amount);
	if (!bagHas(kObjectSesterces))
		bagAdd(kObjectSesterces);
}

void ApplicationPompeii::showEncyclopedia(uint32 index) {
	_savedZone = getCurrentZone();
	setCurrentZone(kZone100);

	if (hasCurrentPuzzle()) {
		varSetByte(90905, 1);
		varSetDword(90026, getCurrentPuzzleId());
	} else {
		varSetByte(90905, 0);
		varSetDword(90026, getCurrentRotationId());
	}

	puzzleSetActive(kPuzzleEncyclopedia);
	visualEncyclopediaShowFile(5, kPuzzleEncyclopedia, Common::String::format("E%03d.out", index));
}

void ApplicationPompeii::restore() {
	if (varGetByte(90905) == 1)
		puzzleSetActive(varGetDword(90026));
	else
		rotationSetActive(varGetDword(90026));

	setSpace(_savedZone);
}

#pragma endregion

} // End of namespace Ring
