# Copyright (C) 2008-2016 Marvell International Ltd.
# All Rights Reserved.

exec-cpp-y += hello_world_cpp
hello_world_cpp-objs-y := src/main.cc src/wmsdk-cpp-helper.cc
# Applications could also define custom linker files if required using following:
#hello_world-ld-y := /path/to/ldscript

hello_world_cpp-lflags-y := -D_Bool=bool -std=c++1y --specs=nosys.specs

# Applications could also define custom board files if required using following:
#hello_world-board-y := /path/to/boardfile

hello_world_cpp-ld-y := $(d)/$(arch_name-y).ld

ifeq ($(XIP), 1)
hello_world_cpp-ld-y := $(d)/$(arch_name-y)-xip.ld
endif



