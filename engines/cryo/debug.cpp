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
 */

#include "cryo/debug.h"

#include "cryo/data/graphics/sprite.h"
#include "cryo/data/graphics/hnm.h"

#include "cryo/data/sound/apc.h"
#include "cryo/data/sound/synchro.h"
#include "cryo/data/sound/zik.h"

#include "cryo/cryo.h"

#include "audio/audiostream.h"
#include "audio/decoders/wave.h"
#include "common/debug-channels.h"
#include "common/file.h"
#include "common/system.h"

namespace Cryo {

Debugger::Debugger(CryoEngine *engine) : _engine(engine) {

	//////////////////////////////////////////////////////////////////////////
	// Register the debugger commands

	// General
	DCmd_Register("help",      WRAP_METHOD(Debugger, cmdHelp));

	DCmd_Register("hnm",       WRAP_METHOD(Debugger, cmdHnm));
	DCmd_Register("music",     WRAP_METHOD(Debugger, cmdMusic));
	DCmd_Register("sync",      WRAP_METHOD(Debugger, cmdSync));
	DCmd_Register("sound",     WRAP_METHOD(Debugger, cmdSound));
	DCmd_Register("sprite",    WRAP_METHOD(Debugger, cmdSprite));
}

Debugger::~Debugger() {
	DebugMan.clearAllDebugChannels();

	// Zero passed pointers
	_engine = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Debugger commands
//////////////////////////////////////////////////////////////////////////
bool Debugger::cmdHelp(int, const char **) {
	DebugPrintf("Debug flags\n");
	DebugPrintf("-----------\n");
	DebugPrintf(" debugflag_list - Lists the available debug flags and their status\n");
	DebugPrintf(" debugflag_enable - Enables a debug flag\n");
	DebugPrintf(" debugflag_disable - Disables a debug flag\n");
	DebugPrintf("\n");
	DebugPrintf("Commands\n");
	DebugPrintf("--------\n");
	DebugPrintf("list - List files inside an archive\n");
	DebugPrintf("hnm   - Show video\n");
	DebugPrintf("music - Play music\n");
	DebugPrintf("sync  - Show sync information\n");
	DebugPrintf("sound - Play sound\n");
	DebugPrintf("sprite - Show a sprite\n");
	DebugPrintf("\n");
	return true;
}

bool Debugger::cmdHnm(int argc, const char **argv) {
	if (argc == 2) {

		// Get sprite name
		Common::String name(const_cast<char *>(argv[1]));
		if (!name.contains('.'))
			name += ".HNM";

		Hnm *hnm = new Hnm();
		hnm->loadFile(name);

		// Show information
		DebugPrintf("%s\n\n", hnm->toString().c_str());

		// TODO Play video

		const Graphics::Surface *surface = hnm->decodeNextFrame();
		g_system->fillScreen(0);
		g_system->copyRectToScreen(surface->getBasePtr(0, 0), 640, 0, 0, 640, 480);
		g_system->updateScreen();

		delete hnm;

	} else {
		DebugPrintf("Syntax: hnm <filename>\n");
	}
	return true;
}

bool Debugger::cmdMusic(int argc, const char **argv) {
	if (argc == 2) {

		// Get music name
		Common::String filename(const_cast<char *>(argv[1]));
		if (!Common::File::exists(filename)) {
			DebugPrintf("Cannot find file %s!\n", filename.c_str());
			return true;
		}

		// Stop all playing sounds
		_engine->_system->getMixer()->stopAll();

		filename.toLowercase();

		// Open sound file and play
		if (filename.hasSuffix(".zik")) {
			Zik *music = new Zik(filename);
			music->play();
			delete music;
		} else if (filename.hasSuffix(".wav")) {
			Common::SeekableReadStream *stream = SearchMan.createReadStreamForMember(filename);
			if (!stream) {
				DebugPrintf("Cannot open stream to wav file (%s)\n", filename.c_str());
				return true;
			}

			Audio::RewindableAudioStream *waveStream = Audio::makeWAVStream(stream, DisposeAfterUse::YES);
			_engine->_system->getMixer()->playStream(Audio::Mixer::kMusicSoundType, &_soundHandle, (Audio::AudioStream *)waveStream);
		}

	} else {
		DebugPrintf("Syntax: music <filename>\n");
	}
	return true;
}

bool Debugger::cmdSync(int argc, const char **argv) {
	if (argc == 2) {

		// Get name
		Common::String name(const_cast<char *>(argv[1]));
		if (!name.contains('.'))
			name += ".syc";

		Synchro *sync = new Synchro(name);

		DebugPrintf("%s\n", sync->toString().c_str());

		delete sync;

	} else {
		DebugPrintf("Syntax: sync <filename>\n");
	}
	return true;
}

bool Debugger::cmdSound(int argc, const char **argv) {
	if (argc == 2) {

		// Get sound name
		Common::String filename(const_cast<char *>(argv[1]));
		if (!Common::File::exists(filename)) {
			DebugPrintf("Cannot find file %s!\n", filename.c_str());
			return true;
		}

		// Stop all playing sounds
		_engine->_system->getMixer()->stopAll();

		filename.toLowercase();

		// Open sound file and play
		if (filename.hasSuffix(".apc")) {
			Apc *apc = new Apc(filename);
			apc->play();
			delete apc;
		} else if (filename.hasSuffix(".wav")) {
			Common::SeekableReadStream *stream = SearchMan.createReadStreamForMember(filename);
			if (!stream) {
				DebugPrintf("Cannot open stream to wav file (%s)\n", filename.c_str());
				return true;
			}

			Audio::RewindableAudioStream *waveStream = Audio::makeWAVStream(stream, DisposeAfterUse::YES);
			_engine->_system->getMixer()->playStream(Audio::Mixer::kPlainSoundType, &_soundHandle, (Audio::AudioStream *)waveStream);
		}

	} else {
		DebugPrintf("Syntax: sound <filename>\n");
	}
	return true;
}

bool Debugger::cmdSprite(int argc, const char **argv) {
	if (argc == 2) {

		// Get sprite name
		Common::String name(const_cast<char *>(argv[1]));
		if (!name.contains('.'))
			name += ".SPR";

		Sprite *sprite = new Sprite(name);
		//sprite->draw();

		delete sprite;

	} else {
		DebugPrintf("Syntax: sprite <filename>\n");
	}
	return true;
}

} // End of namespace Cryo