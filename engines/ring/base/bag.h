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

#ifndef RING_BAG_H
#define RING_BAG_H

#include "ring/shared.h"

#include "common/rect.h"

namespace Ring {

class Application;
class Hotspot;
class Image;
class ImageHandle;
class Object;
class Text;

class Bag : public Common::Serializable {
public:
	Bag();
	~Bag();

	// Initialization
	void initHotspots();

	void setOrigin(const Common::Point &point) { _origin = point; }
	void sub_417D40(uint32 a1, uint32 a2, uint32 a3, uint32 a4);
	void setBackgroundOffset(const Common::Point &point) { _backgroundOffset = point; }
	void sub_417D80(uint32 a1, uint32 a2, uint32 a3, uint32 a4);
	void sub_417DA0(uint32 a1, uint32 a2, uint32 a3, uint32 a4);
	void sub_417DD0(uint32 a1);
	void sub_417DE0(uint32 a1, uint32 a2);
	void sub_417E00();
	uint32 checkHotspotClick(const Common::Point &point);
	uint32 checkHotspot(const Common::Point &point);
	void draw();
	void sub_419280(uint32 a1);
	void sub_4192A0(uint32 a1, uint32 a2);
	void sub_4192C0(uint32 a1, uint32 a2);
	void initialize();
	void reset();

	void loadBackground(Common::String filename1, Common::String filename2, Common::String filename3, Common::String filename4, Common::String filename5, Common::String filename6, Common::String filename7, Common::String filename8, ArchiveType filetype, bool loadAdditionalImages = false);

	// Enable/Disable
	void enable();
	void disable();

	// Management
	void add(ObjectId objectId);
	void remove(ObjectId objectId);
	void removeAll();
	bool has(ObjectId objectId);

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

	// Accessors
	bool isInitialized() { return _isInitialized; }
	void setClickedObject(ObjectId object) { _clickedObject = object; }
	ObjectId getClickedObject() { return _clickedObject; }

	bool getRotationFre() { return _fre; }
	void setRotationFre(bool fre) { _fre = fre; }

private:
	// Bag data
	AssociativeArray<Object *>   _objects;
	Common::Array<ImageHandle *> _images;
	Common::Array<Hotspot*>      _hotspots;
	uint32      _field_C;
	uint32      _field_10;
	uint32      _field_14;
	uint32      _field_18;
	Common::Point _origin;
	uint32      _field_24;
	uint32      _field_28;
	uint32      _objectCount;
	Common::Point _backgroundOffset;
	Image      *_background;
	Image      *_image2;
	Image      *_image3;
	Image      *_image4;
	uint32      _field_48;
	uint32      _field_4C;
	uint32      _field_50;
	uint32      _field_54;
	uint32      _field_58;
	uint32      _field_5C;
	uint32      _field_60;
	uint32      _field_64;
	Image      *_image5;
	Image      *_image6;
	Image      *_image7;
	uint32      _field_74;
	uint32      _field_78;
	uint32      _field_7C;
	uint32      _field_80;
	Image      *_image8;
	uint32      _field_88;
	uint32      _field_8C;
	uint32      _field_90;
	bool        _isInitialized;
	ObjectId    _clickedObject;
	uint32      _field_99;
	uint32      _tickInterval;
	uint32      _ticks;
	Text       *_text;
	FontId      _fontId;
	Color       _foregroundColor;
	Color       _backgroundColor;
	uint32      _field_C5;
	ArchiveType _archiveType;
	Image      *_imageErdaGun;
	Image      *_imageErdaGur;
	bool        _enabled;

	// Current rotation fre
	bool _fre;

	// Drawing flags
	bool _drawImage8;
	bool _drawImageErdaGur;

	void loadImage(Common::String filename, Image **image, ArchiveType archiveType) const;

	Hotspot *getHotspot(const Common::Point &point);
};

} // End of namespace Ring

#endif // RING_BAG_H