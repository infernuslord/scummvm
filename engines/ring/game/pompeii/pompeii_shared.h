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

#ifndef RING_POMPEII_SHARED_H
#define RING_POMPEII_SHARED_H

namespace PompeiiGame {

enum PuzzleId {
	kPuzzle1000                    = 1000,
	kPuzzle1001                    = 1001,
	kPuzzle1002                    = 1002,
	kPuzzle1004                    = 1004,
	kPuzzle1007                    = 1007,
	kPuzzle1010                    = 1010,
	kPuzzle1011                    = 1011,
	kPuzzle1013                    = 1013,
	kPuzzle1015                    = 1015,
	kPuzzle1016                    = 1016,
	kPuzzle1017                    = 1017,
	kPuzzle1020                    = 1020,
	kPuzzle1023                    = 1023,
	kPuzzle1026                    = 1026,
	kPuzzle1027                    = 1027,
	kPuzzle1030                    = 1030,
	kPuzzle1033                    = 1033,
	kPuzzle1035                    = 1035,
	kPuzzle1036                    = 1036,
	kPuzzle1037                    = 1037,
	kPuzzle1038                    = 1038,
	kPuzzle1039                    = 1039,
	kPuzzle1040                    = 1040,
	kPuzzle1044                    = 1044,
	kPuzzle1045                    = 1045,
	kPuzzle1046                    = 1046,
	kPuzzle1048                    = 1048,
	kPuzzle1049                    = 1049,
	kPuzzle1051                    = 1051,
	kPuzzle1053                    = 1053,
	kPuzzle1056                    = 1056,
	kPuzzle1060                    = 1060,
	kPuzzle1063                    = 1063,
	kPuzzle1064                    = 1064,
	kPuzzle30311                   = 30311,
	kPuzzle30312                   = 30312,
	kPuzzle30313                   = 30313,
	kPuzzle30314                   = 30314,
	kPuzzle30317                   = 30317,
	kPuzzle30321                   = 30321,
	kPuzzleEncyclopedia            = 50000,
	kPuzzle70121                   = 70121,
	kPuzzle70211                   = 70211,
	kPuzzleGeneralMenu             = 90000,
	kPuzzleLoad                    = 90001,
	kPuzzleSave                    = 90002,
	kPuzzlePreferences             = 90003,
	kPuzzleStatus                  = 90004,
	kPuzzleInsertCd                = 90006,
	kPuzzle99001                   = 99001,
	kPuzzle99002                   = 99002,
	kPuzzle99003                   = 99003,
	kPuzzle110111                  = 110111,
	kPuzzle110221                  = 110221,
	kPuzzle110222                  = 110222,
};

enum ObjectId {
	kObjectItemList          = 7,
	kObject16                = 16,
	kObject1000              = 1000,
	kObject1001              = 1001,
	kObjectStick             = 1002,
	kObjectRope              = 1003,
	kObjectSalad             = 1004,
	kObject1005              = 1005,
	kObject1006              = 1006,
	kObjectDates             = 1007,
	kObject1008              = 1008,
	kObject1009              = 1009,
	kObject1010              = 1010,
	kObject1011              = 1011,
	kObject1012              = 1012,
	kObject1013              = 1013,
	kObject1016              = 1016,
	kObject1017              = 1017,
	kObjectBracelet          = 1018,
	kObject1019              = 1019,
	kObject1020              = 1020,
	kObject1021              = 1021,
	kObject1023              = 1023,
	kObjectDoveFeather       = 1026,
	kObject1028              = 1028,
	kObject1031              = 1031,
	kObject1033              = 1033,
	kObjectCommercialAdd     = 1036,
	kObject1035              = 1035,
	kObjectBasket            = 1037,
	kObjectBasket2           = 1038,
	kObject1039              = 1039,
	kObject1040              = 1040,
	kObject1041              = 1041,
	kObjectFlask             = 1042,
	kObjectPerfumedOil       = 1043,
	kObject1044              = 1044,
	kObject1045              = 1045,
	kObject1046              = 1046,
	kObject1048              = 1048,
	kObject1049              = 1049,
	kObject1050              = 1050,
	kObject1051              = 1051,
	kObject1052              = 1052,
	kObject1053              = 1053,
	kObject1054              = 1054,
	kObject1055              = 1055,
	kObjectRoses             = 1056,
	kObject1057              = 1057,
	kObject1059              = 1059,
	kObject1061              = 1061,
	kObject1062              = 1062,
	kObject1064              = 1064,
	kObject1066              = 1066,
	kObject1067              = 1067,
	kObject1068              = 1068,
	kObjectStone             = 1069,
	kObjectBranch            = 1070,
	kObject1071              = 1071,
	kObject1072              = 1072,
	kObject1073              = 1073,
	kObject1075              = 1075,
	kObject1076              = 1076,
	kObject1077              = 1077,
	kObject1078              = 1078,
	kObject1079              = 1079,
	kObject1080              = 1080,
	kObject1081              = 1081,
	kObject1084              = 1084,
	kObject1085              = 1085,
	kObject1089              = 1089,
	kObject1093              = 1093,
	kObject1094              = 1094,
	kObjectStone2            = 1095,
	kObjectKey               = 10002,
	kObjectAmulet            = 10003,
	kObjectContract          = 10004,
	kObjectRopes             = 10005,
	kObjectWine              = 10013,
	kObjectIncense           = 10014,
	kObjectLamp              = 10015,
	kObjectEggs              = 10021,
	kObjectTuna              = 10022,
	kObjectMussels           = 10023,
	kObjectDuck              = 10024,
	kObjectDugs              = 10025,
	kObjectDulcia            = 10026,
	kObjectDates2            = 10027,
	kObjectOysters           = 10028,
	kObjectRedFish           = 10029,
	kObjectNightingale       = 10030,
	kObject10041             = 10041,
	kObject10042             = 10042,
	kObject10043             = 10043,
	kObject10044             = 10044,
	kObject10045             = 10045,
	kObject10046             = 10046,
	kObject10047             = 10047,
	kObject10048             = 10048,
	kObject10049             = 10049,
	kObject10050             = 10050,
	kObject10051             = 10051,
	kObject10052             = 10052,
	kObject10053             = 10053,
	kObject10054             = 10054,
	kObject10071             = 10071,
	kObject10441             = 10441,
	kObjectPhiltre1          = 10571,
	kObjectPhiltre2          = 10572,
	kObject10591             = 10591,
	kObject10701             = 10701,
	kObject10801             = 10801,
	kObject11001             = 11001,
	kObject11002             = 11002,
	kObject11004             = 11004,
	kObject11005             = 11005,
	kObject11006             = 11006,
	kObjectKnife             = 30006,
	kObject30301             = 30301,
	kObject30311             = 30311,
	kObject30312             = 30312,
	kObject30313             = 30313,
	kObject30314             = 30314,
	kObject30315             = 30315,
	kObjectHollyWater        = 40413,
	kObjectTali              = 50500,
	kObjectCubes             = 50601,
	kObjectDropOfWater       = 60612,
	kObject70701             = 70701,
	kObject70702             = 70702,
	kObject70703             = 70703,
	kObjectJavelin           = 80801,
	kObjectJavelinWithRose   = 80802,
	kObject90001             = 90001,
	kObject90002             = 90002,
	kObject90003             = 90003,
	kObject90004             = 90004,
	kObject90401             = 90401,
	kObjectRope2             = 90511,
	kObjectBasket3           = 90512,
	kObjectBasket4           = 90513,
	kObjectWheel             = 90514,
	kObjectScales            = 90515,
	kObjectNormalDice        = 90516,
	kObjectLoadedDice        = 90517,
	kObjectNecklace          = 90518,
	kObjectTali2             = 90524,
	kObjectGlassTube         = 90601,
	kObjectGlassTube2        = 90602,
	kObjectPapyrus           = 90703,
	kObjectSylphium          = 90704,
	kObjectMuleTooth         = 91001,
	kObjectFabricAndFlour    = 91003,
	kObjectBread             = 91004,
	kObjectStones            = 91201,
	kObjectPureWine          = 91202,
	kObjectLamp2             = 91203,
	kObjectRose              = 91204,
	kObjectMuleToothPowder   = 91205,
	kObjectDropOfBblood      = 91206,
	kObjectApolloTear        = 91207,
	kObjectIbisFeather       = 91208,
	kObjectIncenseStick      = 91209,
	kObjectItemListCompleted = 91210,
	kObject99000             = 99000,
	kObject99001             = 99001,
	kObject99002             = 99002,
	kObject99003             = 99003,
	kObject99004             = 99004,
	kObject99005             = 99005,
	kObject99006             = 99006,
	kObject99007             = 99007,
	kObject99009             = 99009,
	kObject99022             = 99022,
	kObject99023             = 99023,
	kObject99024             = 99024,
	kObject99025             = 99025,
	kObject99041             = 99041,
	kObject99042             = 99042,
	kObject99043             = 99043,
	kObject99044             = 99044,
	kObject99045             = 99045,
	kObject99046             = 99046,
	kObject99601             = 99601,
	kObjectWood              = 99901,
	kObjectSesterces         = 99950,
	kObjectMule              = 100081,
	kObjectMaskAndCoat       = 911001,
	kObjectCapsa             = 911002
};

} // End of namespace JerusalemGame

#endif // RING_POMPEII_SHARED_H
