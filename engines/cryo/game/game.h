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

#ifndef CRYO_GAME_H
#define CRYO_GAME_H

#include "common/events.h"

namespace Cryo {

class Game {
public:
	virtual ~Game() {}

	virtual void init() = 0;
	virtual void update() = 0;

	// Event handling
	virtual void keyDown(const Common::Event &evt) {}
	virtual void mouseLeftButton(const Common::Event &evt) {}
	virtual void mouseRightButton(const Common::Event &evt) {}
	virtual void mouseMove(const Common::Event &evt) {}

protected:

};

} // End of namespace Cryo

#endif // CRYO_GAME_H
