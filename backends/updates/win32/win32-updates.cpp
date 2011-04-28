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

#if defined(WIN32) && defined(USE_UPDATES)

#include "backends/updates/win32/win32-updates.h"

#include <winsparkle.h>

Win32UpdateManager::Win32UpdateManager() {
	// Set appcast url and initialize framework
	win_sparkle_set_appcast_url(getAppcastUrl().c_str());
	win_sparkle_init();
}

Win32UpdateManager::~Win32UpdateManager() {
	win_sparkle_cleanup();
}

void Win32UpdateManager::checkForUpdates() {
	win_sparkle_check_update_with_ui();
}

void Win32UpdateManager::setAutomaticallyChecksForUpdates(UpdateManager::UpdateState state) {
	// FIXME: Not supported by WinSparkle yet
}

UpdateManager::UpdateState Win32UpdateManager::getAutomaticallyChecksForUpdates() {
	// FIXME: Not supported by WinSparkle yet
	return kUpdateStateNotSupported;
}

void Win32UpdateManager::setUpdateCheckInterval(UpdateInterval interval) {
	// FIXME: Not supported by WinSparkle yet
}

UpdateManager::UpdateInterval Win32UpdateManager::getUpdateCheckInterval() {
	// FIXME: Not supported by WinSparkle yet
	return kUpdateIntervalNotSupported;
}

#endif
