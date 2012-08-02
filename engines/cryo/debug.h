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

#ifndef CRYO_DEBUG_H
#define CRYO_DEBUG_H

#include "gui/debugger.h"

#include "audio/mixer.h"

#include "common/debug.h"

namespace Cryo {

enum {
	kCryoDebugAll      = 1 << 0,
	kCryoDebugGraphics = 1 << 1,
	kCryoDebugResource = 1 << 2,
	kCryoDebugCursor   = 1 << 3,
	kCryoDebugSound    = 1 << 4,
	kCryoDebugMusic    = 1 << 5,
	kCryoDebugSavegame = 1 << 6,
	kCryoDebugLogic    = 1 << 7,
	kCryoDebugUnknown  = 1 << 8
	// the current limitation is 32 debug levels (1 << 31 is the last one)
};

class CryoEngine;

class Debugger : public GUI::Debugger {
public:
	Debugger(CryoEngine *engine);
	~Debugger();

private:
	CryoEngine *_engine;

	bool cmdHelp(int argc, const char **argv);

	// Data
	bool cmdHnm(int argc, const char **argv);
	bool cmdMusic(int argc, const char **argv);
	bool cmdSync(int argc, const char **argv);
	bool cmdSound(int argc, const char **argv);
	bool cmdSprite(int argc, const char **argv);

	// Misc
	Audio::SoundHandle _soundHandle;
};

} // End of namespace LastExpress

#endif // CRYO_DEBUG_H