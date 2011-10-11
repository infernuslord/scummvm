MODULE := engines/cryo

MODULE_OBJS := \
	data/graphics/font.o \
	data/graphics/hnm.o \
	data/graphics/jp6.o \
	data/graphics/sprite.o \
	data/graphics/spw.o \
	data/logic/scenario.o \
	data/logic/wam.o \
	data/resource/bigfile.o \
	data/sound/apc.o \
	data/sound/spp.o \
	data/sound/synchro.o \
	data/sound/zik.o \
	debug.o \
	detection.o \
	cryo.o

# This module can be built as a plugin
ifeq ($(ENABLE_CRYO), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
