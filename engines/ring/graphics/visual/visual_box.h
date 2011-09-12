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

#ifndef RING_VISUAL_BOX_H
#define RING_VISUAL_BOX_H

#include "ring/graphics/visual/visual.h"

namespace Ring {

class Hotspot;
class ImageHandle;
class Text;

class VisualObjectBox : public Visual {
public:
	VisualObjectBox(Id id);
	~VisualObjectBox();

	virtual void draw();
	virtual uint32 handleLeftButtonUp(const Common::Point &point);
	virtual uint32 handleUpdate(const Common::Point &point);
	virtual uint32 handleLeftButtonDown(Common::Point point);
	virtual void alloc();
	virtual void dealloc();

	void init(const Common::String &name, ArchiveType archiveType);
	void setParameters(uint32 a2, uint32 a3, uint32 a4);
	void hide();

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

private:
	struct Data {
		uint32 size;
		char   filename[255];

		Data() {
			size = 0;
			memset(&filename, 0, sizeof(filename));
		}
	};

	Data                    *_data;
	uint32                   _field_11;
	uint32                   _field_15;
	bool                     _isLoaded;
	ArchiveType              _archiveType;
	Common::Array<Hotspot *> _hotspots;
	Common::Array<Text *>    _texts;
	Common::Array<uint32 *>  _field_23;
	Common::Array<uint32 *>  _field_27;
	Common::Array<uint32 *>  _field_2B;
	Text                    *_name;
	ImageHandle             *_imageKeywords;
	uint32                   _field_37;
	uint32                   _size;
	char                     _filename[255];
	uint32                   _field_13E;
	uint32                   _field_142;
	uint32                   _field_146;
	uint32                   _field_14A;
	uint32                   _field_14E;
	uint32                   _field_152;
	Common::Point            _point;
	bool                     _field_15E;

	bool hasImage() { return true; }
};

} // End of namespace Ring

#endif // RING_VISUAL_BOX_H
