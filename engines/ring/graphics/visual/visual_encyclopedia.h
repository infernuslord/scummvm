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

#ifndef RING_VISUAL_ENCYCLOPEDIA_H
#define RING_VISUAL_ENCYCLOPEDIA_H

#include "ring/graphics/visual/visual.h"

namespace Ring {

class VisualObjectEncyclopedia : public Visual {
public:
	VisualObjectEncyclopedia(Id id);
	~VisualObjectEncyclopedia();

	virtual void draw();
	virtual uint32 handleLeftButtonUp(const Common::Point &point);
	virtual uint32 handleUpdate(const Common::Point &point);
	virtual uint32 handleLeftButtonDown(Common::Point point);
	virtual bool handleKey(Common::KeyCode key);
	virtual void alloc();
	virtual void dealloc();

	void init(const Common::String &name, ArchiveType archiveType);
	void setParameters(uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8);
	void showFile(const Common::String &filename);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

private:

};

} // End of namespace Ring

#endif // RING_VISUAL_ENCYCLOPEDIA_H
