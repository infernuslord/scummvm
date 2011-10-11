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

#include "engines/engine.h"

#include "graphics/pixelformat.h"

struct ADGameDescription;

/**
 * This is the namespace of the Cryo engine.
 *
 * Maintainers:
 *  littleboy
 *
 * Supported games:
 *  -
 */
namespace Cryo {

class CryoEngine : public Engine {
public:
	CryoEngine(OSystem *syst, const ADGameDescription *gd);
	~CryoEngine();

	// Event handling
	bool handleEvents();
	void pollEvents();

	// Misc
	Common::RandomSource getRandom() const {return _random; }
	bool isDemo() const;

protected:
	// Engine APIs
	Common::Error run();
	virtual bool hasFeature(EngineFeature f) const;
	virtual Debugger *getDebugger() { return _debugger; }

private:
	const ADGameDescription *_gameDescription;
	Graphics::PixelFormat _pixelFormat;

	// Misc
	Debugger *_debugger;
	Common::RandomSource _random;
};

} // End of namespace Cryo

#endif // CRYO_H
