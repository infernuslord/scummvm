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

#include "cryo/cryo.h"

#include "cryo/game/game.h"

#ifdef ENABLE_ATLANTIS1
#include "cryo/game/atlantis/atlantis.h"
#endif

#ifdef ENABLE_ATLANTIS2
#include "cryo/game/atlantis2/atlantis2.h"
#endif

#ifdef ENABLE_ATLANTIS3
#include "cryo/game/atlantis3/atlantis3.h"
#endif

#ifdef ENABLE_ATLANTIS4
#include "cryo/game/atlantis4/atlantis4.h"
#endif

#ifdef ENABLE_ATLANTIS5
#include "cryo/game/atlantis5/atlantis5.h"
#endif

#ifdef ENABLE_AZTEC
#include "cryo/game/aztec/aztec.h"
#endif

#ifdef ENABLE_CHINA
#include "cryo/game/china/china.h"
#endif

#ifdef ENABLE_EGYPT
//#include "cryo/game/egypt/egypt.h"
#endif

#ifdef ENABLE_EGYPT2
#include "cryo/game/egypt2/egypt2.h"
#endif

#ifdef ENABLE_SALAMMBO
#include "cryo/game/salammbo/salammbo.h"
#endif

#ifdef ENABLE_VERSAILLES
#include "cryo/game/versailles/versailles.h"
#endif

#ifdef ENABLE_VERSAILLES2
#include "cryo/game/versailles2/versailles2.h"
#endif

#ifdef ENABLE_ZEROZONE
#include "cryo/game/zerozone/zerozone.h"
#endif

#include "cryo/helpers.h"

#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/error.h"
#include "common/events.h"
#include "common/fs.h"
#include "common/system.h"
#include "common/timer.h"

#include "engines/engine.h"
#include "engines/util.h"

namespace Cryo {

CryoEngine::CryoEngine(OSystem *syst, const CryoGameDescription *gd) :
	Engine(syst), _gameDescription(gd), _game(NULL),
	_random("cryo")
{
	// Setup mixer
	syncSoundSettings();

	// Adding the default directories
	const Common::FSNode gameDataDir(ConfMan.get("path"));

	SearchMan.addSubDirectoryMatching(gameDataDir, "3D");
	SearchMan.addSubDirectoryMatching(gameDataDir, "APC");
	SearchMan.addSubDirectoryMatching(gameDataDir, "FONTES");
	SearchMan.addSubDirectoryMatching(gameDataDir, "HNM");
	SearchMan.addSubDirectoryMatching(gameDataDir, "IMAGES");
	SearchMan.addSubDirectoryMatching(gameDataDir, "INTERF");
	SearchMan.addSubDirectoryMatching(gameDataDir, "INVENT");
	SearchMan.addSubDirectoryMatching(gameDataDir, "LOC");
	SearchMan.addSubDirectoryMatching(gameDataDir, "MUSIC");
	SearchMan.addSubDirectoryMatching(gameDataDir, "PUZZLES");
	SearchMan.addSubDirectoryMatching(gameDataDir, "REF");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SCENAR");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SOUND");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SPF");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SPRITE");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SPRITES");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SPW");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SYC");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SYNC");
	SearchMan.addSubDirectoryMatching(gameDataDir, "WAM");
	SearchMan.addSubDirectoryMatching(gameDataDir, "WARP");

	// Initialize the custom debug levels
	DebugMan.addDebugChannel(kCryoDebugAll, "All", "Debug everything");
	DebugMan.addDebugChannel(kCryoDebugGraphics, "Graphics", "Debug graphics");
	DebugMan.addDebugChannel(kCryoDebugResource, "Resource", "Debug resource management");
	DebugMan.addDebugChannel(kCryoDebugCursor, "Cursor", "Debug cursor handling");
	DebugMan.addDebugChannel(kCryoDebugSound, "Sound", "Debug sound playback");
	DebugMan.addDebugChannel(kCryoDebugMusic, "Music", "Debug music");
	DebugMan.addDebugChannel(kCryoDebugSavegame, "Savegame", "Debug savegames");
	DebugMan.addDebugChannel(kCryoDebugLogic, "Logic", "Debug logic");
	DebugMan.addDebugChannel(kCryoDebugUnknown, "Unknown", "Debug unknown data");
}

CryoEngine::~CryoEngine() {
	SAFE_DELETE(_game);

	// Zero passed pointers
	_gameDescription = NULL;
}

Common::Error CryoEngine::run() {
	// Initialize the graphics
	initGraphics(640, 480, true);

	// Create debugger. It requires GFX to be initialized
	_debugger = new Debugger(this);

	// Create game
	switch (_gameDescription->gameType) {
	default:
		error("[CryoEngine::run] Unknown game type!");
		break;

#ifdef ENABLE_ATLANTIS1
	case Cryo::GameTypeAtlantis:
		error("[CryoEngine::run] Atlantis not supported");
		break;
#endif

#ifdef ENABLE_ATLANTIS2
	case Cryo::GameTypeAtlantis2:
		error("[CryoEngine::run] Atlantis 2 not supported");
		break;
#endif

#ifdef ENABLE_ATLANTIS3
	case Cryo::GameTypeAtlantis3:
		error("[CryoEngine::run] Atlantis 3 not supported");
		break;
#endif

#ifdef ENABLE_ATLANTIS4
	case Cryo::GameTypeAtlantis4:
		error("[CryoEngine::run] Atlantis 4 not supported");
		break;
#endif

#ifdef ENABLE_ATLANTIS5
	case Cryo::GameTypeAtlantis5:
		error("[CryoEngine::run] Atlantis 5 not supported");
		break;
#endif

#ifdef ENABLE_AZTEC
	case Cryo::GameTypeAztec:
		error("[CryoEngine::run] Aztec not supported");
		break;
#endif

#ifdef ENABLE_CHINA
	case Cryo::GameTypeChina:
		_game = new ChinaGame();
		break;
#endif

#ifdef ENABLE_EGYPT
	case Cryo::GameTypeEgypt:
		error("[CryoEngine::run] Egypt not supported");
		break;
#endif

#ifdef ENABLE_EGYPT2
	case Cryo::GameTypeEgypt2:
		error("[CryoEngine::run] Egypt 2 not supported");
		break;
#endif

#ifdef ENABLE_SALAMMBO
	case Cryo::GameTypeSalammbo:
		error("[CryoEngine::run] Salammbo not supported");
		break;
#endif

#ifdef ENABLE_VERSAILLES
	case Cryo::GameTypeVersailles:
		error("[CryoEngine::run] Versailles not supported");
		break;
#endif

#ifdef ENABLE_VERSAILLES2
	case Cryo::GameTypeVersailles2:
		error("[CryoEngine::run] Versailles 2 not supported");
		break;
#endif

#ifdef ENABLE_ZEROZONE
	case Cryo::GameTypeZeroZone:
		error("[CryoEngine::run] Zero zone not supported");
		break;
#endif
	}

	// Initialize game
	_game->init();

	while (!shouldQuit()) {
		if (handleEvents())
			continue;
	}

	return Common::kNoError;
}

void CryoEngine::pollEvents() {
	Common::Event ev;
	_eventMan->pollEvent(ev);

	switch (ev.type) {

	case Common::EVENT_LBUTTONUP:
		// TODO
		break;

	case Common::EVENT_RBUTTONUP:
		// TODO
		break;

	default:
		break;
	}
}

bool CryoEngine::handleEvents() {
	// Make sure all the subsystems have been initialized
	if (!_debugger)
		error("[CryoEngine::handleEvents] Called before the required subsystems have been initialized");

	// Show the debugger if required
	_debugger->onFrame();

	// Handle input
	Common::Event ev;
	while (_eventMan->pollEvent(ev)) {
		switch (ev.type) {

		case Common::EVENT_KEYDOWN:
			// CTRL-D: Attach the debugger
			if ((ev.kbd.flags & Common::KBD_CTRL) && ev.kbd.keycode == Common::KEYCODE_d)
				_debugger->attach();

			_game->keyDown(ev);
			break;

		case Common::EVENT_MAINMENU:
			// Closing the GMM

		case Common::EVENT_LBUTTONUP:
		case Common::EVENT_LBUTTONDOWN:
			_game->mouseLeftButton(ev);
			break;

		case Common::EVENT_RBUTTONUP:
		case Common::EVENT_RBUTTONDOWN:
			_game->mouseRightButton(ev);
			break;

		case Common::EVENT_MOUSEMOVE:
			_game->mouseMove(ev);
			break;

		case Common::EVENT_QUIT:
			quitGame();
			break;

		default:
			break;
		}
	}

	// Update the screen
	_game->update();
	_system->updateScreen();
	_system->delayMillis(50);

	// The event loop may have triggered the quit status. In this case,
	// stop the execution.
	if (shouldQuit())
		return true;

	return false;
}

} // End of namespace LastExpress
