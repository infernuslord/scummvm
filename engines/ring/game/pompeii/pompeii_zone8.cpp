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

#include "ring/game/pompeii/pompeii_zone8.h"

#include "ring/game/pompeii/pompeii_application.h"
#include "ring/game/pompeii/pompeii_shared.h"

#include "ring/debug.h"
#include "ring/ring.h"
#include "ring/helpers.h"

using namespace PompeiiGame;

namespace Ring {

Zone8Pompeii::Zone8Pompeii(ApplicationPompeii *application) : _app(application) {
	_hideBox = false;
}

Zone8Pompeii::~Zone8Pompeii() {
	// Zero-out passed pointers
	_app = NULL;
}

void Zone8Pompeii::onInit() {
	_app->setCurrentZone(kZone8);

	_app->puzzleAdd(kPuzzle70121);
	_app->puzzleAddBackgroundImage(kPuzzle70121, "S07A01N01P01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle70211);
	_app->puzzleAddBackgroundImage(kPuzzle70211, "S07A02N01P01.bmp", Common::Point(0, 16), true);
	_app->rotationAdd(10711, "S07A01-5", 0, 2);
	_app->rotationAdd(10712, "S07A01-4", 0, 0);
	_app->rotationAdd(10713, "S07A01-3", 0, 0);
	_app->rotationAdd(10714, "S07A01-2", 0, 0);
	_app->rotationAdd(10715, "S07A01-1", 0, 0);
	_app->rotationAdd(10721, "S07A02-1", 0, 6);
	_app->rotationAddMovabilityToRotation(10711, 10712, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10711, 0, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10711, 10713, "", Common::Rect(3080, -250, 3230, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10711, 1, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10712, 10711, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10712, 0, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10712, 10714, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10712, 1, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10712, 10715, "", Common::Rect(30, -250, 180, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10712, 2, 325.0f, 0.30000001f, 87.0f, 0.0f, 1, 325.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10713, 10711, "", Common::Rect(1280, -250, 1430, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10713, 0, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10714, 10712, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10714, 0, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10714, 10715, "", Common::Rect(3080, -250, 3230, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10714, 1, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10714, 10721, "", Common::Rect(3590, -250, 3600, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10714, 2, 321.0f, 0.30000001f, 87.0f, 0.0f, 1, 321.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10714, 10721, "", Common::Rect(0, -250, 140, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10714, 3, 321.0f, 0.30000001f, 87.0f, 0.0f, 1, 321.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10715, 10712, "", Common::Rect(1830, -250, 1980, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10715, 0, 145.0f, 0.30000001f, 87.0f, 0.0f, 1, 145.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10715, 10714, "", Common::Rect(1280, -250, 1430, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10715, 1, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10715, 10721, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10715, 2, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10721, 10714, "", Common::Rect(1790, -250, 1940, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10721, 0, 141.0f, 0.30000001f, 87.0f, 0.0f, 1, 141.0f, 0.30000001f, 87.0);
	_app->rotationAddMovabilityToRotation(10721, 10715, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10721, 1, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0);
	_app->objectAdd(kObjectPapyrus, "papyrus", "apyrus", 1);
	_app->objectAdd(kObjectIbisFeather, "ibis' feather", "ather1", 1);
	_app->objectAddRotationAccessibility(kObjectIbisFeather, 10721, Common::Rect(3422, 126, 3487, 168), false, kCursorTake, 0);
	_app->objectAdd(kObjectSylphium, "sylphium", "lphium", 1);
	_app->objectAddRotationAccessibility(kObjectSylphium, 10721, Common::Rect(3331, 115, 3387, 173), false, kCursorTake, 0);
	_app->objectAdd(kObject10701, "", "", 1);
	_app->objectAddRotationAccessibility(kObject10701, 10711, Common::Rect(1030, -269, 1441, 247), true, kCursorMove, 0);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 0, 10711, 0);
	_app->objectPresentationAddAnimationToRotation(kObject10701, 0, 10711, 1, 15, 12.5, 16);
	_app->objectPresentationSetAnimationOnRotation(10701, 0, 0, 70001);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 1, 10721, 0);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 2, 10721, 1);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 3, 10721, 2);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 4, 10721, 3);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 5, 10721, 4);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddImageToRotation(kObject10701, 6, 10721, 5);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddAnimationToPuzzle(kObject10701, 7, kPuzzle70121, "s07a01n01p01s01", kImageTypeBMP, Common::Point(82, 67), kDrawType1, 1000, 30, 12.5, 4);
	_app->objectPresentationSetAnimationOnPuzzle(10701, 7, 0, 70001);
	_app->objectAddPresentation(kObject10701);
	_app->objectPresentationAddAnimationToPuzzle(kObject10701, 8, kPuzzle70211, "s07a02n01p01s01", kImageTypeBMP, Common::Point(390, 116), kDrawType1, 1000, 29, 12.5, 4);
	_app->objectPresentationSetAnimationOnPuzzle(10701, 8, 0, 70001);
	_app->objectAdd(kObject70701, "", "", 1);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorIdle, 1);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorActionObject, 2);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorAction, 3);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorIdle, 4);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorActionObject, 5);
	_app->objectAddRotationAccessibility(kObject70701, 10711, Common::Rect(3359, -7, 3480, 266), false, kCursorIdle, 6);
	_app->objectAdd(kObject70702, "", "", 1);
	_app->objectAddRotationAccessibility(kObject70702, 10721, Common::Rect(2796, 33, 2930, 176), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject70702, 10721, Common::Rect(2796, 33, 2930, 176), false, kCursorAction, 1);
	_app->objectAdd(kObject70703, "", "", 1);
	_app->objectAddRotationAccessibility(kObject70703, 10721, Common::Rect(3295, 38, 3450, 176), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject70703, 10721, Common::Rect(3100, 40, 3255, 180), false, kCursorAction, 1);
	_app->soundAdd(70001, kSoundTypeAmbientEffect, "07_TAK-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(70002, kSoundTypeAmbientEffect, "07_MOV-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(70003, kSoundTypeAmbientEffect, "07_BRE-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(70004, kSoundTypeAmbientEffect, "07_GIV-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(2056,  kSoundTypeDialog,        "2056.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2057,  kSoundTypeDialog,        "2057.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2058,  kSoundTypeDialog,        "2058.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2059,  kSoundTypeDialog,        "2059.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2060,  kSoundTypeDialog,        "2060.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2061,  kSoundTypeDialog,        "2061.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4083,  kSoundTypeDialog,        "4083.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4084,  kSoundTypeDialog,        "4084.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4085,  kSoundTypeDialog,        "4085.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4086,  kSoundTypeDialog,        "4086.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4087,  kSoundTypeDialog,        "4087.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4088,  kSoundTypeDialog,        "4088.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4089,  kSoundTypeDialog,        "4089.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4090,  kSoundTypeDialog,        "4090.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4091,  kSoundTypeDialog,        "4091.wac",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(77001, kSoundTypeAmbientMusic, "BGR_MU-1.WAc",  _app->getConfiguration().backgroundMusic.loadFrom);
	_app->rotationAddAmbientSound(10711, 77001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10712, 77001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10713, 77001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10714, 77001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10715, 77001, 90, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10721, 77001, 90, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle70121, 77001, 90, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle70211, 77001, 90, 0, 1, 1, 10);
	_app->varDefineByte(70001, 0);
}

void Zone8Pompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	error("[Zone8Pompeii::onButtonUp()] Not implemented");
}

void Zone8Pompeii::onTimer(TimerId id) {
	error("[Zone8Pompeii::onTimer] Not implemented");
}

void Zone8Pompeii::onAnimationNextFrame(Id animationId, const Common::String &name, uint32 frame, uint32 frameCount) {
	error("[Zone8Pompeii::onAnimationNextFrame] Not implemented");
}

void Zone8Pompeii::onSound(Id id, SoundType type, uint32 a3, bool process) {
	error("[Zone8Pompeii::onSound] Not implemented");
}

void Zone8Pompeii::onUpdateBag(const Common::Point &point) {
	if (_hideBox) {
		_app->visualBoxHide(6, kPuzzleMenu);
		_hideBox = false;
	}
}

void Zone8Pompeii::onUpdateBefore(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, const Common::Point &point) {
	error("[Zone8Pompeii::onUpdateBefore] Not implemented");
}

void Zone8Pompeii::onUpdateAfter(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType, const Common::Point &point) {
	if (_hideBox) {
		_app->visualBoxHide(6, kPuzzleMenu);
		_hideBox = false;
	}
}

void Zone8Pompeii::onVisualList(Id id, uint32 type, const Common::Point &point) {
	error("[Zone8Pompeii::onVisualList] Not implemented");
}

} // End of namespace Ring