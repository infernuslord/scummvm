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

#ifndef RING_PILGRIM3_SHARED_H
#define RING_PILGRIM3_SHARED_H

namespace Pilgrim3Game {

//enum PuzzleId {
//};

enum ObjectId {
	kObjectCoat                             = 7,
	kObjectPants                            = 8,
	kObjectSpurs                            = 9,
	kObjectTunic                            = 10,
	kObjectDagger                           = 11,
	kObjectTurban                           = 12,
	kObjectSword                            = 13,
	kObjectStones                           = 61000,
	kObjectEmptyFlask                       = 62002,
	kObjectAcidInFlask                      = 62003,
	kObjectWaterInFlask                     = 62004,
	kObjectRedInFlask                       = 62005,
	kObjectYellowInFlask                    = 62006,
	kObjectBlueInFlask                      = 62007,
	kObjectKyot                             = 65122,
	kObjectFirstTalismanPart                = 66000,
	kObjectLighter                          = 66001,
	kObjectTorch                            = 70014,
	kObjectEmbers                           = 70019,
	kObjectRuby                             = 70020,
	kObjectSapphire                         = 70021,
	kObjectJade                             = 70022,
	kObjectEmerald                          = 70023,
	kObjectCoral                            = 70024,
	kObjectIncenseBranch                    = 70026,
	kObjectVeil                             = 70028,
	kObjectPeacockFeather                   = 70030,
	kObjectSpatula                          = 70032,
	kObjectVeilOverBirdCage                 = 70035,
	kObjectBirdCage                         = 70037,
	kObjectGrape                            = 70042,
	kObjectSword2                           = 70050,
	kObjectDagger2                          = 70051,
	kObjectKyotThePoet                      = 70052,
	kObjectAnNabTheCaravanier               = 70053,
	kObjectLetter                           = 70054,
	kObjectLetter2                          = 70055,
	kObjectFirstTalismanPart2               = 70056,
	kObjectSecondTalismanPart               = 70057,
	kObjectTorch2                           = 70061,
	kObjectRajibTheKhan                     = 70062,
	kObjectTalebTheMetalworker              = 70063,
	kObjectIsaacTheKabalist                 = 70064,
	kObjectCaradocTheWarrior                = 70065,
	kObjectQamarTheAstrologer               = 70066,
	kObjectLighter2                         = 70067,
	kObjectSpatulaWithEmbers                = 70068,
	kObjectJewels                           = 70069,
	kObjectOilInBowl                        = 70073,
	kObjectOilInBowlOnFire                  = 70074,
	kObjectAppleCore                        = 81003,
	kObjectLinenBag                         = 81005,
	kObjectRope                             = 81006,
	kObjectStone                            = 81007,
	kObjectLighter3                         = 81011,
	kObjectTorchOnFire                      = 84000,
	kObjectSkull                            = 85000,
	kObjectRung                             = 85002,
	kObjectCopperKey                        = 85004,
	kObjectGoldKey                          = 85007,
	kObjectIronKey                          = 85009,
	kObjectMagnetizedRosary                 = 85012,
	kObjectBoneKey                          = 85013,
	kObjectSecretkey                        = 85015,
	kObjectPaperInVellum                    = 85019,
	kObjectSquareBox                        = 86002,
	kObjectRoundBox                         = 86005,
	kObjectSecretBox                        = 86007,
	kObjectThirdTalismanPart                = 86008,
	kObjectSecondTalismanPart2              = 86009,
	kObjectFirstTalismanPart3               = 86010,
	kObjectRajibTheKhan2                    = 89003,
	kObjectTalebTheMetalworker2             = 89004,
	kObjectIsaacTheKabalist2                = 89005,
	kObjectQamarTheAstrologer2              = 89006,
	kObjectKyotThePoet2                     = 89007,
	kObjectAnNabTheCaravanier2              = 89008,
	kObjectCaradocTheWarrior2               = 89009,
	kObjectredSticks                        = 90050,
	kObjectwhiteSticks                      = 90051,
	kObjectFirebrand                        = 91004,
	kObjectFirstTalismanPart4               = 91010,
	kObjectSecondTalismanPart3              = 91011,
	kObjectThirdTalismanPart2               = 91012,
	kObjectLighter4                         = 91013,
	kObjectFirebrandOnFire                  = 91014,
	kObjectCrystallRock                     = 91015,
	kObjectFirstTalismanPart5               = 101004,
	kObjectSecondTalismanPart4              = 101005,
	kObject3PiecesOfRope                    = 102002,
	kObjectGutter                           = 102003,
	kObjectJug                              = 102004,
	kObjectWoodenPlatform                   = 102005,
	kObjectJugAndRope                       = 102007,
	kObjectRope2                            = 102010,
	kObject2PiecesOfRope                    = 102012,
	kObjectChain                            = 103001,
	kObjectCrowbar                          = 103002,
	kObjectBoards                           = 103003,
	kObjectLamp                             = 103004,
	kObjectLitLampAttachedToChain           = 103006,
	kObjectUnlitLampAttachedToChain         = 103007,
	kObjectLitLamp                          = 103008,
	kObjectHook                             = 104001,
	kObjectPulley                           = 104002,
	kObjectSieve                            = 104003,
	kObjectNet                              = 104004,
	kObjectO                                = 104006,
	kObjectC                                = 104007,
	kObjectU                                = 104008,
	kObjectL                                = 104009,
	kObjectO2                               = 104010,
	kObjectKey                              = 104011,
	kObjectGoldBars                         = 104013,
	kObjectNetWithGoldBars                  = 104014,
	kObjectGoldBar                          = 104015,
	kObjectNetWithGoldBarsAttachedToHook    = 104018,
	kObjectSaltTose                         = 105002,
	kObjectJarWithOil                       = 106001,
	kObjectCloth                            = 106002,
	kObjectOiledCloth                       = 106003,
	kObjectEmptyJar                         = 106004,
	kObjectSoil                             = 106006,
	kObjectWaterInJar                       = 106005,
	kObjectWarriorMask                      = 106011,
	kObjectRoseLeafs                        = 106020,
	kObjectSword3                           = 999997,
	kObjectDagger3                          = 999998,
	kObjectLighter5                         = 999996,
	kObjectDagger4                          = 999999
};

} // End of namespace JerusalemGame

#endif // RING_PILGRIM3_SHARED_H
