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

#include "ring/game/pompeii/pompeii_zone11.h"

#include "ring/game/pompeii/pompeii_application.h"
#include "ring/game/pompeii/pompeii_shared.h"

#include "ring/debug.h"
#include "ring/ring.h"
#include "ring/helpers.h"

using namespace PompeiiGame;

namespace Ring {

Zone11Pompeii::Zone11Pompeii(ApplicationPompeii *application) : _app(application) {
}

Zone11Pompeii::~Zone11Pompeii() {
	// Zero-out passed pointers
	_app = NULL;
}

void Zone11Pompeii::onInit() {
	_app->setCurrentZone(kZone11);

	_app->puzzleAdd(kPuzzle110111);
	_app->puzzleAddBackgroundImage(kPuzzle110111, "s10a01n01p01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle110221);
	_app->puzzleAddBackgroundImage(kPuzzle110221, "s10a02n02p01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle110222);
	_app->puzzleAddBackgroundImage(kPuzzle110222, "s10a02n02p02.bmp", Common::Point(0, 16), true);
	_app->rotationAdd(11011, "S10A01-1", 0, 2);
	_app->rotationAdd(11021, "S10A02-5", 0, 1);
	_app->rotationAdd(11022, "S10A02-4", 0, 5);
	_app->rotationAdd(11023, "S10A02-3", 0, 3);
	_app->rotationAdd(11024, "S10A02-2", 0, 0);
	_app->rotationAdd(11025, "S10A02-1", 0, 0);
	_app->rotationAddMovabilityToRotation(11011, 11025, "", Common::Rect(2950, -250, 3100, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11011, 0, 257.0f, 0.30000001f, 87.0f, 0.0f, 1, 257.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11021, 11022, "", Common::Rect(2110, -250, 2260, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11021, 0, 173.0f, 0.30000001f, 87.0f, 0.0f, 1, 173.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11021, 11023, "", Common::Rect(330, -250, 480, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11021, 1, 355.0f, 0.30000001f, 87.0f, 0.0f, 1, 355.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11022, 11021, "", Common::Rect(310, -250, 460, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11022, 0, 353.0f, 0.30000001f, 87.0f, 0.0f, 1, 353.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11022, 11024, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11022, 1, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11023, 11021, "", Common::Rect(2130, -250, 2280, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11023, 0, 175.0f, 0.30000001f, 87.0f, 0.0f, 1, 175.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11024, 11022, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11024, 0, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11024, 11025, "", Common::Rect(1280, -250, 1430, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11024, 1, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11025, 11011, "", Common::Rect(1150, -250, 1300, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11025, 0, 77.0f, 0.30000001f, 87.0f, 0.0f, 1, 77.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(11025, 11024, "", Common::Rect(3080, -250, 3230, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(11025, 1, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0f);
	_app->objectAdd(kObjectMuleTooth, "donkey's tooth", "atooth", 1);
	_app->objectAddRotationAccessibility(kObjectMuleTooth, 11022, Common::Rect(1214, 355, 1267, 422), false, kCursorTake, 0);
	_app->objectAdd(kObjectMuleToothPowder, "donkey's tooth powder", "powder", 1);
	_app->objectAddRotationAccessibility(kObjectMuleToothPowder, 11023, Common::Rect(3171, 413, 3480, 588), false, kCursorTake, 0);
	_app->objectAdd(kObjectFabricAndFlour, "fabric and flour", "aflour", 1);
	_app->objectAddRotationAccessibility(kObjectFabricAndFlour, 11023, Common::Rect(3171, 413, 3480, 588), false, kCursorTake, 0);
	_app->objectAdd(kObjectBread, "bread", "bread", 1);
	_app->objectAddRotationAccessibility(kObjectBread, 11022, Common::Rect(2155, 187, 2337, 343), false, kCursorAction, 0);
	_app->objectAdd(kObject11001, "", "", 1);
	_app->objectAddRotationAccessibility(kObject11001, 11011, Common::Rect(1968, -227, 2436, 353), true, kCursorMove, 0);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 0, 11011, 0);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 1, 11022, 0);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 2, 11022, 2);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 3, 11022, 3);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 4, 11022, 3);
	_app->objectAddPresentation(kObject11001);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 6, 11023, 0);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddImageToRotation(kObject11001, 7, 11023, 2);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddAnimationToRotation(kObject11001, 8, 11011, 1, 10, 12.5, 16);
	_app->objectPresentationAddAnimationToRotation(kObject11001, 8, 11023, 1, 10, 12.5, 16);
	_app->objectPresentationAddAnimationToPuzzle(kObject11001, 8, kPuzzle110111, "s10a01n01p01s01", kImageTypeBMP, Common::Point(452, 31), kDrawType1, 1000, 29, 12.5, 16);
	_app->objectPresentationSetAnimationOnRotation(11001, 8, 0, 100001);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddAnimationToRotation(kObject11001, 9, 11022, 1, 15, 12.5, 16);
	_app->objectPresentationSetAnimationOnRotation(11001, 9, 0, 100002);
	_app->objectPresentationAddAnimationToPuzzle(kObject11001, 9, kPuzzle110221, "s10a02n02p01s01", kImageTypeBMP, Common::Point(276, 144), kDrawType1, 1000, 29, 12.5f, 16);
	_app->objectPresentationSetAnimationOnPuzzle(11001, 9, 0, 100002);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddAnimationToRotation(kObject11001, 10, 11022, 4, 15, 12.5, 16);
	_app->objectPresentationAddAnimationToPuzzle(kObject11001, 10, kPuzzle110222, "s10a02n02p02s01", kImageTypeBMP, Common::Point(296, 37), kDrawType1, 1000, 29, 12.5f, 16);
	_app->objectPresentationSetAnimationOnRotation(11001, 10, 0, 100002);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationAddAnimationToPuzzle(kObject11001, 11, kPuzzle110111, "s10a01n01p01s02", kImageTypeBMP, Common::Point(42, 162), kDrawType1, 1000, 29, 12.5, 4);
	_app->objectPresentationSetAnimationOnPuzzle(11001, 11, 0, 100003);
	_app->objectAddPresentation(kObject11001);
	_app->objectPresentationShow(kObject11001, 12);
	_app->objectAdd(kObject11004, "", "", 1);
	_app->objectAddRotationAccessibility(kObject11004, 11023, Common::Rect(3306,  19, 3600, 147), false, kCursorActionObject, 0);
	_app->objectAddRotationAccessibility(kObject11004, 11023, Common::Rect(   0,  19,   22, 147), false, kCursorActionObject, 0);
	_app->objectAdd(kObject11005, "", "", 1);
	_app->objectAddRotationAccessibility(kObject11005, 11023, Common::Rect(  94, 147,  221, 250), false, kCursorAction, 0);
	_app->objectAdd(kObject11006, "", "", 1);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 1);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorIdle, 2);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorActionObject, 3);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 4);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 5);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 6);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 7);
	_app->objectAddRotationAccessibility(kObject11006, 11022, Common::Rect(3028,   5, 3130, 273), false, kCursorAction, 8);
	_app->objectAdd(kObject11002, "", "", 1);
	_app->objectAddRotationAccessibility(kObject11002, 11011, Common::Rect(3257, -10, 3410, 255), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject11002, 11011, Common::Rect(3257, -10, 3410, 255), false, kCursorAction, 1);
	_app->objectAddRotationAccessibility(kObject11002, 11011, Common::Rect(3257, -10, 3410, 255), false, kCursorIdle, 2);
	_app->soundAdd(100001, kSoundTypeAmbientEffect, "10_PUT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(100003, kSoundTypeAmbientEffect, "10_THR-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(100004, kSoundTypeAmbientEffect, "10_THR-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(100005, kSoundTypeAmbientEffect, "10_TAK-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(100006, kSoundTypeAmbientEffect, "10_TAK-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(2062,   kSoundTypeDialog,        "2062.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4053,   kSoundTypeDialog,        "4053.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4054,   kSoundTypeDialog,        "4054.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4055,   kSoundTypeDialog,        "4055.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4056,   kSoundTypeDialog,        "4056.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4057,   kSoundTypeDialog,        "4057.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4058,   kSoundTypeDialog,        "4058.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4059,   kSoundTypeDialog,        "4059.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4060,   kSoundTypeDialog,        "4060.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4061,   kSoundTypeDialog,        "4061.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4062,   kSoundTypeDialog,        "4062.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4063,   kSoundTypeDialog,        "4063.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4064,   kSoundTypeDialog,        "4064.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4065,   kSoundTypeDialog,        "4065.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4066,   kSoundTypeDialog,        "4066.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4067,   kSoundTypeDialog,        "4067.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4068,   kSoundTypeDialog,        "4068.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4069,   kSoundTypeDialog,        "4069.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(100002, kSoundTypeAmbientMusic,  "10_AMB-1.WAs", _app->getConfiguration().backgroundMusic.loadFrom);
	_app->rotationAddAmbientSound(11011, 100002, 80, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(11021, 100002, 80, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(11022, 100002, 85, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(11023, 100002, 75, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(11024, 100002, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(11025, 100002, 85, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle110111, 100002, 80, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle110221, 100002, 85, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle110222, 100002, 85, 0, 1, 1, 10);
	_app->varDefineByte(100001, 0);
}

void Zone11Pompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	error("[Zone11Pompeii::onButtonUp()] Not implemented");
}

} // End of namespace Ring
