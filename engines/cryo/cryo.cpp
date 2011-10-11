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

CryoEngine::CryoEngine(OSystem *syst, const ADGameDescription *gd) :
	Engine(syst), _gameDescription(gd),
	_random("cryo")
{
	// Setup mixer
	syncSoundSettings();

	// Adding the default directories
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "data");

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

	// Zero passed pointers
	_gameDescription = NULL;
}

Common::Error CryoEngine::run() {
	// Initialize the graphics
	const Graphics::PixelFormat dataPixelFormat(2, 5, 5, 5, 0, 10, 5, 0, 0);
	initGraphics(640, 480, true, &dataPixelFormat);

	// We do not support color conversion
	if (_system->getScreenFormat() != dataPixelFormat)
		return Common::kUnsupportedColorMode;

	// Create debugger. It requires GFX to be initialized
	_debugger = new Debugger(this);



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

		break;

	case Common::EVENT_RBUTTONUP:

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
			break;

		case Common::EVENT_MAINMENU:
			// Closing the GMM

		case Common::EVENT_LBUTTONUP:
		case Common::EVENT_LBUTTONDOWN:

			break;

		case Common::EVENT_RBUTTONUP:
		case Common::EVENT_RBUTTONDOWN:

			break;

		case Common::EVENT_MOUSEMOVE:

			break;

		case Common::EVENT_QUIT:
			quitGame();
			break;

		default:
			break;
		}
	}

	// Update the screen
	_system->updateScreen();
	_system->delayMillis(50);

	// The event loop may have triggered the quit status. In this case,
	// stop the execution.
	if (shouldQuit())
		return true;

	return false;
}

///////////////////////////////////////////////////////////////////////////////////
/// Misc Engine
///////////////////////////////////////////////////////////////////////////////////
bool CryoEngine::hasFeature(EngineFeature f) const {
	return (f == kSupportsRTL);
}

} // End of namespace LastExpress
