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

#include "ring/graphics/visual/visual_box.h"

namespace Ring {

VisualObjectBox::VisualObjectBox(Id id) : Visual(id) {
	error("[VisualObjectBox] Not implemented");
}

VisualObjectBox::~VisualObjectBox() {
	error("[~VisualObjectBox] Not implemented");
}

void VisualObjectBox::draw() {
	error("[VisualObjectBox::init] Not implemented");
}

uint32 VisualObjectBox::handleLeftButtonUp(const Common::Point &point) {
	error("[VisualObjectBox::handleLeftButtonUp] Not implemented");
}

uint32 VisualObjectBox::handleUpdate(const Common::Point &point) {
	error("[VisualObjectBox::handleUpdate] Not implemented");
}

uint32 VisualObjectBox::handleLeftButtonDown(Common::Point point) {
	error("[VisualObjectBox::handleLeftButtonDown] Not implemented");
}

void VisualObjectBox::alloc() {
	error("[VisualObjectBox::alloc] Not implemented");
}

void VisualObjectBox::dealloc() {
	error("[VisualObjectBox::dealloc] Not implemented");
}

void VisualObjectBox::init(const Common::String &name, ArchiveType archiveType) {
	error("[VisualObjectBox::init] Not implemented");
}

void VisualObjectBox::setParameters(uint32 a2, uint32 a3, uint32 a4) {
	error("[VisualObjectBox::setParameters] Not implemented");
}

void VisualObjectBox::hide() {
	error("[VisualObjectBox::hide] Not implemented");
}

void VisualObjectBox::saveLoadWithSerializer(Common::Serializer &s) {
	error("[VisualObjectBox::saveLoadWithSerializer] Not implemented");
}

} // End of namespace Ring
