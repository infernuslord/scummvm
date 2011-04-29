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
	if (state == kUpdateStateNotSupported)
		return;

	win_sparkle_set_automatic_check_for_updates(state == kUpdateStateEnabled ? 1 : 0);
}

Common::UpdateManager::UpdateState Win32UpdateManager::getAutomaticallyChecksForUpdates() {
	switch (win_sparkle_get_automatic_check_for_updates()) {
	default:
		break;

	case 0:
		return kUpdateStateDisabled;

	case 1:
		return kUpdateStateEnabled;
	}

	return kUpdateStateNotSupported;
}

void Win32UpdateManager::setUpdateCheckInterval(UpdateInterval interval) {
	if (interval == kUpdateIntervalNotSupported)
		return;

	win_sparkle_set_update_check_interval(interval);
}

Common::UpdateManager::UpdateInterval Win32UpdateManager::getUpdateCheckInterval() {
	// This is kind of a hack but necessary, as the value stored by WinSparkle might have been changed outside of ScummVM
	// (in which case we return the default interval of one day
	switch (win_sparkle_get_update_check_interval()) {
	default:
		break;

	case kUpdateIntervalOneDay:
		return kUpdateIntervalOneDay;

	case kUpdateIntervalOneWeek:
		return kUpdateIntervalOneWeek;

	case kUpdateIntervalOneMonth:
		return kUpdateIntervalOneMonth;
	}

	// Return the default value (one day)
	return kUpdateIntervalOneDay;
}

#endif
