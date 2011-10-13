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

#include "ring/game/pompeii/pompeii_zone3.h"

#include "ring/game/pompeii/pompeii_application.h"
#include "ring/game/pompeii/pompeii_shared.h"

#include "ring/debug.h"
#include "ring/ring.h"
#include "ring/helpers.h"

using namespace PompeiiGame;

namespace Ring {

Zone3Pompeii::Zone3Pompeii(ApplicationPompeii *application) : _app(application) {
	_hideBox = false;
}

Zone3Pompeii::~Zone3Pompeii() {
	// Zero-out passed pointers
	_app = NULL;
}

void Zone3Pompeii::onInit() {
	_app->setCurrentZone(kZone3);

	_app->puzzleAdd(kPuzzle10211);
	_app->puzzleAddBackgroundImage(kPuzzle10211, "s02a01n01p01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle10241);
	_app->puzzleAddBackgroundImage(kPuzzle10241, "s02a04n01p01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle10245);
	_app->puzzleAddBackgroundImage(kPuzzle10245, "s02a04n01p05.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle10246);
	_app->puzzleAddBackgroundImage(kPuzzle10246, "s02a04n01p06.bmp", Common::Point(0, 16), true);
	_app->rotationAdd(102112, "S02A01-1", 0, 10);
	_app->rotationSetCompressionBufferLength(102112, 1200000);
	_app->rotationAdd(10211, "S02A01-6", 0, 1);
	_app->rotationAdd(10212, "S02A01-5", 0, 1);
	_app->rotationAdd(10213, "S02A01-4", 0, 1);
	_app->rotationAdd(10214, "S02A01-3", 0, 1);
	_app->rotationAdd(10215, "S02A01-2", 0, 2);
	_app->rotationAdd(10221, "S02A02-1", 0, 1);
	_app->rotationAdd(10231, "S02A03-3", 0, 0);
	_app->rotationAdd(10232, "S02A03-2", 0, 0);
	_app->rotationAdd(10233, "S02A03-1", 0, 0);
	_app->rotationAdd(10241, "S02A04-3", 0, 4);
	_app->rotationSetCompressionBufferLength(10241, 1200000);
	_app->rotationAdd(10242, "S02A04-2", 0, 3);
	_app->rotationAdd(10243, "S02A04-1", 0, 2);
	_app->rotationAddMovabilityToRotation(10211, 10212, "", Common::Rect(585, -222, 1105, 343), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10211, 0, 34.0f, 0.30000001f, 87.0f, 0.0f, 1, 34.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10211, 10214, "", Common::Rect(3396, -180, 3600, 325), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10211, 1, 315.0f, 0.30000001f, 87.0f, 0.0f, 1, 315.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10211, 10214, "", Common::Rect(0, -180, 286, 325), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10211, 2, 315.0f, 0.30000001f, 87.0f, 0.0f, 1, 315.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10211, 10215, "", Common::Rect(2144, -292, 2554, 327), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10211, 3, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10212, 10211, "", Common::Rect(2308, -234, 2735, 329), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10212, 0, 214.0f, 0.30000001f, 87.0f, 0.0f, 1, 214.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10212, 10213, "", Common::Rect(3543, -254, 3600, 322), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10212, 1, 315.0f, 0.30000001f, 87.0f, 0.0f, 1, 315.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10212, 10213, "", Common::Rect(0, -254, 423, 322), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10212, 2, 315.0f, 0.30000001f, 87.0f, 0.0f, 1, 315.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10213, 10212, "", Common::Rect(1560, -182, 1991, 332), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10213, 0, 135.0f, 0.30000001f, 87.0f, 0.0f, 1, 135.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10213, 10214, "", Common::Rect(2487, -198, 2954, 311), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10213, 1, 236.0f, 0.30000001f, 87.0f, 0.0f, 1, 236.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10213, 10221, "", Common::Rect(196, -155, 638, 331), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10213, 2, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10214, 10211, "", Common::Rect(1745, -255, 2253, 306), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10214, 0, 135.0f, 0.30000001f, 87.0f, 0.0f, 1, 135.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10214, 10213, "", Common::Rect(423, -248, 889, 332), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10214, 1, 56.0f, 0.30000001f, 87.0f, 0.0f, 1, 56.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10215, 10211, "", Common::Rect(249, -166, 604, 299), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10215, 0, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10221, 10213, "", Common::Rect(1958, -178, 2517, 397), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10221, 0, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10221, 10233, "", Common::Rect(335, -120, 666, 299), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10221, 1, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10231, 10232, "", Common::Rect(1112, -185, 1622, 313), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10231, 0, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10231, 10243, "", Common::Rect(594, -191, 947, 322), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10231, 1, 31.0f, 0.30000001f, 87.0f, 0.0f, 1, 31.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10232, 10231, "", Common::Rect(2874, -183, 3362, 322), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10232, 0, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10232, 10233, "", Common::Rect(1161, -205, 1668, 294), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10232, 1, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10232, 10243, "", Common::Rect(254, -129, 711, 313), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10232, 2, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10233, 10221, "", Common::Rect(2116, -129, 2415, 327), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10233, 0, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10233, 10232, "", Common::Rect(2891, -199, 3369, 315), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10233, 1, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10241, 10242, "", Common::Rect(101, -155, 762, 399), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10241, 0, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10241, 10243, "", Common::Rect(2007, -159, 2605, 408), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10241, 1, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10242, 10241, "", Common::Rect(1996, -134, 2432, 318), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10242, 0, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10243, 10232, "", Common::Rect(2037, -208, 2499, 313), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10243, 0, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10243, 10241, "", Common::Rect(223, -166, 648, 320), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10243, 1, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->objectAdd(kObject10201, "", "", 1);
	_app->objectAddRotationAccessibility(kObject10201, 10215, Common::Rect(1977, -301, 2610, 282), true, kCursorMove, 0);
	_app->objectAdd(kObject10202, "", "", 1);
	_app->objectAddRotationAccessibility(kObject10202, 10242, Common::Rect(434, -92, 602, 154), true, kCursorMove, 0);
	_app->objectAddPresentation(kObject10202);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 0, 102112, 0, 15, 12.5f, 16);
	_app->objectAddPresentation(kObject10202);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 1, 102112, 1, 15, 12.5f, 4);
	_app->objectPresentationSetAnimationOnRotation(kObject10202, 1, 0, 20001);
	_app->objectAddPresentation(kObject10202);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 2, 102112, 4, 15, 12.5f, 16);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 2, 102112, 5, 15, 12.5f, 16);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 2, 102112, 6, 15, 12.5f, 16);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 2, 102112, 7, 15, 12.5f, 16);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 2, 102112, 8, 15, 12.5f, 16);
	_app->objectPresentationAddAnimationToRotation(kObject10202, 2, 102112, 9, 15, 12.5f, 16);
	_app->objectAdd(kObject20000, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20000, 102112, Common::Rect(26, 63, 135, 222), false, kCursorIdle, 0);
	_app->objectAddPresentation(kObject20000);
	_app->objectPresentationAddImageToPuzzle(kObject20000, 0, kPuzzle10246, "s02a04n01p06l01.bmp", Common::Point(121, 197), true, kDrawType1, 1000);
	_app->objectAdd(kObjectStones, "Stones", "stones", 1);
	_app->objectAddRotationAccessibility(kObjectStones, 10242, Common::Rect(555, 350, 731, 406), false, kCursorTake, 0);
	_app->objectAddPresentation(kObjectStones);
	_app->objectPresentationAddImageToRotation(kObjectStones, 0, 10242, 2);
	_app->objectAdd(kObject20001, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20001, 10241, Common::Rect(356, 17, 465, 315), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject20001, 10241, Common::Rect(356, 17, 465, 315), false, kCursorActionObject, 1);
	_app->objectAddRotationAccessibility(kObject20001, 10241, Common::Rect(356, 17, 465, 315), false, kCursorIdle, 2);
	_app->objectAddPresentation(kObject20001);
	_app->objectPresentationAddImageToRotation(kObject20001, 0, 10241, 0);
	_app->objectPresentationAddAnimationToRotation(kObject20001, 0, 10241, 1, 14, 12.5f, 4);
	_app->objectPresentationAddImageToRotation(kObject20001, 0, 10242, 0);
	_app->objectPresentationAddImageToRotation(kObject20001, 0, 10243, 0);
	_app->objectPresentationSetAnimationOnRotation(kObject20001, 0, 0, 20000);
	_app->objectAddPresentation(kObject20001);
	_app->objectPresentationAddAnimationToPuzzle(kObject20001, 1, kPuzzle10241, "s02a04n01p01s01", kImageTypeBMP, Common::Point(109, 111), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject20001, 1, 0, 20000);
	_app->objectAddPresentation(kObject20001);
	_app->objectPresentationAddAnimationToPuzzle(kObject20001, 2, kPuzzle10241, "s02a04n01p01s02", kImageTypeBMP, Common::Point(320, 48), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject20001, 2, 0, 20001);
	_app->objectAdd(kObject20002, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20002, 10241, Common::Rect(2097, -28, 2272, 261), false, kCursorActionObject, 0);
	_app->objectAddRotationAccessibility(kObject20002, 10241, Common::Rect(2097, -28, 2272, 261), false, kCursorIdle, 1);
	_app->objectAddPresentation(kObject20002);
	_app->objectPresentationAddImageToRotation(kObject20002, 0, 10241, 2);
	_app->objectPresentationAddAnimationToRotation(kObject20002, 0, 10241, 3, 20, 12.5f, 4);
	_app->objectPresentationAddImageToRotation(kObject20002, 0, 10242, 1);
	_app->objectPresentationAddImageToRotation(kObject20002, 0, 10243, 1);
	_app->objectPresentationSetAnimationOnRotation(kObject20002, 0, 0, 20000);
	_app->objectAddPresentation(kObject20002);
	_app->objectPresentationAddAnimationToPuzzle(kObject20002, 1, kPuzzle10245, "s02a04n01p05s01", kImageTypeBMP, Common::Point(485, 76), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject20002, 1, 0, 20000);
	_app->objectAddPresentation(kObject20002);
	_app->objectPresentationAddAnimationToPuzzle(kObject20002, 2, kPuzzle10245, "s02a04n01p05s02", kImageTypeBMP, Common::Point(44, 18), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject20002, 2, 0, 20001);
	_app->objectAdd(kObject20006, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20006, 10215, Common::Rect(344, -14, 509, 268), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject20006, 10215, Common::Rect(344, -14, 509, 268), false, kCursorIdle, 1);
	_app->objectAddPresentation(kObject20006);
	_app->objectPresentationAddImageToRotation(kObject20006, 0, 10211, 0);
	_app->objectPresentationAddImageToRotation(kObject20006, 0, 10212, 0);
	_app->objectPresentationAddImageToRotation(kObject20006, 0, 10213, 0);
	_app->objectPresentationAddImageToRotation(kObject20006, 0, 10214, 0);
	_app->objectPresentationAddImageToRotation(kObject20006, 0, 10215, 0);
	_app->objectPresentationAddAnimationToRotation(kObject20006, 0, 10215, 1, 15, 12.5f, 4);
	_app->objectPresentationSetAnimationOnRotation(kObject20006, 0, 0, 20000);
	_app->objectAdd(kObject20007, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20007, 10241, Common::Rect(356, 17, 465, 315), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject20007, 10241, Common::Rect(356, 17, 465, 315), false, kCursorIdle, 1);
	_app->objectAddPresentation(kObject20007);
	_app->objectPresentationAddImageToRotation(kObject20007, 0, 10241, 0);
	_app->objectPresentationAddAnimationToRotation(kObject20007, 0, 10241, 1, 14, 12.5f, 4);
	_app->objectPresentationAddImageToRotation(kObject20007, 0, 10242, 0);
	_app->objectPresentationAddImageToRotation(kObject20007, 0, 10243, 0);
	_app->objectPresentationSetAnimationOnRotation(kObject20007, 0, 0, 20000);
	_app->objectAddPresentation(kObject20007);
	_app->objectPresentationAddAnimationToPuzzle(kObject20007, 1, kPuzzle10241, "s02a04n01p01s01", kImageTypeBMP, Common::Point(109, 111), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject20007, 1, 0, 20000);
	_app->objectAddPresentation(kObject20007);
	_app->objectPresentationAddAnimationToPuzzle(kObject20007, 2, kPuzzle10241, "s02a04n01p01s02", kImageTypeBMP, Common::Point(320, 48), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject20007, 2, 0, 20001);
	_app->objectAdd(kObject20009, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20009, 10241, Common::Rect(330, 438, 478, 539), false, kCursorActionObject, 0);
	_app->objectAdd(kObject20010, "", "", 1);
	_app->objectAddRotationAccessibility(kObject20010, 10241, Common::Rect(1233, 262, 1624, 375), false, kCursorActionObject, 0);
	_app->soundAdd(20042, kSoundTypeAmbientEffect, "02_AMB-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(20043, kSoundTypeAmbientEffect, "02_TAK-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(20044, kSoundTypeAmbientEffect, "02_TAK-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(20045, kSoundTypeAmbientEffect, "02_PUT-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(20046, kSoundTypeAmbientEffect, "02_PUT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(20047, kSoundTypeAmbientEffect, "02_PUT-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(20048, kSoundTypeAmbientEffect, "05_THR-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(1091, kSoundTypeDialog, "1091.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1092, kSoundTypeDialog, "1092.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1093, kSoundTypeDialog, "1093.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1094, kSoundTypeDialog, "1094.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1096, kSoundTypeDialog, "1096.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2077, kSoundTypeDialog, "2077.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2078, kSoundTypeDialog, "2078.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2079, kSoundTypeDialog, "2079.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2080, kSoundTypeDialog, "2080.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2081, kSoundTypeDialog, "2081.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2082, kSoundTypeDialog, "2082.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2083, kSoundTypeDialog, "2083.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2084, kSoundTypeDialog, "2084.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2085, kSoundTypeDialog, "2085.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2086, kSoundTypeDialog, "2086.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2087, kSoundTypeDialog, "2087.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2088, kSoundTypeDialog, "2088.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2089, kSoundTypeDialog, "2089.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2090, kSoundTypeDialog, "2090.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2091, kSoundTypeDialog, "2091.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2092, kSoundTypeDialog, "2092.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2093, kSoundTypeDialog, "2093.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2094, kSoundTypeDialog, "2094.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2095, kSoundTypeDialog, "2095.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3057, kSoundTypeDialog, "3057.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3058, kSoundTypeDialog, "3058.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3059, kSoundTypeDialog, "3059.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3060, kSoundTypeDialog, "3060.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3061, kSoundTypeDialog, "3061.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3062, kSoundTypeDialog, "3062.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3063, kSoundTypeDialog, "3063.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3064, kSoundTypeDialog, "3064.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3065, kSoundTypeDialog, "3065.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3066, kSoundTypeDialog, "3066.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3067, kSoundTypeDialog, "3067.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3068, kSoundTypeDialog, "3068.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3069, kSoundTypeDialog, "3069.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3070, kSoundTypeDialog, "3070.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3071, kSoundTypeDialog, "3071.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3072, kSoundTypeDialog, "3072.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3073, kSoundTypeDialog, "3073.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3074, kSoundTypeDialog, "3074.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(20041, kSoundTypeAmbientMusic, "BGR_MU-1.WAc", _app->getConfiguration().backgroundMusic.loadFrom);
	_app->soundSetVolume(20041, 95);
	_app->soundAdd(102001, kSoundTypeAmbientMusic, "BGR_MU-2.WAc", _app->getConfiguration().backgroundMusic.loadFrom);
	_app->rotationAddAmbientSound(10211, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10212, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10213, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10214, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10215, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10221, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10231, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10232, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10233, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10241, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10242, 102001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10243, 102001, 90, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle10211, 102001, 90, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle10241, 102001, 90, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle10245, 102001, 90, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle10246, 102001, 90, 0, 1, 1, 10);
	_app->varDefineByte(20000, 0);
	_app->varDefineByte(20001, 0);
	_app->varDefineByte(20002, 0);
	_app->varDefineByte(20003, 0);
	_app->varDefineByte(20004, 0);
	_app->varDefineByte(20005, 0);
	_app->varDefineByte(20006, 0);
	_app->varDefineByte(20007, 0);
	_app->varDefineByte(20008, 0);
	_app->varDefineByte(20009, 0);
	_app->varDefineByte(20010, 0);
}

void Zone3Pompeii::onSetup(SetupType type) {
	switch (type) {
	default:
		break;

	case kSetupTypeNone:
		_app->setSpace(kZone100);
		_app->soundPlay(90802, kSoundLoop);
		_app->objectPresentationShow(kObject99009);
		_app->playMovie("CONCL_-1");
		_app->puzzleSetActive(kPuzzle99001);
		_app->soundPlay(99007);
		break;
	}
}

void Zone3Pompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	error("[Zone3Pompeii::onButtonUp] Not implemented");
}

void Zone3Pompeii::onTimer(TimerId id) {
	switch (id) {
	default:
		break;

	case kTimer0:
		_app->timerStop(kTimer0);
		_app->rotationSetRolTo(102112, 290.0, 12.0, 87.0);
		_app->objectPresentationShow(kObject10202, 1);
		_app->soundPlay(1091);
		break;

	case kTimer1:
		_app->timerStop(kTimer1);
		_app->objectPresentationUnpauseAnimation(kObject20001, 0);
		_app->objectPresentationUnpauseAnimation(kObject20001, 1);
		_app->objectPresentationUnpauseAnimation(kObject20002, 0);
		_app->objectPresentationUnpauseAnimation(kObject20002, 1);
		_app->objectPresentationUnpauseAnimation(kObject20006, 0);
		_app->objectPresentationUnpauseAnimation(kObject20007, 0);
		_app->objectPresentationUnpauseAnimation(kObject20007, 1);
		break;

	case kTimer2:
		_app->timerStop(kTimer2);
		_app->objectPresentationUnpauseAnimation(kObject20001, 2);
		_app->objectPresentationUnpauseAnimation(kObject20002, 2);
		_app->objectPresentationUnpauseAnimation(kObject20007, 2);
		_app->objectPresentationUnpauseAnimation(kObject10202, 1);
		break;
	}
}

void Zone3Pompeii::onAnimationNextFrame(Id animationId, const Common::String &name, uint32 frame, uint32 frameCount) {
	error("[Zone3Pompeii::onAnimationNextFrame] Not implemented");
}

void Zone3Pompeii::onSound(Id id, SoundType type, uint32 a3, bool process) {
	error("[Zone3Pompeii::onSound] Not implemented");
}

void Zone3Pompeii::onUpdateBag(const Common::Point &point) {
	if (_hideBox) {
		_app->visualBoxHide(6, kPuzzleMenu);
		_hideBox = false;
	}
}

void Zone3Pompeii::onBagClickedObject(ObjectId objectId) {
	error("[Zone3Pompeii::onBagClickedObject] Not implemented");
}

void Zone3Pompeii::onUpdateBefore(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, const Common::Point &point) {
	error("[Zone3Pompeii::onUpdateBefore] Not implemented");
}

void Zone3Pompeii::onUpdateAfter(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType, const Common::Point &point) {
	if (_hideBox) {
		_app->visualBoxHide(6, kPuzzleMenu);
		_hideBox = false;
	}
}

void Zone3Pompeii::onVisualList(Id id, uint32 type, const Common::Point &point) {
	error("[Zone3Pompeii::onVisualList] Not implemented");
}

} // End of namespace Ring
