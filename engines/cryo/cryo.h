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
 *
 */

#ifndef CRYO_H
#define CRYO_H

#include "cryo/debug.h"

#include "common/random.h"

#include "engines/advancedDetector.h"
#include "engines/engine.h"

#include "graphics/pixelformat.h"

/**
 * This is the namespace of the Cryo engine.
 *
 * Maintainers:
 *  littleboy
 *
 * Supported games:
 *  - Atlantis: The Lost Tales
 *  - Atlantis II: Beyond Atlantis,
 *  - Atlantis III: The New World
 *  - Atlantis Evolution
 *  - The Secrets of Atlantis: The Sacred Legacy
 *  - Aztec: The Curse in the Heart of the City of Gold
 *  - China: The Forbidden City
 *  - Egypt 1156 B.C.: Tomb of the Pharaoh
 *  - Egypt II: The Heliopolis Prophecy
 *  - Salammbo: Battle for Carthage
 *  - Versailles 1685
 *  - Versailles II: Testament of the King
 *  - Zero Zone
 *
 */
namespace Cryo {

struct CryoGameDescription {
	ADGameDescription desc;

	int gameType;
	uint32 features;
};

enum CryoGameType {
	GameTypeAtlantis,
	GameTypeAtlantis2,
	GameTypeAtlantis3,
	GameTypeAtlantis4,
	GameTypeAtlantis5,
	GameTypeAztec,
	GameTypeChina,
	GameTypeEgypt,
	GameTypeEgypt2,
	GameTypeSalammbo,
	GameTypeVersailles,
	GameTypeVersailles2,
	GameTypeZeroZone
};

class Game;

class CryoEngine : public Engine {
public:
	CryoEngine(OSystem *syst, const CryoGameDescription *gd);
	~CryoEngine();

	// Event handling
	bool handleEvents();
	void pollEvents();

	// Misc
	Common::RandomSource getRandom() const {return _random; }

protected:
	// Engine APIs
	Common::Error run();
	virtual Debugger *getDebugger() { return _debugger; }

private:
	const CryoGameDescription *_gameDescription;

	// Misc
	Debugger *_debugger;
	Common::RandomSource _random;

	Game *_game;
};

} // End of namespace Cryo

#endif // CRYO_H
