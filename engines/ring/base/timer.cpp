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
 * $URL$
 * $Id$
 *
 */

#include "ring/base/timer.h"

#include "ring/helpers.h"

namespace Ring {

#pragma region Timer

Timer::Timer(TimerId id, uint32 elapseTime): BaseId(id), _elapseTime(elapseTime) {
	_fired = 0;
	_tickStart = g_system->getMillis();

	// TODO Start timer
}

Timer::~Timer() {
	// TODO Stop timer
}

#pragma endregion

#pragma region TimerHandler

TimerHandler::TimerHandler() {
}

TimerHandler::~TimerHandler() {
	CLEAR_ARRAY(Timer, _timers);
}

void TimerHandler::start(TimerId id, uint32 elapseTime) {
	if (_timers.has(id))
		error("[TimerHandler::start] Timer with that id already exists (%d)", id);

	_timers.push_back(new Timer(id, elapseTime));
}

void TimerHandler::stop(TimerId id) {
	if (!_timers.has(id))
		error("[TimerHandler::stop] Timer with that id doesn't exist (%d)", id);

	_timers.remove_at(_timers.getIndex(id));
}

void TimerHandler::stopAll() {
	CLEAR_ARRAY(Timer, _timers);
}

bool TimerHandler::has(TimerId id) {
	return _timers.has(id);
}

void TimerHandler::incrementFiredCount(TimerId id) {
	if (!_timers.has(id))
		return;

	_timers.get(id)->incrementFiredCount();
}

#pragma endregion

} // End of namespace Ring
