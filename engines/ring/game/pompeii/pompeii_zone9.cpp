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

#include "ring/game/pompeii/pompeii_zone9.h"

#include "ring/game/pompeii/pompeii_application.h"
#include "ring/game/pompeii/pompeii_shared.h"

#include "ring/debug.h"
#include "ring/ring.h"
#include "ring/helpers.h"

using namespace PompeiiGame;

namespace Ring {

Zone9Pompeii::Zone9Pompeii(ApplicationPompeii *application) : _app(application) {
}

Zone9Pompeii::~Zone9Pompeii() {
	// Zero-out passed pointers
	_app = NULL;
}

void Zone9Pompeii::onInit() {
	_app->setCurrentZone(kZone9);

	_app->rotationAdd(10811, "S08A01-6", 0, 2);
	_app->rotationAdd(10812, "S08A01-5", 0, 4);
	_app->rotationAdd(10813, "S08A01-4", 0, 1);
	_app->rotationAdd(10814, "S08A01-3", 0, 1);
	_app->rotationAdd(10815, "S08A01-2", 0, 1);
	_app->rotationAdd(10816, "S08A01-1", 0, 1);
	_app->rotationAddMovabilityToRotation(10811, 10813, "", Common::Rect(1280, -250, 1430, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10811, 0, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10811, 10814, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10811, 1, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10811, 10815, "", Common::Rect(3080, -250, 3230, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10811, 2, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10811, 10816, "", Common::Rect(2830, -250, 2980, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10811, 3, 245.0f, 0.30000001f, 87.0f, 0.0f, 1, 245.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10812, 10816, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10812, 0, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10813, 10811, "", Common::Rect(3080, -250, 3230, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10813, 0, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10813, 10814, "", Common::Rect(2830, -250, 2980, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10813, 1, 245.0f, 0.30000001f, 87.0f, 0.0f, 1, 245.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10814, 10811, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10814, 0, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10814, 10813, "", Common::Rect(1030, -250, 1180, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10814, 1, 65.0f, 0.30000001f, 87.0f, 0.0f, 1, 65.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10814, 10815, "", Common::Rect(3330, -250, 3480, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10814, 2, 295.0f, 0.30000001f, 87.0f, 0.0f, 1, 295.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10814, 10816, "", Common::Rect(3080, -250, 3230, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10814, 3, 270.0f, 0.30000001f, 87.0f, 0.0f, 1, 270.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10815, 10811, "", Common::Rect(1280, -250, 1430, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10815, 0, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10815, 10814, "", Common::Rect(1530, -250, 1680, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10815, 1, 115.0f, 0.30000001f, 87.0f, 0.0f, 1, 115.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10815, 10816, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10815, 2, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10816, 10811, "", Common::Rect(1030, -250, 1180, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10816, 0, 65.0f, 0.30000001f, 87.0f, 0.0f, 1, 65.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10816, 10812, "", Common::Rect(2180, -250, 2330, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10816, 1, 180.0f, 0.30000001f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10816, 10814, "", Common::Rect(1280, -250, 1430, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10816, 2, 90.0f, 0.30000001f, 87.0f, 0.0f, 1, 90.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10816, 10815, "", Common::Rect(380, -250, 530, 250), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10816, 3, 0.0f, 0.30000001f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->objectAdd(kObject10801, "", "", 1);
	_app->objectAddRotationAccessibility(kObject10801, 10811, Common::Rect(286, -171, 476, 99), true, kCursorMove, 0);
	_app->objectAddPresentation(kObject10801);
	_app->objectPresentationAddImageToRotation(kObject10801, 0, 10811, 0);
	_app->objectPresentationAddImageToRotation(kObject10801, 0, 10812, 3);
	_app->objectPresentationAddImageToRotation(kObject10801, 0, 10813, 0);
	_app->objectPresentationAddImageToRotation(kObject10801, 0, 10814, 0);
	_app->objectPresentationAddImageToRotation(kObject10801, 0, 10815, 0);
	_app->objectPresentationAddImageToRotation(kObject10801, 0, 10816, 0);
	_app->objectPresentationAddAnimationToRotation(kObject10801, 0, 10811, 1, 15, 12.5, 16);
	_app->objectPresentationSetAnimationOnRotation(10801, 0, 0, 80001);
	_app->objectAddPresentation(kObject10801);
	_app->objectPresentationAddImageToRotation(kObject10801, 1, 10812, 0);
	_app->objectAddPresentation(kObject10801);
	_app->objectPresentationAddImageToRotation(kObject10801, 2, 10812, 2);
	_app->objectAddPresentation(kObject10801);
	_app->objectPresentationAddAnimationToRotation(kObject10801, 3, 10812, 1, 15, 12.5, 16);
	_app->objectPresentationSetAnimationOnRotation(10801, 3, 0, 80002);
	_app->objectAdd(kObjectJavelinWithRose, "javelin with rose", "n_rose", 9);
	_app->objectAddRotationAccessibility(kObjectJavelinWithRose, 10812, Common::Rect(1944, -8, 2000, 187), false, kCursorAction, 1);
	_app->objectAdd(kObjectJavelin, "javelot", "avelin", 9);
	_app->objectAddRotationAccessibility(kObjectJavelin, 10812, Common::Rect(1944,   -8, 2000, 187), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObjectJavelin, 10812, Common::Rect(1800,  -77, 3600, 370), false, kCursorAction, 2);
	_app->objectAddRotationAccessibility(kObjectJavelin, 10812, Common::Rect(   0,  -77, 1800, 370), false, kCursorAction, 3);
	_app->objectAddRotationAccessibility(kObjectJavelin, 10812, Common::Rect(3025, -357, 3420, -91), false, kCursorAction, 4);
	_app->soundAdd(80002, kSoundTypeAmbientEffect, "08_APP-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(80003, kSoundTypeAmbientEffect, "08_PUT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(3016,  kSoundTypeDialog,        "3016.wav",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3017,  kSoundTypeDialog,        "3017.wav",     _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3019,  kSoundTypeDialog,        "3019.wav",     _app->getConfiguration().dialog.loadFrom);
}

void Zone9Pompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	error("[Zone9Pompeii::onButtonUp()] Not implemented");
}

} // End of namespace Ring
