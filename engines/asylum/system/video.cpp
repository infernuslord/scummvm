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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "asylum/system/video.h"

#include "asylum/system/graphics.h"
#include "asylum/system/text.h"

#include "asylum/asylum.h"
#include "asylum/respack.h"
#include "asylum/staticres.h"

namespace Asylum {

Video::Video(AsylumEngine *engine, Audio::Mixer *mixer): _skipVideo(false) {
	Common::Event stopEvent;
	_stopEvents.clear();
	stopEvent.type = Common::EVENT_KEYDOWN;
	stopEvent.kbd.keycode  = Common::KEYCODE_ESCAPE;
	_stopEvents.push_back(stopEvent);

	_smkDecoder = new Graphics::SmackerDecoder(mixer);

	_text = new VideoText(engine);
	_text->loadFont(MAKE_RESOURCE(kResourcePackShared, 57));	// video font
}

Video::~Video() {
	delete _smkDecoder;
	delete _text;
}

void Video::playVideo(int32 videoNumber, bool showSubtitles) {
	char filename[20];
	sprintf(filename, "mov%03d.smk", videoNumber);

	if (!_smkDecoder->loadFile(filename)) {
		_smkDecoder->close();

		error("[Video::playVideo] Invalid video index (%d)", videoNumber);
	}

	bool lastMouseState = g_system->showMouse(false);
	_skipVideo = false;

	if (showSubtitles)
		loadSubtitles(videoNumber);

	int32 x = Common::Rational(g_system->getWidth()  - _smkDecoder->getWidth(),  2).toInt();
	int32 y = Common::Rational(g_system->getHeight() - _smkDecoder->getHeight(), 2).toInt();

	while (!_smkDecoder->endOfVideo() && !_skipVideo) {
		processVideoEvents();
		if (_smkDecoder->needsUpdate()) {
			Graphics::Surface *frame = _smkDecoder->decodeNextFrame();

			if (frame) {
				g_system->copyRectToScreen((byte *)frame->pixels, frame->pitch, x, y, frame->w, frame->h);

				if(showSubtitles) {
					Graphics::Surface *screen = g_system->lockScreen();
					performPostProcessing((byte *)screen->pixels);
					g_system->unlockScreen();
				}

				if (_smkDecoder->hasDirtyPalette())
					_smkDecoder->setSystemPalette();

				g_system->updateScreen();
			}
		}
		g_system->delayMillis(10);
	}


	_smkDecoder->close();
	_subtitles.clear();
	g_system->showMouse(lastMouseState);
}

void Video::performPostProcessing(byte *screen) {
	int32 curFrame = _smkDecoder->getCurFrame();

	// Reset subtitle area, by filling it with zeroes
	memset(screen + 640 * 400, 0, 640 * 80);

	for (uint32 i = 0; i < _subtitles.size(); i++) {
		VideoSubtitle curSubtitle = _subtitles[i];
		if (curFrame >= curSubtitle.frameStart &&
		        curFrame <= curSubtitle.frameEnd) {
			_text->drawMovieSubtitle(screen, curSubtitle.textResourceId);
			break;
		}
	}
}

void Video::loadSubtitles(int32 videoNumber) {
	// Read vids.cap

	char movieToken[10];
	sprintf(movieToken, "[MOV%03d]", videoNumber);

	Common::File subsFile;
	subsFile.open("vids.cap");
	char *buffer = new char[(uint)subsFile.size()];
	subsFile.read(buffer, (uint32)subsFile.size());
	subsFile.close();

	char *start = strstr(buffer, movieToken);
	char *line = 0;

	if (start) {
		start += 20; // skip token, newline and "CAPTION = "

		uint32 count = strcspn(start, "\r\n");
		line = new char[count + 1];

		strncpy(line, start, count);
		line[count] = 0;

		char *tok = strtok(line, " ");

		while (tok) {
			VideoSubtitle newSubtitle;
			newSubtitle.frameStart = atoi(tok);

			tok = strtok(NULL, " ");
			if (!tok)
				error("[Video::loadSubtitles] Invalid subtitle (frame end missing)!");

			newSubtitle.frameEnd = atoi(tok);

			tok = strtok(NULL, " ");
			if (!tok)
				error("[Video::loadSubtitles] Invalid subtitle (resource id missing)!");

			newSubtitle.textResourceId = (ResourceId)(atoi(tok) + video_subtitle_resourceIds[videoNumber]);

			tok = strtok(NULL, " ");

			_subtitles.push_back(newSubtitle);
		}

		delete [] line;
	}

	delete [] buffer;
}

void Video::processVideoEvents() {
	Common::Event curEvent;
	while (g_system->getEventManager()->pollEvent(curEvent)) {
		if (curEvent.type == Common::EVENT_RTL || curEvent.type == Common::EVENT_QUIT) {
			_skipVideo = true;
		}

		for (Common::List<Common::Event>::const_iterator iter = _stopEvents.begin(); iter != _stopEvents.end(); ++iter) {
			if (curEvent.type == iter->type) {
				if (iter->type == Common::EVENT_KEYDOWN || iter->type == Common::EVENT_KEYUP) {
					if (curEvent.kbd.keycode == iter->kbd.keycode) {
						_skipVideo = true;
						break;
					}
				} else {
					_skipVideo = true;
					break;
				}
			}
		}
	}
}


VideoText::VideoText(AsylumEngine *engine) : _vm(engine) {
	_curFontFlags = 0;
	_fontResource = NULL;
}

VideoText::~VideoText() {
	delete _fontResource;

	// Zero-out passed pointers
	_vm = NULL;
}

void VideoText::loadFont(ResourceId resourceId) {
	delete _fontResource;

	_fontResource = new GraphicResource(_vm, resourceId);

	if (resourceId != kResourceNone) {
		// load font flag data
		_curFontFlags = Common::Rational(_fontResource->getFlags(), 16).toInt() & 0x0F;
	}
}

void VideoText::drawMovieSubtitle(byte *screenBuffer, ResourceId resourceId) {
	Common::String textLine[4];
	Common::String tmpLine;
	int32 curLine = 0;
	ResourceEntry *textRes = getResource()->get(resourceId);
	char *text = strdup((const char *)textRes->data);	// for strtok
	char *tok  = strtok(text, " ");
	int32 startY  = 420; // starting y for up to 2 subtitles
	int32 spacing = 30;  // spacing for up to 2 subtitles

	// Videos can have up to 4 lines of text
	while (tok) {
		tmpLine += tok;
		tmpLine += " ";
		if (getTextWidth(tmpLine.c_str()) > 640) {
			tmpLine = tok;
			curLine++;
			if (curLine >= 2) {
				startY  = 410; // starting Y for 3 subtitles
				spacing = 20;  // spacing for 3-4 subtitles
			}
			if (curLine >= 3) {
				startY = 402;  // starting Y for 4 subtitles
			}
		}
		textLine[curLine] += tok;
		textLine[curLine] += " ";
		tok = strtok(NULL, " ");
	}

	for (int32 i = 0; i < curLine + 1; i++) {
		int32 textWidth = getTextWidth(textLine[i].c_str());
		drawText(screenBuffer, (int16)Common::Rational(640 - textWidth, 2).toInt(), (int16)(startY + i * spacing), textLine[i].c_str());
	}

	free(text);
}

int32 VideoText::getTextWidth(const char *text) {
	if (!_fontResource)
		error("[VideoText::getTextWidth] Video text resources not initialized properly!");

	int32 width = 0;

	while (*text) {
		GraphicFrame *font = _fontResource->getFrame((uint8)*text);
		width += font->surface.w + font->x - _curFontFlags;

		text++;
	}

	return width;
}

void VideoText::drawText(byte *screenBuffer, int16 x, int16 y, const char *text) {
	if (!_fontResource)
		error("[VideoText::drawText] Video text resources not initialized properly!");

	while (*text) {
		GraphicFrame *fontLetter = _fontResource->getFrame((uint8)*text);
		copyToVideoFrame(screenBuffer, fontLetter, x, y + fontLetter->y);
		x += (int16)(fontLetter->surface.w + fontLetter->x - _curFontFlags);
		text++;
	}
}

void VideoText::copyToVideoFrame(byte *screenBuffer, GraphicFrame *frame, int32 x, int32 y) const {
	uint16 h = frame->surface.h;
	uint16 w = frame->surface.w;
	int32 screenBufferPitch = 640;
	byte *buffer = (byte *)frame->surface.pixels;
	byte *dest   = screenBuffer + y * screenBufferPitch + x;

	while (h--) {
		memcpy(dest, buffer, w);
		dest   += screenBufferPitch;
		buffer += frame->surface.w;
	}
}

} // end of namespace Asylum