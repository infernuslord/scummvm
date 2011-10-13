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

#include "ring/game/pompeii/pompeii_zone6.h"

#include "ring/game/pompeii/pompeii_application.h"
#include "ring/game/pompeii/pompeii_shared.h"

#include "ring/debug.h"
#include "ring/ring.h"
#include "ring/helpers.h"

using namespace PompeiiGame;

namespace Ring {

Zone6Pompeii::Zone6Pompeii(ApplicationPompeii *application) : _app(application) {
	_hideBox = false;
	_frame1  = 0;
	_frame2  = 0;
	_playSoundValue = 0;
}

Zone6Pompeii::~Zone6Pompeii() {
	// Zero-out passed pointers
	_app = NULL;
}

void Zone6Pompeii::onInit() {
	_app->setCurrentZone(kZone6);

	_app->puzzleAdd(kPuzzle50511);
	_app->puzzleAddBackgroundImage(kPuzzle50511, "s05a01n01p01.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50515);
	_app->puzzleAddBackgroundImage(kPuzzle50515, "s05a01n01p05.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50518);
	_app->puzzleAddBackgroundImage(kPuzzle50518, "s05a01n01p08.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50519);
	_app->puzzleAddBackgroundImage(kPuzzle50519, "s05a01n01p09.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50522);
	_app->puzzleAddBackgroundImage(kPuzzle50522, "s05a02n01p02.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50525);
	_app->puzzleAddBackgroundImage(kPuzzle50525, "s05a02n01p05.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50526);
	_app->puzzleAddBackgroundImage(kPuzzle50526, "s05a02n01p06.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle50529);
	_app->puzzleAddBackgroundImage(kPuzzle50529, "s05a02n01p09.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle505210);
	_app->puzzleAddBackgroundImage(kPuzzle505210, "s05a02n01p10.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle505213);
	_app->puzzleAddBackgroundImage(kPuzzle505213, "s05a02n01p13.bmp", Common::Point(0, 16), true);
	_app->puzzleAdd(kPuzzle505214);
	_app->puzzleAddBackgroundImage(kPuzzle505214, "s05a02n01p14.bmp", Common::Point(0, 16), true);
	_app->rotationAdd(10511, "S05A01-1", 0, 8);
	_app->rotationAdd(10521, "S05A02-1", 0, 14);
	_app->rotationAdd(10531, "S05A03-1", 0, 0);
	_app->rotationSetCompressionBufferLength(10521, 1300000);
	_app->rotationAddMovabilityToRotation(10511, 10521, "", Common::Rect(3447, -127, 3599, 266), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10511, 0, 0.0f, 0.0f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10511, 10531, "", Common::Rect(469, -290, 768, 296), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10511, 1, 0.0f, 0.0f, 87.0f, 0.0f, 1, 0.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10521, 10511, "", Common::Rect(2023, -176, 2522, 396), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10521, 0, 180.0f, 0.0f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->rotationAddMovabilityToRotation(10531, 10511, "", Common::Rect(1974, -268, 2443, 329), true, kCursorMove, 0);
	_app->rotationSetMovabilityToRotation(10531, 0, 0.0f, 0.0f, 87.0f, 0.0f, 1, 180.0f, 0.30000001f, 87.0f);
	_app->puzzleAddMovabilityToRotation(kPuzzle50519,  10511, "", Common::Rect(0, 420, 640, 464), true, kCursorBack, 0);
	_app->puzzleAddMovabilityToRotation(kPuzzle505213, 10521, "", Common::Rect(0, 420, 640, 464), true, kCursorBack, 0);
	_app->objectAdd(kObject55555, "", "", 1);
	_app->objectAddRotationAccessibility(kObject55555, 10511, Common::Rect(24, -112, 374, 187), true, kCursorZoom, 0);
	_app->objectAdd(kObjectTali, "bones", "tali", 9);
	_app->objectAddPuzzleAccessibility(kObjectTali, kPuzzle505213, Common::Rect(0, 0, 640, 420), false, kCursorActionObject, 0);
	_app->objectAddPuzzleAccessibility(kObjectTali, kPuzzle505213, Common::Rect(0, 0, 640, 420), false, kCursorTake, 1);
	_app->objectAddPuzzleAccessibility(kObjectTali, kPuzzle505213, Common::Rect(0, 0, 640, 420), false, kCursorActionObject, 2);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 0, kPuzzle505213, "s05a02n01p13l01.bmp", Common::Point(190, 397), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 1, kPuzzle505213, "s05a02n01p13l02.bmp", Common::Point(224, 401), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 2, kPuzzle505213, "s05a02n01p13l03.bmp", Common::Point(258, 396), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 3, kPuzzle505213, "s05a02n01p13l04.bmp", Common::Point(293, 398), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 4, kPuzzle505213, "s05a02n01p13l05.bmp", Common::Point(328, 398), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 5, kPuzzle505213, "s05a02n01p13l06.bmp", Common::Point(362, 398), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 6, kPuzzle505213, "s05a02n01p13l07.bmp", Common::Point(399, 399), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 7, kPuzzle505213, "s05a02n01p13l08.bmp", Common::Point(436, 396), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 8, kPuzzle505213, "s05a02n01p13l09.bmp", Common::Point(469, 396), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 9, kPuzzle505213, "s05a02n01p13l10.bmp", Common::Point(503, 396), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 10, kPuzzle505213, "s05a02n01p13l11.bmp", Common::Point(505, 41), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 11, kPuzzle505213, "s05a02n01p13l12.bmp", Common::Point(470, 38), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 12, kPuzzle505213, "s05a02n01p13l13.bmp", Common::Point(433, 39), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 13, kPuzzle505213, "s05a02n01p13l14.bmp", Common::Point(401, 39), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 14, kPuzzle505213, "s05a02n01p13l15.bmp", Common::Point(364, 40), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 15, kPuzzle505213, "s05a02n01p13l16.bmp", Common::Point(327, 40), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 16, kPuzzle505213, "s05a02n01p13l17.bmp", Common::Point(294, 41), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 17, kPuzzle505213, "s05a02n01p13l18.bmp", Common::Point(262, 46), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 18, kPuzzle505213, "s05a02n01p13l19.bmp", Common::Point(224, 44), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 19, kPuzzle505213, "s05a02n01p13l20.bmp", Common::Point(182, 49), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 20, kPuzzle505213, "s05a02n01p13s01.0f001.tga", Common::Point(215, 135), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 21, kPuzzle505213, "s05a02n01p13s01.0f002.tga", Common::Point(215, 135), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 22, kPuzzle505213, "s05a02n01p13s01.0f003.tga", Common::Point(215, 135), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 23, kPuzzle505213, "s05a02n01p13s01.0f004.tga", Common::Point(215, 135), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 24, kPuzzle505213, "s05a02n01p13s02.0f001.tga", Common::Point(376, 141), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 25, kPuzzle505213, "s05a02n01p13s02.0f002.tga", Common::Point(376, 141), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 26, kPuzzle505213, "s05a02n01p13s02.0f003.tga", Common::Point(376, 141), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 27, kPuzzle505213, "s05a02n01p13s02.0f004.tga", Common::Point(376, 141), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 28, kPuzzle505213, "s05a02n01p13s03.0f001.tga", Common::Point(199, 265), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 29, kPuzzle505213, "s05a02n01p13s03.0f002.tga", Common::Point(199, 265), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 30, kPuzzle505213, "s05a02n01p13s03.0f003.tga", Common::Point(199, 265), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 31, kPuzzle505213, "s05a02n01p13s03.0f004.tga", Common::Point(199, 265), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 32, kPuzzle505213, "s05a02n01p13s04.0f001.tga", Common::Point(383, 274), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 33, kPuzzle505213, "s05a02n01p13s04.0f002.tga", Common::Point(383, 274), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 34, kPuzzle505213, "s05a02n01p13s04.0f003.tga", Common::Point(383, 274), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 35, kPuzzle505213, "s05a02n01p13s04.0f004.tga", Common::Point(383, 274), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 36, kPuzzle505213, "s05a02n01p13s05.0f001.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 37, kPuzzle505213, "s05a02n01p13s05.0f002.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 38, kPuzzle505213, "s05a02n01p13s05.0f003.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 39, kPuzzle505213, "s05a02n01p13s05.0f004.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 40, kPuzzle505213, "s05a02n01p13s05.0f005.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 41, kPuzzle505213, "s05a02n01p13s05.0f006.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 42, kPuzzle505213, "s05a02n01p13s05.0f007.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 43, kPuzzle505213, "s05a02n01p13s05.0f008.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 44, kPuzzle505213, "s05a02n01p13s05.0f009.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddImageToPuzzle(kObjectTali, 45, kPuzzle505213, "s05a02n01p13s05.0f010.tga", Common::Point(0, 0), true, kDrawType3, 1000);
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddTextToPuzzle(kObjectTali, 46, kPuzzleMenu, "", Common::Point(1, 55), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectAddPresentation(kObjectTali);
	_app->objectPresentationAddTextToPuzzle(kObjectTali, 47, kPuzzleMenu, "", Common::Point(1, 425), kFontDefault, Color(0, 0, 0), Color(255, 255, 255));
	_app->objectAdd(kObjectCubes, "Cubes", "dices", 9);
	_app->objectAddPuzzleAccessibility(kObjectCubes, kPuzzle505213, Common::Rect(0, 0, 640, 420), false, kCursorActionObject, 0);
	_app->objectAddPuzzleAccessibility(kObjectCubes, kPuzzle505213, Common::Rect(0, 0, 640, 420), false, kCursorTake, 1);
	_app->objectAddPuzzleAccessibility(kObjectCubes, kPuzzle505213, Common::Rect(0, 0, 640, 420), false, kCursorActionObject, 2);
	_app->objectAddPresentation(kObjectCubes);
	_app->objectPresentationAddAnimationToPuzzle(kObjectCubes, 0, kPuzzle505213, "s05a02n01p01s01", kImageTypeTGA, Common::Point(30, 0), kDrawType3, 100, 6, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObjectCubes, 0, 0, 50601);
	_app->objectAddPresentation(kObjectCubes);
	_app->objectPresentationAddAnimationToPuzzle(kObjectCubes, 1, kPuzzle505213, "s05a02n01p01s01", kImageTypeTGA, Common::Point(70, 0), kDrawType3, 100, 6, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObjectCubes, 1, 0, 50602);
	_app->objectAddPresentation(kObjectCubes);
	_app->objectPresentationAddAnimationToPuzzle(kObjectCubes, 2, kPuzzle505213, "s05a02n01p01s01", kImageTypeTGA, Common::Point(50, 0), kDrawType3, 100, 6, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObjectCubes, 2, 0, 50603);
	_app->objectAddPresentation(kObjectCubes);
	_app->objectPresentationAddAnimationToPuzzle(kObjectCubes, 3, kPuzzle505213, "s05a02n01p01s01", kImageTypeTGA, Common::Point(50, 0), kDrawType3, 100, 6, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObjectCubes, 3, 0, 50604);
	_app->objectAdd(kObjectSesterces, "sesterces", "terces", 1);
	_app->objectAdd(kObjectNecklace, "necklace", "cklace", 1);
	_app->objectAdd(kObjectRope2, "rope", "rope", 1);
	_app->objectAdd(kObjectBasket3, "basket", "bucket", 1);
	_app->objectAdd(kObjectBasket4, "basket", "bucket", 1);
	_app->objectAdd(kObjectPureWine, "pure wine", "wine", 1);
	_app->objectAddRotationAccessibility(kObjectPureWine, 10511, Common::Rect(3107, -101, 3139, -52), false, kCursorTake, 0);
	_app->objectAdd(kObjectIncenseStick, "incense stick", "astick", 1);
	_app->objectAddRotationAccessibility(kObjectIncenseStick, 10511, Common::Rect(3100, -33, 3179, 28), false, kCursorAction, 0);
	_app->objectAddPuzzleAccessibility(kObjectIncenseStick, kPuzzle50518, Common::Rect(248, 239, 355, 333), false, kCursorTake, 1);
	_app->objectAddPuzzleAccessibility(kObjectIncenseStick, kPuzzle50518, Common::Rect(0, 420, 640, 464), true, kCursorBack, 9);
	_app->objectAdd(kObjectLamp2, "lamp", "lamp", 1);
	_app->objectAddRotationAccessibility(kObjectLamp2, 10511, Common::Rect(3165, -91, 3206, -50), false, kCursorTake, 0);
	_app->objectAdd(kObjectNormalDice, "normal dices", "dices", 9);
	_app->objectAddRotationAccessibility(kObjectNormalDice, 10521, Common::Rect(221, 320, 284, 382), false, kCursorTake, 0);
	_app->objectAdd(kObjectLoadedDice, "loaded dices", "dices", 9);
	_app->objectAddRotationAccessibility(kObjectLoadedDice, 10521, Common::Rect(671, 324, 734, 350), false, kCursorTake, 1);
	_app->objectAdd(kObjectWheel, "wheel", "wheel", 9);
	_app->objectAddPuzzleAccessibility(kObjectWheel, kPuzzle50511, Common::Rect(168, 371, 219, 463), true, kCursorTake, 0);
	_app->objectAdd(kObjectScales, "scales", "scales", 1);
	_app->objectAddRotationAccessibility(kObjectScales, 10511, Common::Rect(3014, -70, 3125, 31), false, kCursorTake, 0);
	_app->objectAddRotationAccessibility(kObjectScales, 10521, Common::Rect(291,  248, 703, 375), false, kCursorActionObject, 1);
	_app->objectAddRotationAccessibility(kObjectScales, 10521, Common::Rect(284,  240, 337, 287), false, kCursorActionObject, 2);
	_app->objectAddRotationAccessibility(kObjectScales, 10521, Common::Rect(376,  247, 423, 289), false, kCursorActionObject, 3);
	_app->objectAdd(kObjectTali2, "tali", "tali", 1);
	_app->objectAdd(kObject50501, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50501, 10511, Common::Rect(2149, -215, 2418, 401), true, kCursorMove, 0);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 0, 10511, 0);
	_app->objectPresentationAddAnimationToRotation(kObject50501, 0, 10511, 1, 15, 12.5f, 16);
	_app->objectPresentationSetAnimationOnRotation(kObject50501, 0, 0, 50606);
	_app->objectAddPresentation(kObject50501);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 2, 10511, 2);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 3, 10511, 3);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 4, 10511, 4);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 5, 10511, 5);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 6, 10511, 6);
	_app->objectAddPresentation(kObject50501);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToPuzzle(kObject50501, 8, kPuzzle50518, "s05a01n01p08l01.bmp", Common::Point(244, 231), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddImageToRotation(kObject50501, 9, 10511, 7);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddAnimationToPuzzle(kObject50501, 10, kPuzzle50515, "s05a01n01p05s01", kImageTypeBMP, Common::Point(152, 145), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50501, 10, 0, 50606);
	_app->objectAddPresentation(kObject50501);
	_app->objectPresentationAddAnimationToPuzzle(kObject50501, 11, kPuzzle50515, "s05a01n01p05s02", kImageTypeBMP, Common::Point(352, 126), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50501, 11, 0, 50607);
	_app->objectAdd(kObject50502, "", "", 1);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 0, 10521, 0);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 0, kPuzzle50522, "s05a02n01p02s01", kImageTypeBMP, Common::Point(340, 155), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 0, 0, 50606);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddAnimationToRotation(kObject50502, 1, 10521, 1, 3, 12.5f, 6);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 2, 10521, 2);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 2, kPuzzle50525, "s05a02n01p05s01", kImageTypeBMP, Common::Point(148, 107), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 2, 0, 50606);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 3, 10521, 3);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 4, 10521, 4);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 5, 10521, 5);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 6, 10521, 6);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 7, 10521, 7);
	_app->objectAddPresentation(kObject50502);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 9, 10521, 9);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 9, kPuzzle50529, "s05a02n01p09s01", kImageTypeBMP, Common::Point(74, 70), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 9, 0, 50606);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 10, 10521, 10);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 10, kPuzzle505210, "s05a02n01p10s01", kImageTypeBMP, Common::Point(425, 110), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 10, 0, 50606);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 11, 10521, 11);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 11, kPuzzle505214, "s05a02n01p14s01", kImageTypeBMP, Common::Point(466, 138), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 11, 0, 50606);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddAnimationToRotation(kObject50502, 12, 10521, 13, 3, 12.5f, 6);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddImageToRotation(kObject50502, 13, 10521, 12);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 14, kPuzzle50526, "s05a02n01p06s01", kImageTypeBMP, Common::Point(41, 74), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 14, 0, 50606);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 15, kPuzzle50526, "s05a02n01p06s02", kImageTypeBMP, Common::Point(451, 107), kDrawType1, 1000, 29, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 15, 0, 50607);
	_app->objectAddPresentation(kObject50502);
	_app->objectPresentationAddAnimationToPuzzle(kObject50502, 16, kPuzzle505210, "s05a02n01p10s02", kImageTypeBMP, Common::Point(97, 65), kDrawType1, 1000, 28, 12.5f, 4);
	_app->objectPresentationSetAnimationOnPuzzle(kObject50502, 16, 0, 50607);
	_app->objectAdd(kObject50511, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorIdle, 1);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorAction, 2);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorIdle, 3);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorAction, 4);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorAction, 5);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorAction, 6);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorIdle, 7);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorAction, 8);
	_app->objectAddRotationAccessibility(kObject50511, 10511, Common::Rect(3181, 10, 3371, 206), false, kCursorIdle, 9);
	_app->objectAdd(kObject50512, "", "", 1);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(0, 0, 0, 0), false, kCursorTake, 0);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(303, 51, 393, 129), true, kCursorActionObject, 1);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(303, 51, 393, 129), false, kCursorActionObject, 2);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(234, 149, 302, 224), false, kCursorActionObject, 3);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(394, 147, 467, 222), false, kCursorActionObject, 4);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(234, 149, 302, 224), true, kCursorTake, 5);
	_app->objectAddPuzzleAccessibility(kObject50512, kPuzzle50511, Common::Rect(394, 147, 467, 222), true, kCursorTake, 6);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 0, kPuzzle50511, "s05a01n01p01l01.bmp", Common::Point(174, 370), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 1, kPuzzle50511, "s05a01n01p01l04.bmp", Common::Point(306, 54), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 2, kPuzzle50511, "s05a01n01p01l05.bmp", Common::Point(235, 51), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 3, kPuzzle50511, "s05a01n01p01l06.bmp", Common::Point(219, 165), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 4, kPuzzle50511, "s05a01n01p01l07.bmp", Common::Point(394, 154), true, kDrawType1, 1000);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddAnimationToPuzzle(kObject50512, 5, kPuzzle50511, "s05a01n01p01s01", kImageTypeBMP, Common::Point(230, 48), kDrawType1, 1000, 30, 15.0f, 10);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 6, kPuzzle50511, "s05a01n01p01l02.bmp", Common::Point(236, 148), true, kDrawType1, 1000);
	_app->objectPresentationShow(kObject50512, 6);
	_app->objectAddPresentation(kObject50512);
	_app->objectPresentationAddImageToPuzzle(kObject50512, 7, kPuzzle50511, "s05a01n01p01l03.bmp", Common::Point(390, 145), true, kDrawType1, 1000);
	_app->objectPresentationShow(kObject50512, 7);
	_app->objectAdd(kObject50521, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50521, 10521, Common::Rect(68,  -49, 270, 254), false, kCursorAction, 0);
	_app->objectAdd(kObject50522, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50522, 10521, Common::Rect(546,   5, 673, 250), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject50522, 10521, Common::Rect(546,   5, 673, 250), false, kCursorIdle, 1);
	_app->objectAddRotationAccessibility(kObject50522, 10521, Common::Rect(546,   5, 673, 250), false, kCursorAction, 2);
	_app->objectAdd(kObject50523, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50523, 10521, Common::Rect(300, 231, 610, 371), false, kCursorActionObject, 0);
	_app->objectAdd(kObject50524, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50524, 10521, Common::Rect(669, -36, 829, 245), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject50524, 10521, Common::Rect(669, -36, 829, 245), false, kCursorIdle, 1);
	_app->objectAdd(kObject50525, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50525, 10521, Common::Rect(80,  -40, 226, 255), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject50525, 10521, Common::Rect(80,  -40, 226, 255), false, kCursorIdle, 1);
	_app->objectAddRotationAccessibility(kObject50525, 10521, Common::Rect(80,  -40, 226, 255), false, kCursorAction, 2);
	_app->objectAdd(kObject50526, "", "", 1);
	_app->objectAddRotationAccessibility(kObject50526, 10521, Common::Rect(170, 42, 341, 245), false, kCursorAction, 0);
	_app->objectAddRotationAccessibility(kObject50526, 10521, Common::Rect(170, 42, 341, 245), false, kCursorAction, 1);
	_app->objectAddRotationAccessibility(kObject50526, 10521, Common::Rect(170, 42, 341, 245), false, kCursorIdle, 2);
	_app->objectAddRotationAccessibility(kObject50526, 10521, Common::Rect(170, 42, 341, 245), false, kCursorAction, 3);
	_app->objectAddRotationAccessibility(kObject50526, 10521, Common::Rect(170, 42, 341, 245), false, kCursorIdle, 4);
	_app->objectAddRotationAccessibility(kObject50526, 10521, Common::Rect(170, 42, 341, 245), false, kCursorAction, 5);
	_app->soundAdd(50502, kSoundTypeAmbientEffect, "05_BLO-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50503, kSoundTypeAmbientEffect, "05_CLO-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50504, kSoundTypeAmbientEffect, "05_HIT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50505, kSoundTypeAmbientEffect, "05_OPE-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50506, kSoundTypeAmbientEffect, "05_PUT-4.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50507, kSoundTypeAmbientEffect, "05_PUT-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50508, kSoundTypeAmbientEffect, "05_PUT-5.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50509, kSoundTypeAmbientEffect, "05_PUT-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50510, kSoundTypeAmbientEffect, "05_PUT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50511, kSoundTypeAmbientEffect, "05_SQU-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50512, kSoundTypeAmbientEffect, "05_TAK-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50513, kSoundTypeAmbientEffect, "05_TAK-6.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50514, kSoundTypeAmbientEffect, "05_TAK-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50515, kSoundTypeAmbientEffect, "05_TAK-5.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50516, kSoundTypeAmbientEffect, "05_TAK-4.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50517, kSoundTypeAmbientEffect, "05_TAK-2.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50518, kSoundTypeAmbientEffect, "05_TAK-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50519, kSoundTypeAmbientEffect, "05_TAK-9.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50520, kSoundTypeAmbientEffect, "05_TAK-8.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50521, kSoundTypeAmbientEffect, "05_THR-3.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50522, kSoundTypeAmbientEffect, "05_THR-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50523, kSoundTypeAmbientEffect, "05_THR-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50524, kSoundTypeAmbientEffect, "05_THR-7.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50525, kSoundTypeAmbientEffect, "05_THR-5.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50526, kSoundTypeAmbientEffect, "05_THR-6.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50527, kSoundTypeAmbientEffect, "05_THR-4.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(50528, kSoundTypeAmbientEffect, "05_WAT-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->soundAdd(1068, kSoundTypeDialog, "1068.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1069, kSoundTypeDialog, "1069.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1070, kSoundTypeDialog, "1070.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1071, kSoundTypeDialog, "1071.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1072, kSoundTypeDialog, "1072.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1073, kSoundTypeDialog, "1073.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1074, kSoundTypeDialog, "1074.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1075, kSoundTypeDialog, "1075.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1076, kSoundTypeDialog, "1076.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1077, kSoundTypeDialog, "1077.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1078, kSoundTypeDialog, "1078.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1079, kSoundTypeDialog, "1079.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1080, kSoundTypeDialog, "1080.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1081, kSoundTypeDialog, "1081.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1082, kSoundTypeDialog, "1082.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1083, kSoundTypeDialog, "1083.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1084, kSoundTypeDialog, "1084.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1085, kSoundTypeDialog, "1085.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1086, kSoundTypeDialog, "1086.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(1087, kSoundTypeDialog, "1087.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2023, kSoundTypeDialog, "2023.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2024, kSoundTypeDialog, "2024.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2025, kSoundTypeDialog, "2025.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2026, kSoundTypeDialog, "2026.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2068, kSoundTypeDialog, "2068.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2069, kSoundTypeDialog, "2069.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2070, kSoundTypeDialog, "2070.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2071, kSoundTypeDialog, "2071.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2072, kSoundTypeDialog, "2072.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2073, kSoundTypeDialog, "2073.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2074, kSoundTypeDialog, "2074.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(2075, kSoundTypeDialog, "2075.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3055, kSoundTypeDialog, "3055.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(3056, kSoundTypeDialog, "3056.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4022, kSoundTypeDialog, "4022.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4023, kSoundTypeDialog, "4023.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4024, kSoundTypeDialog, "4024.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4025, kSoundTypeDialog, "4025.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4026, kSoundTypeDialog, "4026.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4027, kSoundTypeDialog, "4027.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4028, kSoundTypeDialog, "4028.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4029, kSoundTypeDialog, "4029.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4030, kSoundTypeDialog, "4030.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4092, kSoundTypeDialog, "4092.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(4093, kSoundTypeDialog, "4093.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59060, kSoundTypeDialog, "tali60.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59070, kSoundTypeDialog, "tali70.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59080, kSoundTypeDialog, "tali80.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59090, kSoundTypeDialog, "tali90.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59100, kSoundTypeDialog, "tali100.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59101, kSoundTypeDialog, "tali101.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59110, kSoundTypeDialog, "tali110.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59120, kSoundTypeDialog, "tali120.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59130, kSoundTypeDialog, "tali130.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59140, kSoundTypeDialog, "tali140.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59141, kSoundTypeDialog, "tali141.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59150, kSoundTypeDialog, "tali150.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59160, kSoundTypeDialog, "tali160.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59170, kSoundTypeDialog, "tali170.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59180, kSoundTypeDialog, "tali180.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59190, kSoundTypeDialog, "tali190.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59191, kSoundTypeDialog, "tali191.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59200, kSoundTypeDialog, "tali200.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59210, kSoundTypeDialog, "tali210.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59220, kSoundTypeDialog, "tali220.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59230, kSoundTypeDialog, "tali230.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59240, kSoundTypeDialog, "tali240.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59250, kSoundTypeDialog, "tali250.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59260, kSoundTypeDialog, "tali260.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59270, kSoundTypeDialog, "tali270.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(59280, kSoundTypeDialog, "tali280.wac", _app->getConfiguration().dialog.loadFrom);
	_app->soundAdd(50501, kSoundTypeAmbientMusic, "05_AMB-1.WAs", _app->getConfiguration().ambientEffect.loadFrom);
	_app->rotationAddAmbientSound(10511, 50501, 95, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10521, 50501, 100, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10531, 50501, 95, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50511, 50501, 95, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50515, 50501, 95, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50518, 50501, 95, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50519, 50501, 95, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50522, 50501, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50525, 50501, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50526, 50501, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50529, 50501, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle505210, 50501, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle505213, 50501, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle505214, 50501, 100, 0, 1, 1, 10);
	_app->soundAdd(50550, kSoundTypeAmbientMusic, "BGR_MU-2.WAc", _app->getConfiguration().ambientEffect.loadFrom);
	_app->puzzleAddAmbientSound(kPuzzle505213, 50550, 100, 0, 1, 1, 10);
	_app->soundAdd(50551, kSoundTypeAmbientMusic, "BGR_MU-1.WAc", _app->getConfiguration().ambientEffect.loadFrom);
	_app->rotationAddAmbientSound(10511, 50551, 100, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10521, 50551, 100, 0, 1, 1, 10);
	_app->rotationAddAmbientSound(10531, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50511, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50515, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50518, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50519, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50522, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50525, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50526, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle50529, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle505210, 50551, 100, 0, 1, 1, 10);
	_app->puzzleAddAmbientSound(kPuzzle505214, 50551, 100, 0, 1, 1, 10);
	_app->varDefineByte(50001, 0);
	_app->varDefineWord(50001, 0);
	_app->varDefineWord(50002, 0);
	_app->varDefineByte(50002, 0);
	_app->varDefineByte(50003, 0);
	_app->varDefineByte(50004, 0);
	_app->varDefineByte(50005, 0);
	_app->varDefineByte(50006, 0);
	_app->varDefineByte(50007, 0);
	_app->varDefineByte(50609, 0);
	_app->varDefineByte(50601, 0);
	_app->varDefineByte(50602, 0);
	_app->varDefineByte(50603, 0);
	_app->varDefineByte(50604, 0);
	_app->varDefineByte(50605, 0);
	_app->varDefineByte(50606, 0);
	_app->varDefineByte(50607, 0);
	_app->varDefineByte(50608, 0);
	_app->varDefineByte(50613, 0);
	_app->varDefineByte(50614, 0);
	_app->varDefineByte(50615, 0);
	_app->varDefineByte(50616, 0);
	_app->varDefineByte(50610, 0);
	_app->varDefineByte(50611, 0);
	_app->varDefineByte(50612, 0);
	_app->varDefineWord(50601, 0);
	_app->varDefineWord(50602, 0);
	_app->varDefineWord(50603, 0);
	_app->varDefineWord(50604, 0);
	_app->varDefineWord(50605, 0);
	_app->varDefineWord(50606, 0);
	_app->varDefineWord(50607, 0);
	_app->varDefineWord(50608, 0);
	_app->varDefineWord(50609, 0);
	_app->varDefineWord(50610, 0);
	_app->varDefineWord(50611, 0);
	_app->varDefineWord(50612, 0);
	_app->varDefineByte(50620, 0);
	_app->varDefineByte(50621, 0);
}

void Zone6Pompeii::onButtonUp(ObjectId id, Id target, Id puzzleRotationId, uint32 a4, const Common::Point &point) {
	error("[Zone6Pompeii::onButtonUp()] Not implemented");
}

void Zone6Pompeii::onTimer(TimerId id) {
	switch (id) {
	default:
		break;

	case 0:
		_app->timerStop(kTimer0);
		_app->varSetByte(50609, 1);
		_app->objectPresentationUnpauseAnimation(kObjectCubes, 2);
		_app->objectPresentationUnpauseAnimation(kObjectCubes, 3);
		_app->objectPresentationHide(kObjectCubes, 2);
		_app->objectPresentationHide(kObjectCubes, 3);

		handleEvents();

		_app->varSetByte(50607, 0);
		_app->varSetByte(50608, 0);
		_app->varSetByte(50603, 0);
		_app->varSetByte(50604, 0);
		_app->varSetWord(50603, 0);
		_app->varSetWord(50604, 0);
		_app->varSetWord(50607, 0);
		_app->varSetWord(50608, 0);
		_app->varSetWord(50611, 0);
		_app->varSetWord(50612, 0);
		_frame1 = rnd(6) + 1;
		_frame2 = rnd(6) + 1;
		_app->objectPresentationShow(kObjectCubes, 2);
		_app->soundPlay(50527);
		break;

	case 1:
		_app->timerStop(kTimer1);
		_app->soundPlay(2071);
		break;

	case 2:
		_app->timerStop(kTimer2);
		_app->objectPresentationUnpauseAnimation(kObject50501, 0);
		_app->objectPresentationUnpauseAnimation(kObject50501, 10);
		_app->objectPresentationUnpauseAnimation(kObject50502, 0);
		_app->objectPresentationUnpauseAnimation(kObject50502, 2);
		_app->objectPresentationUnpauseAnimation(kObject50502, 9);
		_app->objectPresentationUnpauseAnimation(kObject50502, 10);
		_app->objectPresentationUnpauseAnimation(kObject50502, 11);
		_app->objectPresentationUnpauseAnimation(kObject50502, 14);
		break;

	case 3:
		_app->timerStop(kTimer3);
		_app->objectPresentationUnpauseAnimation(kObject50501, 11);
		_app->objectPresentationUnpauseAnimation(kObject50502, 15);
		_app->objectPresentationUnpauseAnimation(kObject50502, 16);
		break;
	}
}

void Zone6Pompeii::onAnimationNextFrame(Id animationId, const Common::String &name, uint32 frame, uint32 frameCount) {
	error("[Zone6Pompeii::onAnimationNextFrame] Not implemented");
}

void Zone6Pompeii::onSound(Id id, SoundType type, uint32 a3, bool process) {
	error("[Zone6Pompeii::onSound] Not implemented");
}

void Zone6Pompeii::onUpdateBag(const Common::Point &point) {
	if (_hideBox) {
		_app->visualBoxHide(6, kPuzzleMenu);
		_hideBox = false;
	}
}

void Zone6Pompeii::onUpdateBefore(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, const Common::Point &point) {
	error("[Zone6Pompeii::onUpdateBefore] Not implemented");
}

void Zone6Pompeii::onUpdateAfter(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType, const Common::Point &point) {
	if (_hideBox) {
		_app->visualBoxHide(6, kPuzzleMenu);
		_hideBox = false;
	}
}

void Zone6Pompeii::onAfterRide(Id movabilityFrom, Id movabilityTo, uint32 movabilityIndex, Id target, MovabilityType movabilityType) {
	if (movabilityType == kMovabilityPuzzleToRotation && movabilityTo == 505213) {
		_app->timerStop(kTimer1);
		_app->objectSetAccessibilityOn(kObject50523);

		if (_app->varGetByte(90001) == 2) {
			_app->rotationSetMovabilityOff(10521);

			if (_app->varGetByte(90215) == 2) {
				if (_app->varGetByte(50002) == _playSoundValue)
					_app->soundPlay(2074);
				else if ( _app->varGetByte(50003) == _playSoundValue)
					_app->soundPlay(2073);
			} else {
				_app->soundPlay(2075);
			}
		} else {
			if (_app->varGetByte(90001) > 2)
				_app->objectPresentationShow(kObject50502, 4);
		}
	}
}

void Zone6Pompeii::onVisualList(Id id, uint32 type, const Common::Point &point) {
	error("[Zone6Pompeii::onVisualList] Not implemented");
}

} // End of namespace Ring
