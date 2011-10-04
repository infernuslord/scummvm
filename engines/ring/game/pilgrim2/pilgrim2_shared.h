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

#ifndef RING_PILGRIM2_SHARED_H
#define RING_PILGRIM2_SHARED_H

namespace Pilgrim2Game {

//enum PuzzleId {
//};

enum ObjectId {
	kObjectPhorbas                      = 10000,
	kObjectBigKey                       = 10002,
	kObjectAdze                         = 10003,
	kObjectRope                         = 10004,
	kObjectTineul                       = 10005,
	kObjectTineulAndRope                = 10008,
	kObjectPearlBox                     = 10016,
	kObjectBucketOnRope                 = 10018,
	kObjectBucketFullOfWater            = 10019,
	kObjectMeat                         = 10024,
	kObjectLittleStones                 = 10050,
	kObjectOilGourd                     = 10051,
	kObjectOiledKey                     = 10052,
	kObjectNail                         = 10059,
	kObjectWoodenBoard                  = 10060,
	kObjectMass                         = 10064,
	kObjectBucket                       = 10066,
	kObjectMassAndAdze                  = 10067,
	kObjectSimonLetter                  = 10069,
	kObjectHammer                       = 10072,
	kObjectHammerAndAdze                = 10073,
	kObjectLadder                       = 10074,
	kObjectSilverDinar                  = 20000,
	kObjectChelidonia                   = 22008,
	kObjectLemon                        = 22009,
	kObjectSmallBox                     = 22010,
	kObjectCodedMessage                 = 22011,
	kObjectMedicalHerbs                 = 22012,
	kObjectUncodedMessage               = 22013,
	kObjectArtemisia                    = 22021,
	kObjectChelidonia2                  = 22022,
	kObjectMallow                       = 22023,
	kObjectGreenAnisen                  = 22024,
	kObjectStJohnWort                   = 22025,
	kObjectIronStick                    = 22052,
	kObjectOilLamp                      = 22055,
	kObjectNotebook                     = 22073,
	kObjectGreenAnisen2                 = 22075,
	kObjectArtemisia2                   = 22076,
	kObjectStJohnWort2                  = 22077,
	kObjectMallow2                      = 22078,
	kObjectHawthornPollen               = 22079,
	kObjectSpiritOfRedPoppy             = 22080,
	kObjectWaterOfBistorte              = 22082,
	kObjectRaspberryWater               = 22083,
	kObjectMortar                       = 22084,
	kObjectMeasuringGlass               = 22086,
	kObjectGlassFlask                   = 22088,
	kObjectGlassFlask2                  = 22089,
	kObjectSword                        = 24007,
	kObjectBucketOfWater                = 24009,
	kObjectWaterJug                     = 24010,
	kObjectSecondRightPart              = 24023,
	kObjectFourthLeftPart               = 24024,
	kObjectThirdLeftPart                = 24025,
	kObjectFirstRightPart               = 24026,
	kObjectFirstLeftPart                = 24027,
	kObjectSecondLeftPart               = 24028,
	kObjectFifthLeftPart                = 24029,
	kObjectHead                         = 24030,
	kObjectTorso                        = 24031,
	kObjectRightButton                  = 24032,
	kObjectLeftButton                   = 24033,
	kObjectIcicles                      = 25000,
	kObjectSling                        = 25001,
	kObjectKey                          = 25007,
	kObjectKey2                         = 25008,
	kObjectKey3                         = 25009,
	kObjectKey4                         = 25010,
	kObjectKey5                         = 25011,
	kObjectKey6                         = 25012,
	kObjectKey7                         = 25013,
	kObjectKey8                         = 25014,
	kObjectKey9                         = 25015,
	kObjectKey10                        = 25016,
	kObjectSlingWithNarcoticIcicles     = 25020,
	kObjectNarcoticIcicles              = 25021,
	kObjectNarcoticFlask                = 25022,
	kObjectSmallCrystalBall             = 26014,
	kObjectLargeCrystalBall             = 27000,
	kObjectToothedWhee                  = 27001,
	kObjectSmallCase                    = 27006,
	kObjectMetallicSkyMap               = 27020,
	kObjectBoar                         = 27021,
	kObjectStag                         = 27022,
	kObjectHare                         = 27023,
	kObjectKnights                      = 27024,
	kObjectDonkey                       = 27025,
	kObjectMermaid                      = 27026,
	kObjectDragon                       = 27027,
	kObjectPeacock                      = 27028,
	kObjectHawks                        = 27029,
	kObjectStork                        = 27030,
	kObjectSheatfish                    = 27031,
	kObjectCat                          = 27032,
	kObjectSkyMapFrame                  = 27033,
	kObjectKey11                        = 27043,
	kObjectTalisman                     = 29000,
	kObjectWaxDoll                      = 30002,
	kObjectWeight                       = 30010,
	kObjectWeight2                       = 30011,
	kObjectWeight3                      = 30012,
	kObjectWeight4                      = 30013,
	kObjectWeight5                      = 30014,
	kObjectWeight6                      = 30015,
	kObjectWeight7                      = 30016,
	kObjectWeight8                      = 30017,
	kObjectWeight9                      = 30018,
	kObjectBowAndArrows                 = 30020,
	kObjectCarafe                       = 30022,
	kObjectInkBottle                    = 30027,
	kObjectLighter                      = 30033,
	kObjectDungPancakes                 = 41001,
	kObjectBrooch                       = 41016,
	kObjectMouse                        = 41015,
	kObjectMagnifyingGlass              = 41017,
	kObjectIronNeedle                   = 41018,
	kObjectMap                          = 41019,
	kObjectBishop                       = 41030,
	kObjectTorchOnFire                  = 41038,
	kObjectDungPancakesOnFire           = 41040,
	kObjectBrooch2                      = 41052,
	kObjectBush                         = 50003,
	kObjectWoodenBranch                 = 50004,
	kObjectTurban                       = 50005,
	kObjectWhiteSulphur                 = 50011,
	kObjectKyot                         = 50013,
	kObjectTorch                        = 50017,
	kObjectBurningTorch                 = 50018,
	kObjectParchment                    = 50020,
	kObjectTalisman2                    = 50021,
	kObjectRajib                        = 59003,
	kObjectTaleb                        = 59004,
	kObjectIsaac                        = 59005,
	kObjectQamar                        = 59006,
	kObjectAnNab                        = 59008,
	kObjectCaradoc                      = 59009,
	kObjectRedSulphur                   = 930001,
	kObjectBlackSulphur                 = 940001,
	kObjectLighter2                     = 999996,
	kObjectSword2                       = 999997,
	kObjectDagger                       = 999998
};

} // End of namespace JerusalemGame

#endif // RING_PILGRIM2_SHARED_H
