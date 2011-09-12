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

/**
 * Visual object box
 *
 * This shows the dialog options when talking to people in the game
 */
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
	void setParameters(Id keywordId, const Common::Point &point);
	void hide();

	// Serializable
	void saveLoadWithSerializer(Common::Serializer &s);

private:
	struct Keyword {
		Id id;
		Common::String name;

		Keyword() {
			id = 0;
		}

		Keyword(const Keyword& keyword) {
			id   = keyword.id;
			name = keyword.name;
		}
	};

	struct DialogList : BaseObject {
		Common::Array<Keyword *> keywords;

		DialogList() : BaseObject(0) {}

		DialogList(Id keywordId) : BaseObject(keywordId) {}

		~DialogList();
	};

	Keyword                         *_keyword;
	Keyword                         *_currentKeyword;
	uint32                           _field_15;
	bool                             _isLoaded;
	ArchiveType                      _archiveType;
	Common::Array<Hotspot *>         _hotspots;
	Common::Array<Text *>            _options;
	Common::Array<Keyword *>         _keywords;
	Common::Array<uint32 *>          _field_27;
	AssociativeArray<DialogList *>   _dialogs;
	Text                            *_name;
	ImageHandle                     *_imageKeywords;
	uint32                           _field_37;
	uint32                           _dialogId;
	Common::String                   _dialogName;
	bool                             _isSetup;
	Id                               _keywordId1;
	Id                               _keywordId2;
	Id                               _keywordId3;
	Id                               _keywordId4;
	Id                               _keywordId;
	Common::Point                    _point;
	bool                             _showOptions;

	bool hasImage() { return true; }
	void reset();

	void setupOptions();
	void loadKeyword(Id keywordId);
	void addHotspot(Text *text, uint32 keywordIndex);
	void sub_4830A0(Id keywordId);
	void playDialog(uint32 keywordIndex, Id keywordId);
	void adjustOptions();
	void ignoreKeyword();
	bool isKeywordLoaded(Id keywordId);

};

} // End of namespace Ring

#endif // RING_VISUAL_BOX_H
