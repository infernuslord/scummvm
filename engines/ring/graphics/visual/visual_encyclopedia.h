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

class Hotspot;
class ImageHandle;
class Movie2;
class Text;

enum Facetype {
	kFaceTypeArial   = 0,
	kFaceTypeCourier = 1,
	kFaceTypeImpact  = 2
};

class EncyclopediaEntry {
public:
	EncyclopediaEntry();
	~EncyclopediaEntry() {}

	uint32 load(const char *buffer, uint32 size);

	const Common::String getFilename() { return _filename; }

private:
	uint32         _field_0;
	Common::String _label;
	Common::String _filename;
	uint32         _field_C;
	uint32         _field_10;
	Facetype       _facetype;
	uint32         _field_18;
	uint32         _field_1C;
	uint32         _height;
	bool           _smallWeight;
	bool           _italic;
	uint32         _field_2C;
	uint32         _field_30;
	uint32         _field_34;
	uint32         _field_38;
};

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
	bool                                _isLoaded;
	ArchiveType                         _archiveType;
	Common::Array<Hotspot *>            _hotspots;
	Common::Array<Text *>               _texts;
	uint32                              _field_17;
	ImageHandle                        *_imageArrowDown_dis;
	ImageHandle                        *_imageArrowDown_hlt;
	ImageHandle                        *_imageArrowDown_nor;
	ImageHandle                        *_imageArrowUp_dis;
	ImageHandle                        *_imageArrowUp_hlt;
	ImageHandle                        *_imageArrowUp_nor;
	ImageHandle                        *_image7;
	ImageHandle                        *_imageSlide;
	ImageHandle                        *_imageSlider;
	uint32                              _field_3F;
	uint32                              _field_43;
	uint32                              _field_47;
	uint32                              _field_4B;
	uint32                              _field_4F;
	uint32                              _field_50;
	uint32                              _field_54;
	float                               _field_58;
	float                               _top;
	uint32                              _field_60;
	uint32                              _field_64;
	uint32                              _field_68;
	uint32                              _field_6C;
	/* missing fields */
	uint32                              _field_80;
	uint32                              _field_84;
	uint32                              _tickCount;
	uint32                              _field_90;
	uint32                              _field_94;
	Movie2                             *_movie;
	uint32                              _field_9C;
	uint32                              _field_A0;
	uint32                              _field_A4;
	Text                               *_text;
	Hotspot                            *_hotspot;
	Common::String                      _filename;
	uint32                              _field_B4;
	uint32                              _field_B8;
	uint32                              _field_BC;
	uint32                              _field_C0;
	uint32                              _field_C4;
	uint32                              _field_C8;
	bool                                _field_CC;
	bool                                _fonts[285];
	uint32                              _field_541;
	uint32                              _field_545;
	uint32                              _field_549;
	uint32                              _soundId;
	uint32                              _field_551;
	Common::Array<EncyclopediaEntry *>  _entries;

	bool load();
	bool loadEntries(const Common::String &filename);
	void previous(uint32 y);
	void next(uint32 y);

	void addHotspots();
	void addHotspot(Id target, Text *text, CursorId cursorId);
	void setHotspot();

	Id addSound(CursorId cursorId);

	void playMovie(uint32 entryIndex);
	void stopMovie(uint32 soundIndex);

	FontId getFontId(Facetype faceType, int height, bool smallWeight, bool italic, bool underline);
	void drawText(Text *text);
};

} // End of namespace Ring

#endif // RING_VISUAL_ENCYCLOPEDIA_H
