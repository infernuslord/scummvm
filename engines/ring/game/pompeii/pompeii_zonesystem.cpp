/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 7
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 07110-1301, USA.
 */

#include "ring/game/pompeii/pompeii_zonesystem.h"

#include "ring/game/pompeii/pompeii_application.h"
#include "ring/game/pompeii/pompeii_shared.h"

#include "ring/debug.h"
#include "ring/ring.h"

using namespace PompeiiGame;

namespace Ring {

ZoneSystemPompeii::ZoneSystemPompeii(ApplicationPompeii *application) : _app(application) {
}

ZoneSystemPompeii::~ZoneSystemPompeii() {
	// Zero-out passed pointers
	_app = NULL;
}

void ZoneSystemPompeii::onInit() {
	_app->setCurrentZone(kZone100);

	_app->puzzleAdd(kPuzzleMenu);
	_app->objectAdd(kObject1, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject1, kPuzzleMenu, Common::Rect(0, 0, 640, 480), false, kCursorDefault, 0);
	_app->objectAddPresentation(kObject1);
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1,  16), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1,  32), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1,  48), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1,  64), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1,  80), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1,  96), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1, 112), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1, 128), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationAddTextToPuzzle(kObject1, 0, kPuzzleMenu, "", Common::Point(1, 144), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectPresentationShow(kObject1, 0);
	_app->objectAddPresentation(kObject1);
	_app->objectPresentationAddTextToPuzzle(kObject1, 1, kPuzzleMenu, "", Common::Point(10, 464), kFontDefault, Color(255, 255, 255), Color(0, 0, 0));
	_app->objectPresentationShow(kObject1, 1);
	_app->puzzleAdd(kPuzzleEncyclopedia);
	_app->puzzleAddBackgroundImage(kPuzzleEncyclopedia, "encyclopedia.bmp", Common::Point(0, 0), true);
	_app->objectAdd(kObjectExitEncyclopedia, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObjectExitEncyclopedia, kPuzzleEncyclopedia, Common::Rect(0, 440, 250, 480), true, kCursorMenuActive, 0);
	_app->objectSetPuzzleAccessibilityKey(kObjectExitEncyclopedia, 0, Common::KEYCODE_ESCAPE);
	_app->puzzleAdd(kPuzzle99001);
	_app->puzzleAddBackgroundImage(kPuzzle99001, "concl_p01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle99002);
	_app->puzzleAddBackgroundImage(kPuzzle99002, "concl_p02.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle99003);
	_app->puzzleAddBackgroundImage(kPuzzle99003, "concl_p06.bmp", Common::Point(0, 16), true);
	_app->objectAdd(kObject99009, "", "", 1);
	_app->objectAddPresentation(kObject99009);
	_app->objectPresentationAddAnimationToPuzzle(kObject99009, 0, kPuzzle99001, "concl_p01s01", kImageTypeBMP, Common::Point(158,  41), kDrawType1, 1000, 28, 12.5, 4);
	_app->objectPresentationAddAnimationToPuzzle(kObject99009, 0, kPuzzle99002, "concl_p02s01", kImageTypeBMP, Common::Point(311,  19), kDrawType1, 1000, 28, 12.5, 4);
	_app->objectPresentationAddAnimationToPuzzle(kObject99009, 0, kPuzzle99003, "concl_p06s01", kImageTypeBMP, Common::Point(170, 105), kDrawType1, 1000, 28, 12.5, 4);
	_app->objectAdd(kObject6, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(0, 420, 640, 480), false, kCursorBack, 0);
	_app->objectSetPuzzleAccessibilityKey(kObject6, 0, Common::KEYCODE_SPACE);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(  0,   0, 320, 240), false, kCursorZoom, 1);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(320,   0, 640, 240), false, kCursorZoom, 2);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(  0, 240, 320, 420), false, kCursorZoom, 3);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(320, 240, 640, 420), false, kCursorZoom, 4);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(  0,   0,   1,   1), false, kCursorZoom, 5);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(  5,  52,  58, 111), false, kCursorZoom, 6);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(  2, 176,  47, 213), false, kCursorZoom, 7);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(  0, 133,  50, 168), false, kCursorZoom, 8);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(270,  61, 334,  94), false, kCursorZoom, 9);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(305, 178, 359, 212), false, kCursorZoom, 10);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(363, 171, 394, 206), false, kCursorZoom, 11);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(405, 153, 468, 181), false, kCursorZoom, 12);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(568, 199, 637, 234), false, kCursorZoom, 13);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect( 75, 402, 155, 457), false, kCursorZoom, 14);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(183, 389, 256, 431), false, kCursorZoom, 15);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(367, 392, 476, 434), false, kCursorZoom, 16);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(467, 331, 557, 355), false, kCursorZoom, 17);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(410, 319, 464, 367), false, kCursorZoom, 18);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 0, kPuzzleMenu, "map_00.bmp", Common::Point(0, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 1, kPuzzleMenu, "map_01.bmp", Common::Point(0, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 2, kPuzzleMenu, "map_02.bmp", Common::Point(0, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 3, kPuzzleMenu, "map_03.bmp", Common::Point(0, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 4, kPuzzleMenu, "map_04.bmp", Common::Point(0, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddAnimationToPuzzle(kObject6, 5, kPuzzleMenu, "map_where", kImageTypeTGA, Common::Point(0, 0), kDrawType3, 1100, 3, 5.0, 4);
	_app->objectPresentationSetAnimationCoordinatesOnPuzzle(6, 5, Common::Point(0, 0));
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 6, kPuzzleMenu, "map_s01a02n02r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 7, kPuzzleMenu, "map_s11a02n01r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 8, kPuzzleMenu, "map_s07a01n01r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 9, kPuzzleMenu, "map_s04a03n01r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 10, kPuzzleMenu, "map_s06a02n01r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 11, kPuzzleMenu, "map_s00a02n04r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 12, kPuzzleMenu, "map_s03a01n02r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 13, kPuzzleMenu, "map_s00a05n04r01.bmp", Common::Point(98, 371), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 14, kPuzzleMenu, "map_s05a01n01r01.bmp", Common::Point(98, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 15, kPuzzleMenu, "map_s10a01n01r01.bmp", Common::Point(98, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 16, kPuzzleMenu, "map_s08a01n02r01.bmp", Common::Point(98, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 17, kPuzzleMenu, "map_s09a02n01r01.bmp", Common::Point(98, 0), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject6);
	_app->objectPresentationAddImageToPuzzle(kObject6, 18, kPuzzleMenu, "map_s00a04n06r01.bmp", Common::Point(98, 0), true, kDrawType1, 1000);
	_app->objectAdd(kObjectItemListCompleted, "Item list completed", "st_yes", 1);
	_app->objectAdd(kObjectItemList, "Item list", "ist_no", 1);
	_app->objectAddPuzzleAccessibility(kObjectItemList, kPuzzleMenu, Common::Rect(0, 0, 640, 480), false, kCursorBack, 0);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 0, kPuzzleMenu, "list.bmp", Common::Point(226, 86), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 1, kPuzzleMenu, "list_1.bmp", Common::Point(239, 102), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 2, kPuzzleMenu, "list_2.bmp", Common::Point(239, 134), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 3, kPuzzleMenu, "list_3.bmp", Common::Point(239, 157), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 4, kPuzzleMenu, "list_4.bmp", Common::Point(239, 181), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 5, kPuzzleMenu, "list_5.bmp", Common::Point(239, 213), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 6, kPuzzleMenu, "list_6.bmp", Common::Point(239, 246), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 7, kPuzzleMenu, "list_7.bmp", Common::Point(239, 289), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 8, kPuzzleMenu, "list_8.bmp", Common::Point(239, 312), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectItemList);
	_app->objectPresentationAddImageToPuzzle(kObjectItemList, 9, kPuzzleMenu, "list_9.bmp", Common::Point(239, 336), true, kDrawType1, 1000);
	_app->objectAddPuzzleAccessibility(kObject6, kPuzzleMenu, Common::Rect(0, 420, 640, 480), false, kCursorBack, 99);
	_app->puzzleAdd(kPuzzleGeneralMenu);
	_app->puzzleAddBackgroundImage(kPuzzleGeneralMenu, "Menu.bmp", Common::Point(0, 0), true);
	_app->puzzleAdd(kPuzzleSave);
	_app->puzzleAddBackgroundImage(kPuzzleSave, "Save.bmp", Common::Point(0, 0), true);
	_app->puzzleAdd(kPuzzleLoad);
	_app->puzzleAddBackgroundImage(kPuzzleLoad, "Load.bmp", Common::Point(0, 0), true);
	_app->puzzleAdd(kPuzzleStatus);
	_app->puzzleAddBackgroundImage(kPuzzleStatus, "Status.bmp", Common::Point(0, 0), true);
	_app->puzzleAdd(kPuzzlePreferences);
	_app->puzzleAddBackgroundImage(kPuzzlePreferences, "Preferences.bmp", Common::Point(0, 0), true);
	_app->objectAdd(kObjectYesNo, "", "", 1);
	_app->objectAddPresentation(kObjectYesNo);
	_app->objectPresentationAddImageToPuzzle(kObjectYesNo, 0, kPuzzleMenu, "Exit.bmp", Common::Point(160, 165), true, kDrawType1, 2000);
	_app->objectAddPuzzleAccessibility(kObjectYesNo, kPuzzleMenu, Common::Rect(240, 255, 290, 305), false, kCursorMenuActive, 1);
	_app->objectAddPuzzleAccessibility(kObjectYesNo, kPuzzleMenu, Common::Rect(360, 255, 410, 305), false, kCursorMenuActive, 0);
	_app->objectSetPuzzleAccessibilityKey(kObjectYesNo, 0, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObjectYesNo, 1, Common::KEYCODE_ESCAPE);
	_app->objectAddPresentation(kObjectYesNo);
	_app->objectPresentationAddImageToPuzzle(kObjectYesNo, 1, kPuzzleMenu, "box_ok.bmp", Common::Point(240, 255), true, kDrawType1, 2000);
	_app->objectAddPresentation(kObjectYesNo);
	_app->objectPresentationAddImageToPuzzle(kObjectYesNo, 2, kPuzzleMenu, "box_cancel.bmp", Common::Point(360, 255), true, kDrawType1, 2000);
	_app->objectAdd(kObject3, "", "", 1);
	_app->objectAddPresentation(kObject3);
	_app->objectPresentationAddImageToPuzzle(kObject3, 0, kPuzzleMenu, "Warning.bmp", Common::Point(160, 165), true, kDrawType1, 1000);
	_app->objectPresentationAddTextToPuzzle(kObject3, 0, kPuzzleMenu, "", Common::Point(200, 200), kFontDefault, Color(255, 95, 0), Color(-1, -1, -1));
	_app->objectPresentationAddTextToPuzzle(kObject3, 0, kPuzzleMenu, "", Common::Point(300, 280), kFontDefault, Color(255, 95, 0), Color(-1, -1, -1));
	_app->objectAddPresentation(kObject3);
	_app->objectPresentationAddImageToPuzzle(kObject3, 1, kPuzzleMenu, "box_ok.bmp", Common::Point(240, 255), true, kDrawType1, 1000);
	_app->objectAddPuzzleAccessibility(kObject3, kPuzzleMenu, Common::Rect(240, 255, 280, 295), false, kCursorMenuActive, 0);
	_app->objectSetPuzzleAccessibilityKey(kObject3, 0, Common::KEYCODE_RETURN);
	_app->objectAdd(kObjectQuestion, "", "", 1);
	_app->objectAddPresentation(kObjectQuestion);
	_app->objectPresentationAddImageToPuzzle(kObjectQuestion, 0, kPuzzleMenu, "Question.bmp", Common::Point(160, 165), true, kDrawType1, 1000);
	_app->objectPresentationAddTextToPuzzle(kObjectQuestion, 0, kPuzzleMenu, "", Common::Point(200, 200), kFontDefault, Color(255, 95, 0), Color(-1, -1, -1));
	_app->objectPresentationAddTextToPuzzle(kObjectQuestion, 0, kPuzzleMenu, "", Common::Point(200, 280), kFontDefault, Color(255, 95, 0), Color(-1, -1, -1));
	_app->objectAddPresentation(kObjectQuestion);
	_app->objectPresentationAddImageToPuzzle(kObjectQuestion, 1, kPuzzleMenu, "box_ok.bmp", Common::Point(240, 255), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectQuestion);
	_app->objectPresentationAddImageToPuzzle(kObjectQuestion, 2, kPuzzleMenu, "box_cancel.bmp", Common::Point(360, 255), true, kDrawType1, 1000);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(240, 255, 280, 295), false, kCursorMenuActive, 0);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(360, 255, 400, 295), false, kCursorMenuActive, 1);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 0, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 1, Common::KEYCODE_ESCAPE);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(180, 250, 250, 281), false, kCursorMenuActive, 2);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(180, 283, 250, 309), false, kCursorMenuActive, 3);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 2, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 3, Common::KEYCODE_ESCAPE);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(240, 255, 280, 295), false, kCursorMenuActive, 4);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(360, 255, 400, 295), false, kCursorMenuActive, 5);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 4, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 5, Common::KEYCODE_ESCAPE);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(180, 250, 250, 281), false, kCursorMenuActive, 6);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(180, 283, 250, 309), false, kCursorMenuActive, 7);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 6, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 7, Common::KEYCODE_ESCAPE);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(240, 255, 280, 295), false, kCursorMenuActive, 8);
	_app->objectAddPuzzleAccessibility(kObjectQuestion, kPuzzleMenu, Common::Rect(360, 255, 400, 295), false, kCursorMenuActive, 9);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 8, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObjectQuestion, 9, Common::KEYCODE_ESCAPE);
	_app->objectAdd(kObject5, "", "", 1);
	_app->objectAddPresentation(kObject5);
	_app->objectPresentationAddImageToPuzzle(kObject5, 0, kPuzzleMenu, "play.bmp", Common::Point(160, 165), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject5);
	_app->objectPresentationAddImageToPuzzle(kObject5, 1, kPuzzleMenu, "play_cont.bmp", Common::Point(200, 200), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject5);
	_app->objectPresentationAddImageToPuzzle(kObject5, 2, kPuzzleMenu, "play_new.bmp", Common::Point(200, 250), true, kDrawType1, 1000);
	_app->objectAddPuzzleAccessibility(kObject5, kPuzzleMenu, Common::Rect(200, 200, 440, 240), false, kCursorMenuActive, 0);
	_app->objectAddPuzzleAccessibility(kObject5, kPuzzleMenu, Common::Rect(200, 250, 440, 290), false, kCursorMenuActive, 1);
	_app->objectSetPuzzleAccessibilityKey(kObject5, 0, Common::KEYCODE_RETURN);
	_app->puzzleAdd(kPuzzleInsertCd);
	_app->puzzleAddBackgroundImage(kPuzzleInsertCd, "insertcd.bmp", Common::Point(0, 0), true);
	_app->objectAdd(kObject16, "", "", 1);
	_app->objectAddPresentation(kObject16);
	_app->objectPresentationAddTextToPuzzle(kObject16, 0, kPuzzleInsertCd, "", Common::Point(320, 240), kFontDefault, Color(255, 95, 0), Color(-1, -1, -1));
	_app->objectPresentationAddTextToPuzzle(kObject16, 0, kPuzzleInsertCd, "", Common::Point(320, 260), kFontDefault, Color(255, 95, 0), Color(-1, -1, -1));
	_app->objectAddPresentation(kObject16);
	_app->objectPresentationAddImageToPuzzle(kObject16, 1, kPuzzleInsertCd, "box_ok.bmp", Common::Point(240, 255), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject16);
	_app->objectPresentationAddImageToPuzzle(kObject16, 2, kPuzzleInsertCd, "box_cancel.bmp", Common::Point(360, 255), true, kDrawType1, 1000);
	_app->objectAddPuzzleAccessibility(kObject16, kPuzzleInsertCd, Common::Rect(240, 255, 280, 295), true, kCursorMenuActive, 2);
	_app->objectAddPuzzleAccessibility(kObject16, kPuzzleInsertCd, Common::Rect(360, 255, 400, 295), true, kCursorMenuActive, 1);
	_app->objectAddPuzzleAccessibility(kObject16, kPuzzleInsertCd, Common::Rect(240, 255, 280, 295), false, kCursorMenuActive, 3);
	_app->objectSetPuzzleAccessibilityKey(kObject16, 0, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObject16, 1, Common::KEYCODE_ESCAPE);
	_app->objectAdd(kObject99000, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99000, kPuzzleGeneralMenu, Common::Rect(250, 35, 600, 65), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99000);
	_app->objectPresentationAddImageToPuzzle(kObject99000, 0, kPuzzleGeneralMenu, "men1_h.bmp", Common::Point(230, 25), true, kDrawType1, 2000);
	_app->objectAdd(kObject99001, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99001, kPuzzleGeneralMenu, Common::Rect(250, 85, 600, 115), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99001);
	_app->objectPresentationAddImageToPuzzle(kObject99001, 0, kPuzzleGeneralMenu, "men2_h.bmp", Common::Point(230, 75), true, kDrawType1, 2000);
	_app->objectAdd(kObject99002, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99002, kPuzzleGeneralMenu, Common::Rect(250, 135, 600, 165), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99002);
	_app->objectPresentationAddImageToPuzzle(kObject99002, 0, kPuzzleGeneralMenu, "men3_h.bmp", Common::Point(230, 125), true, kDrawType1, 2000);
	_app->objectAdd(kObject99003, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99003, kPuzzleGeneralMenu, Common::Rect(250, 185, 600, 215), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99003);
	_app->objectPresentationAddImageToPuzzle(kObject99003, 0, kPuzzleGeneralMenu, "men4_h.bmp", Common::Point(230, 175), true, kDrawType1, 2000);
	_app->objectAdd(kObject99004, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99004, kPuzzleGeneralMenu, Common::Rect(250, 235, 600, 265), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99004);
	_app->objectPresentationAddImageToPuzzle(kObject99004, 0, kPuzzleGeneralMenu, "men5_h.bmp", Common::Point(230, 225), true, kDrawType1, 2000);
	_app->objectAdd(kObject99005, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99005, kPuzzleGeneralMenu, Common::Rect(250, 285, 600, 315), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99005);
	_app->objectPresentationAddImageToPuzzle(kObject99005, 0, kPuzzleGeneralMenu, "men6_h.bmp", Common::Point(230, 275), true, kDrawType1, 2000);
	_app->objectAdd(kObject99006, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99006, kPuzzleGeneralMenu, Common::Rect(250, 335, 600, 365), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99006);
	_app->objectPresentationAddImageToPuzzle(kObject99006, 0, kPuzzleGeneralMenu, "men7_h.bmp", Common::Point(230, 325), true, kDrawType1, 2000);
	_app->objectAdd(kObject99007, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99007, kPuzzleGeneralMenu, Common::Rect(250, 420, 600, 450), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99007);
	_app->objectPresentationAddImageToPuzzle(kObject99007, 0, kPuzzleGeneralMenu, "men8_h.bmp", Common::Point(463, 408), true, kDrawType1, 2000);
	_app->objectSetPuzzleAccessibilityKey(kObject99007, 0, Common::KEYCODE_ESCAPE);
	_app->objectAdd(kObject99022, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99022, kPuzzleLoad, Common::Rect(505, 410, 535, 440), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99022);
	_app->objectPresentationAddImageToPuzzle(kObject99022, 0, kPuzzleLoad, "cancel_h.bmp", Common::Point(505, 400), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject99022, 0, Common::KEYCODE_ESCAPE);
	_app->objectAdd(kObject99023, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99023, kPuzzleLoad, Common::Rect(390, 410, 420, 440), false, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99023);
	_app->objectPresentationAddImageToPuzzle(kObject99023, 0, kPuzzleLoad, "ok_h.bmp", Common::Point(390, 400), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject99023, 0, Common::KEYCODE_RETURN);
	_app->objectAddPresentation(kObject99023);
	_app->objectPresentationAddImageToPuzzle(kObject99023, 1, kPuzzleLoad, "ok_d.bmp", Common::Point(390, 400), true, kDrawType1, 2400);
	_app->objectAdd(kObject99024, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99024, kPuzzleSave, Common::Rect(505, 410, 535, 440), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99024);
	_app->objectPresentationAddImageToPuzzle(kObject99024, 0, kPuzzleSave, "cancel_h.bmp", Common::Point(505, 400), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject99024, 0, Common::KEYCODE_ESCAPE);
	_app->objectAdd(kObject99025, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99025, kPuzzleSave, Common::Rect(390, 410, 420, 440), false, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99025);
	_app->objectPresentationAddImageToPuzzle(kObject99025, 0, kPuzzleSave, "ok_h.bmp", Common::Point(390, 400), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject99025, 0, Common::KEYCODE_RETURN);
	_app->objectAddPresentation(kObject99025);
	_app->objectPresentationAddImageToPuzzle(kObject99025, 1, kPuzzleSave, "ok_d.bmp", Common::Point(390, 400), true, kDrawType1, 2400);
	_app->objectAdd(kObject99041, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99041, kPuzzlePreferences, Common::Rect(505, 410, 535, 440), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99041);
	_app->objectPresentationAddImageToPuzzle(kObject99041, 0, kPuzzlePreferences, "cancel_h.bmp", Common::Point(505, 400), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject99041, 0, Common::KEYCODE_ESCAPE);
	_app->objectAdd(kObject99042, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99042, kPuzzlePreferences, Common::Rect(390, 410, 420, 440), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99042);
	_app->objectPresentationAddImageToPuzzle(kObject99042, 0, kPuzzlePreferences, "ok_h.bmp", Common::Point(390, 400), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject99042, 0, Common::KEYCODE_RETURN);
	_app->objectAdd(kObject99043, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99043, kPuzzlePreferences, Common::Rect(400, 345, 560, 380), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99043);
	_app->objectPresentationAddImageToPuzzle(kObject99043, 0, kPuzzlePreferences, "Pref_off.bmp", Common::Point(400, 345), true, kDrawType1, 2200);
	_app->objectAddPresentation(kObject99043);
	_app->objectPresentationAddImageToPuzzle(kObject99043, 1, kPuzzlePreferences, "Pref_on.bmp", Common::Point(400, 345), true, kDrawType1, 2200);
	_app->objectAdd(kObject99044, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject99044, kPuzzlePreferences, Common::Rect(400, 265, 560, 300), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject99044);
	_app->objectPresentationAddImageToPuzzle(kObject99044, 0, kPuzzlePreferences, "Pref_nor.bmp", Common::Point(400, 265), true, kDrawType1, 2200);
	_app->objectAddPresentation(kObject99044);
	_app->objectPresentationAddImageToPuzzle(kObject99044, 1, kPuzzlePreferences, "Pref_inv.bmp", Common::Point(400, 265), true, kDrawType1, 2300);
	_app->objectAdd(kObject99045, "", "adrag", 4);
	_app->objectSetActiveDrawCursor(kObject99045, Common::Point(14, 14), 0, kCursorTypeImage, 0, 0, kLoadFromCursor);
	_app->objectSetPassiveDrawCursor(kObject99045, Common::Point(14, 14), 0, kCursorTypeImage, 0, 0, kLoadFromCursor);
	_app->objectAddPuzzleAccessibility(kObject99045, kPuzzlePreferences, Common::Rect(350, 112, 622, 132), true, kCursorDragDrop, 0);
	_app->objectAddPresentation(kObject99045);
	_app->objectPresentationAddImageToPuzzle(kObject99045, 0, kPuzzlePreferences, "slider.tga", Common::Point(0, 112), true, kDrawType3, 2200);
	_app->objectAdd(kObject99046, "", "adrag", 4);
	_app->objectSetActiveDrawCursor(kObject99046, Common::Point(14, 14), 0, kCursorTypeImage, 0.0f, 0, kLoadFromCursor);
	_app->objectSetPassiveDrawCursor(kObject99046, Common::Point(14, 14), 0, kCursorTypeImage, 0.0f, 0, kLoadFromCursor);
	_app->objectAddPuzzleAccessibility(kObject99046, kPuzzlePreferences, Common::Rect(350, 192, 610, 212), true, kCursorDragDrop, 0);
	_app->objectAddPresentation(kObject99046);
	_app->objectPresentationAddImageToPuzzle(kObject99046, 0, kPuzzlePreferences, "slider.tga", Common::Point(0, 192), true, kDrawType3, 2200);
	_app->objectAdd(kObject90401, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject90401, kPuzzleStatus, Common::Rect(30, 405, 70, 445), true, kCursorMenuActive, 0);
	_app->objectAddPuzzleAccessibility(kObject90401, kPuzzleStatus, Common::Rect(30, 405, 70, 445), true, kCursorMenuActive, 0);
	_app->objectAddPresentation(kObject90401);
	_app->objectPresentationAddImageToPuzzle(kObject90401, 0, kPuzzleStatus, "cancsta_h.bmp", Common::Point(30, 405), true, kDrawType1, 2400);
	_app->objectSetPuzzleAccessibilityKey(kObject90401, 0, Common::KEYCODE_RETURN);
	_app->objectSetPuzzleAccessibilityKey(kObject90401, 1, Common::KEYCODE_ESCAPE);

	for (uint32 i = 1; i < 27; i++) {
		_app->objectAddPresentation(kObject90401);
		_app->objectPresentationAddImageToPuzzle(kObject90401, i, kPuzzleStatus, Common::String::format("stat.%04d.bmp", i), Common::Point(190, 120), true, kDrawType1, 2400);
	}

	_app->objectAdd(kObject99601, "", "", 1);
	_app->objectAddPresentation(kObject99601);
	_app->objectPresentationAddAnimationToPuzzle(kObject99601, 0, kPuzzleSave, "kybcur", kImageTypeBMP, Common::Point(0, 0), kDrawType1, 2300, 6, 12.5, 16);
	_app->objectPresentationSetAnimationCoordinatesOnPuzzle(99601, 0, Common::Point(192, 388));
	_app->objectAddPresentation(kObject99601);
	_app->objectPresentationAddTextToPuzzle(kObject99601, 1, kPuzzleSave, "", Common::Point(30, 437), kFontDefault, Color(248, 250, 36), Color(-1, -1, -1));
	_app->objectPresentationAddTextToPuzzle(kObject99601, 1, kPuzzleLoad, "", Common::Point(30, 437), kFontDefault, Color(248, 250, 36), Color(-1, -1, -1));

	_app->setArchiveType(kArchiveFile);
	_app->objectAddPresentation(kObject99601);
	_app->objectPresentationAddImageToPuzzle(kObject99601, 2, kPuzzleSave, "osc.bmp", Common::Point(320, 135), true, kDrawType1, 5000);

	if (_app->getConfiguration().artSY)
		_app->setArchiveType(kArchiveArt);

	_app->visualListAddToPuzzle(1, kPuzzleSave, 129,
								"", "", "", "", "ar_uph.tga", "", "ar_upn.tga", "", "ar_dnh.tga", "", "ar_dnn.tga", "", "",
								kDrawType3, Common::Point(0, 0), Common::Point(0, 0), 30, 75, 235, 20, 25, 0,
								Common::Point(280, 80), 270, 70, 40, 40, Common::Point(280, 400), 270, 390, 40, 40,
								Common::Point(0, 0), kImageTypeBMP, kDrawType1, 170, 300, 14, Color(248, 250, 36),
								Color(255, 255, 255), Color(-1, -1, -1), kFontDefault, _app->getConfiguration().artSY ? kArchiveArt : kArchiveFile);

	_app->visualListSetOff(1, kPuzzleSave);

	_app->visualListAddToPuzzle(4, kPuzzleLoad, 65,
								"", "", "", "", "ar_uph.tga", "", "ar_upn.tga", "", "ar_dnh.tga", "", "ar_dnn.tga", "", "",
								kDrawType3, Common::Point(0, 0), Common::Point(0, 0), 30, 75, 235, 20, 25, 0,
								Common::Point(280, 80), 270, 70, 40, 40, Common::Point(280, 400), 270, 390, 40, 40,
								Common::Point(326, 143), kImageTypeBMP, kDrawType1, 170, 300, 14, Color(248, 250, 36),
								Color(255, 255, 255), Color(-1, -1, -1), kFontDefault, _app->getConfiguration().artSY ? kArchiveArt : kArchiveFile);

	_app->visualListSetOff(4, kPuzzleLoad);

	_app->soundAdd(990015, kSoundTypeAmbientEffect, "00_TAK-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900001, kSoundTypeAmbientEffect, "00_CLO-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900002, kSoundTypeAmbientEffect, "00_CLO-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900003, kSoundTypeAmbientEffect, "00_CLO-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900004, kSoundTypeAmbientEffect, "00_CLO-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900005, kSoundTypeAmbientEffect, "00_CLO-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900006, kSoundTypeAmbientEffect, "00_OPE-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900007, kSoundTypeAmbientEffect, "00_OPE-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900008, kSoundTypeAmbientEffect, "00_OPE-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900009, kSoundTypeAmbientEffect, "00_OPE-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900010, kSoundTypeAmbientEffect, "05_TAK-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900011, kSoundTypeAmbientEffect, "05_TAK-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900012, kSoundTypeAmbientEffect, "05_TAK-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900013, kSoundTypeAmbientEffect, "05_OPE-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900014, kSoundTypeAmbientEffect, "05_CLO-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(900015, kSoundTypeAmbientEffect, "09_CUT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990001, kSoundTypeAmbientMusic,  "FS_FOO-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990002, kSoundTypeAmbientMusic,  "FS_FOO-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990003, kSoundTypeAmbientMusic,  "FS_FOO-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990004, kSoundTypeAmbientMusic,  "FS_FOO-4.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990011, kSoundTypeAmbientMusic,  "FS_FOO-5.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990012, kSoundTypeAmbientMusic,  "FS_FOO-6.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990013, kSoundTypeAmbientMusic,  "FS_FOO-7.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(990014, kSoundTypeAmbientMusic,  "FS_FOO-8.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(90802, kSoundTypeAmbientMusic, "00_LOW-1.WAs", kLoadFromDisk);
	_app->soundAdd(90801, kSoundTypeAmbientMusic, "bgr_mus.was", kLoadFromDisk); // Original has "was", but the file is actually "wac"
	_app->puzzleAddAmbientSound(kPuzzleGeneralMenu, 90801, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzleLoad, 90801, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzleSave, 90801, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzlePreferences, 90801, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzleStatus, 90801, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzleInsertCd, 90801, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzleEncyclopedia, 90801, 100, 0, 1, 1, 10);
	_app->soundAdd(90800, kSoundTypeDialog, "4114.wac", kLoadFromDisk);
	_app->soundAdd(99007, kSoundTypeDialog, "4125.wac", kLoadFromDisk);
	_app->soundAdd(99008, kSoundTypeDialog, "4126.wac", kLoadFromDisk);
	_app->soundAdd(99009, kSoundTypeDialog, "4127.wac", kLoadFromDisk);
	_app->varDefineByte(91201, 0);
	_app->varDefineByte(91202, 0);
	_app->varDefineByte(91203, 0);
	_app->varDefineByte(91204, 0);
	_app->varDefineByte(91205, 0);
	_app->varDefineByte(91206, 0);
	_app->varDefineByte(91207, 0);
	_app->varDefineByte(91208, 0);
	_app->varDefineByte(91209, 0);
	_app->varDefineByte(98001, 0);
	_app->varDefineByte(98002, 0);
	_app->varDefineByte(98003, 0);
	_app->varDefineByte(98004, 0);
	_app->varDefineByte(98005, 0);
	_app->varDefineByte(98006, 0);
	_app->varDefineByte(98007, 0);
	_app->varDefineByte(98008, 0);
	_app->varDefineByte(98009, 0);
	_app->varDefineByte(90001, 1);
	_app->varDefineByte(90002, 1);
	_app->varDefineByte(90003, 0);
	_app->varDefineByte(90004, 0);
	_app->varDefineByte(90005, 0);
	_app->varDefineByte(90006, 0);
	_app->varDefineByte(90007, 0);
	_app->varDefineByte(90101, 0);
	_app->varDefineByte(90102, 0);
	_app->varDefineByte(90103, 0);
	_app->varDefineByte(90104, 0);
	_app->varDefineByte(90105, 0);
	_app->varDefineByte(90106, 0);
	_app->varDefineByte(90107, 0);
	_app->varDefineByte(90108, 0);
	_app->varDefineByte(90109, 0);
	_app->varDefineByte(90110, 0);
	_app->varDefineByte(90111, 0);
	_app->varDefineByte(90112, 0);
	_app->varDefineByte(90113, 0);
	_app->varDefineByte(90201, 0);
	_app->varDefineByte(90202, 0);
	_app->varDefineByte(90203, 0);
	_app->varDefineByte(90204, 0);
	_app->varDefineByte(90205, 0);
	_app->varDefineByte(90206, 0);
	_app->varDefineByte(90207, 0);
	_app->varDefineByte(90208, 0);
	_app->varDefineByte(90209, 0);
	_app->varDefineByte(90210, 0);
	_app->varDefineByte(90211, 0);
	_app->varDefineByte(90212, 0);
	_app->varDefineByte(90213, 0);
	_app->varDefineByte(90214, 0);
	_app->varDefineByte(90215, 0);
	_app->varDefineByte(90216, 0);
	_app->varDefineByte(90301, 0);
	_app->varDefineByte(90302, 0);
	_app->varDefineByte(90303, 0);
	_app->varDefineByte(90304, 0);
	_app->varDefineByte(90305, 0);
	_app->varDefineByte(90306, 0);
	_app->varDefineByte(90307, 0);
	_app->varDefineByte(90308, 0);
	_app->varDefineByte(90309, 0);
	_app->varDefineByte(90310, 0);
	_app->varDefineByte(90311, 0);
	_app->varDefineByte(90401, 0);
	_app->varDefineByte(90402, 0);
	_app->varDefineByte(90403, 0);
	_app->varDefineByte(90404, 0);
	_app->varDefineByte(90405, 0);
	_app->varDefineByte(90406, 0);
	_app->varDefineByte(90407, 0);
	_app->varDefineByte(90408, 0);
	_app->varDefineByte(90409, 0);
	_app->varDefineByte(90410, 0);
	_app->varDefineByte(90411, 0);
	_app->varDefineByte(90412, 0);
	_app->varDefineByte(90413, 0);
	_app->varDefineByte(90414, 0);
	_app->varDefineByte(90415, 0);
	_app->varDefineByte(90416, 0);
	_app->varDefineByte(90417, 0);
	_app->varDefineByte(90418, 0);
	_app->varDefineByte(90419, 0);
	_app->varDefineByte(90420, 0);
	_app->varDefineByte(90421, 0);
	_app->varDefineByte(90905, 0);
	_app->varDefineByte(90903, 0);
	_app->varDefineByte(90904, 16);
	_app->varDefineByte(90508, 0);
	_app->varDefineByte(90509, 1);
	_app->varDefineWord(99501, 6);
	_app->varDefineWord(99502, 6);
	_app->varDefineDword(90026, 0);
	_app->varDefineDword(99027, 0);
	_app->visualAddEncyclopediaToPuzzle(5, kPuzzleEncyclopedia, "E001.out", _app->_configuration.artSY ? kArchiveArt :  kArchiveFile);
	_app->visualEncyclopediaSetParameters(5, kPuzzleEncyclopedia, Common::Point(20, 20), Common::Rect(50, 428, 50, 580), true);
	_app->visualAddBoxToPuzzle(6, 1, " ", kArchiveFile);
	_app->varDefineWord(99500, 0);
	_app->varDefineDword(99028, 10111);
	_app->varDefineByte(91300, 1);
}

void ZoneSystemPompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	error("[ZoneSystemPompeii::onButtonUp()] Not implemented");
}

void ZoneSystemPompeii::onSound(Id id, SoundType /*type*/, uint32 /*a3*/, bool /*process*/) {
	switch (id) {
	default:
		break;

	case 99007:
		_app->playMovie("CONCL_-2");
		_app->puzzleSetActive(kPuzzle99002);
		_app->soundPlay(99008);
		break;

	case 99008:
		_app->playMovie("CONCL_-3");
		_app->puzzleSetActive(kPuzzle99003);
		_app->soundPlay(99009);
		break;

	case 99009:
		_app->soundStop(90802, 1024);
		_app->playMovie("CONCL_-4");
		_app->playMovie("CONCL_-5");
		_app->showCredits();
		_app->exitToMenu(kMenuAction13);
		break;
	}
}

void ZoneSystemPompeii::onBag(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, DragControl *dragControl, byte type) {
	error("[ZoneSystemPompeii::onBag] Not implemented");
}

void ZoneSystemPompeii::onUpdateBag(const Common::Point &/*point*/) {
	if (_app->hasCurrentRotation())
		_app->varSetDword(99027, _app->getCurrentRotationId());

	_app->objectPresentationHide(kObject6, 6);
	_app->objectPresentationHide(kObject6, 7);
	_app->objectPresentationHide(kObject6, 8);
	_app->objectPresentationHide(kObject6, 9);
	_app->objectPresentationHide(kObject6, 10);
	_app->objectPresentationHide(kObject6, 11);
	_app->objectPresentationHide(kObject6, 12);
	_app->objectPresentationHide(kObject6, 13);
	_app->objectPresentationHide(kObject6, 14);
	_app->objectPresentationHide(kObject6, 15);
	_app->objectPresentationHide(kObject6, 16);
	_app->objectPresentationHide(kObject6, 17);
	_app->objectPresentationHide(kObject6, 18);
	_app->objectPresentationHide(kObjectYesNo, 2);
	_app->objectPresentationHide(kObjectYesNo, 1);
	_app->objectPresentationHide(kObjectQuestion, 1);
	_app->objectPresentationHide(kObjectQuestion, 2);
	_app->objectPresentationHide(kObject3, 1);
	_app->objectPresentationHide(kObject5, 1);
	_app->objectPresentationHide(kObject5, 2);
	_app->objectPresentationHide(kObject99000, 0);
	_app->objectPresentationHide(kObject99001, 0);
	_app->objectPresentationHide(kObject99002, 0);
	_app->objectPresentationHide(kObject99003, 0);
	_app->objectPresentationHide(kObject99004, 0);
	_app->objectPresentationHide(kObject99005, 0);
	_app->objectPresentationHide(kObject99006, 0);

	if (!_app->varGetByte(98008))
		_app->objectPresentationHide(kObject99007);

	_app->objectPresentationHide(kObject99023, 0);
	_app->objectPresentationHide(kObject99022, 0);
	_app->objectPresentationHide(kObject99025, 0);
	_app->objectPresentationHide(kObject99024, 0);
	_app->objectPresentationHide(kObject99042, 0);
	_app->objectPresentationHide(kObject99041, 0);
	_app->objectPresentationHide(kObject90401, 0);
	_app->objectPresentationHide(kObject16, 1);
	_app->objectPresentationHide(kObject16, 2);
}

void ZoneSystemPompeii::onBagClickedObject(ObjectId objectId) {
	switch (objectId) {
	default:
		break;

	case kObjectItemList:
	case kObjectItemListCompleted:
		_app->cursorDelete();
		_app->objectPresentationHide(kObjectItemList);
		_app->objectPresentationShow(kObjectItemList, 0);
		_app->objectSetAccessibilityOn(kObjectItemList);

		for (uint32 i = 1; i < 10; i++) {
			if (_app->varGetByte(91200 + i) > 0)
				_app->objectPresentationShow(kObjectItemList, i);
		}
		break;

	case kObjectAmulet:
		_app->cursorDelete();

		if (_app->soundIsPlayingType(kSoundTypeDialog))
			_app->onCall(777);
		break;
	}
}

void ZoneSystemPompeii::onUpdateBefore(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, const Common::Point &point) {
	error("[ZoneSystemPompeii::onUpdateBefore] Not implemented");
}

} // End of namespace Ring
