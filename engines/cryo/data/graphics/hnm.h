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

#ifndef CRYO_HNM_H
#define CRYO_HNM_H

#include "video/video_decoder.h"

#include "graphics/pixelformat.h"
#include "graphics/surface.h"

#include "common/str.h"

namespace Cryo {

#define ID_HNM4 MKTAG('H','N','M','4')
#define ID_HNM6 MKTAG('H','N','M','6')

class Hnm : public Video::VideoDecoder {
public:
	Hnm();
	~Hnm();

	bool loadStream(Common::SeekableReadStream *stream);
	void close();

	const Graphics::Surface *decodeNextFrame();

	bool isVideoLoaded() const { return _fileStream != 0; }

	uint16 getWidth() const { return _header->getWidth(); }
	uint16 getHeight() const { return _header->getHeight(); }
	Graphics::PixelFormat getPixelFormat() const { return _header->getPixelFormat(); }
	uint32 getFrameCount() const { return _header->getFrameCount(); }
	uint32 getTimeToNextFrame() const;

	Common::String toString();

private:
	enum Chunk {

		// HNM4
		kChunkPL = 0x5040, // Palette
		kChunkIZ = 0x495A, // Keyframe
		kChunkIU = 0x4955, // Interframe
		kChunkSD = 0x5344, // Sound data

		// HNM6
		kChunkAA = 0x4141, // Audio
		kChunkBB = 0x4242, // Audio continuation
		kChunkIX = 0x4958  // Video frame
	};

	struct Header {
		uint32 signature;
		byte field_4;
		byte field_5;
		byte field_6;
		byte bpp;

		Header() {
			signature = 0;
			field_4   = 0;
			field_5   = 0;
			field_6   = 0;
			bpp       = 0;
		}

		virtual void load(Common::SeekableReadStream *stream);

		virtual uint16 getWidth() const { return 0; }
		virtual uint16 getHeight() const { return 0; }
		virtual Graphics::PixelFormat getPixelFormat() const { return Graphics::PixelFormat::createFormatCLUT8(); }
		virtual uint32 getFrameCount() const  { return 0; }

		virtual Common::String toString() const;
	};

	struct Headerv4 : Header {
		uint16 width;
		uint16 height;
		uint32 filesize;
		uint32 frames;
		uint32 tabOffset;
		uint16 bits;
		uint16 channels;
		uint32 framesize;
		char   creator[17];
		char   copyright[17];

		Headerv4() {
			width     = 0;
			height    = 0;
			filesize  = 0;
			frames    = 0;
			tabOffset = 0;
			bits      = 0;
			channels  = 0;
			framesize = 0;
			memset(creator, 0, sizeof(creator));
			memset(copyright, 0, sizeof(copyright));
		}

		void load(Common::SeekableReadStream *stream);

		uint16 getWidth() const { return width; }
		uint16 getHeight() const { return height; }
		Graphics::PixelFormat getPixelFormat() const { return Graphics::PixelFormat::createFormatCLUT8(); };
		uint32 getFrameCount() const { return frames; }

		Common::String toString() const;
	};

	struct Headerv6 : Header {
		uint16 width;
		uint16 height;
		uint32 filesize;
		uint32 frames;
		uint32 reserved;
		uint32 maxBuffer;   ///< Max buffer size (usually 0x20000)
		uint32 maxChunk;    ///< Max frame chunk size
		char   creator[17];
		char   copyright[17];

		Headerv6() {
			width     = 0;
			height    = 0;
			filesize  = 0;
			frames    = 0;
			reserved  = 0;
			maxBuffer = 0;
			maxChunk  = 0;
			memset(creator, 0, sizeof(creator));
			memset(copyright, 0, sizeof(copyright));
		}

		void load(Common::SeekableReadStream *stream);

		uint16 getWidth() const { return width; }
		uint16 getHeight() const { return height; }
		Graphics::PixelFormat getPixelFormat() const { return Graphics::PixelFormat::createFormatCLUT8(); };
		uint32 getFrameCount() const { return frames; }

		Common::String toString() const;
	};

	Header *_header;

	Common::SeekableReadStream *_fileStream;
	Graphics::Surface *_surface;

	void loadHeader(Common::SeekableReadStream *stream);

	// Chunk decoding
	void decodeChunkv4();
	void decodeChunkv6();

	void decodeAA();
	void decodeBB();
	void decodeIX();

	Common::String twoCC2str(uint16 tag);
};

} // End of namespace Cryo

#endif // CRYO_HNM_H
