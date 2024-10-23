# Uncomment for build configs
# RELEASE = 1
# SANITIZE = 1

UNAME = $(shell uname -s)

# Detect host platform
ifndef HOST_PLATFORM
	ifeq ($(UNAME),Darwin)
		HOST_PLATFORM = macos
		HOST_ARCH = $(shell uname -m)
	else ifeq ($(UNAME),Linux)
		HOST_PLATFORM = linux
		HOST_ARCH = x86_64
	else
		HOST_PLATFORM = windows
		HOST_ARCH = x86_64
	endif
endif

# Detect target platform if not provided
ifndef TARGET_PLATFORM
	TARGET_PLATFORM = $(HOST_PLATFORM)
endif

ifndef TARGET_ARCH
	TARGET_ARCH = $(HOST_ARCH)
endif

# Library paths
PATH_LIB         = libs
# PATH_SOLOUD      = $(PATH_LIB)/soloud
PATH_SOKOL       = $(PATH_LIB)/sokol
PATH_SOKOL_TOOLS = $(PATH_LIB)/sokol-tools-bin
PATH_STB         = $(PATH_LIB)/stb

CCFLAGS = 
LDFLAGS =

# Compiler and linker setup
ifeq ($(HOST_PLATFORM),macos)
	CC   = $(shell brew --prefix llvm)/bin/clang++
	LD   = $(shell brew --prefix llvm)/bin/clang++
	CCFLAGS += -I$(shell brew --prefix llvm)/include -DWITH_COREAUDIO
	LDFLAGS += -L$(shell brew --prefix llvm)/lib
	DYLIB = dylib
	LDFLAGS += -framework Foundation -framework Cocoa -framework QuartzCore -framework AppKit
	LDFLAGS += -framework CoreAudio -framework AudioToolbox
	LDFLAGS += -framework OpenGL
else ifeq ($(HOST_PLATFORM),linux)
	CC = g++
	LD = g++
	LDFLAGS += -lGL -lasound -lSDL2
	DYLIB = so
endif

# Compiler flags
CCFLAGS += -std=c++17 -Wall -Wextra
LDFLAGS += -lstdc++
INCFLAGS = -iquote src -iquote util -Ilibs/sokol -I$(PATH_STB)

# Release or debug configuration
ifdef RELEASE
	CCFLAGS += -O2 -DTARGET_RELEASE
else
	CCFLAGS += -O0 -g -fno-omit-frame-pointer -DTARGET_DEBUG
	ifdef SANITIZE
		CCFLAGS += -fsanitize=undefined,address -fno-sanitize=function
		LDFLAGS += -fsanitize=undefined,address -fno-sanitize=function
	endif
endif

# Directories and file setup
BIN = bin
SRC_CPP = $(shell find src -name "*.cpp")
SRC_OBJC = $(shell find src -name "*.mm")
# SRC_STB = $(PATH_STB)/stb_vorbis.c

OBJ_CPP = $(SRC_CPP:%.cpp=$(BIN)/%.o)
OBJ_OBJC = $(SRC_OBJC:%.mm=$(BIN)/%.o)
# OBJ_STB = $(BIN)/libs/stb/stb_vorbis.o

# Soloud audio library sources
# SRC_CPP += $(shell find $(PATH_SOLOUD)/src/core -name "*.cpp")
# SRC_CPP += $(shell find $(PATH_SOLOUD)/src/audiosource/wav -name "*.cpp")
# SRC_CPP += $(shell find $(PATH_SOLOUD)/src/filter -name "*.cpp")
# OBJ_CPP = $(SRC_CPP:%.cpp=$(BIN)/%.o)

# Output file names
OUT = $(BIN)/thepit
OUT_SHARED = $(BIN)/thepit.$(DYLIB)

# Shader sources
SRC_SHADER = $(shell find src/shader -name "*.glsl")
OUT_SHADER = $(SRC_SHADER:%.glsl=%.glsl.h)

# Targets
all: dirs shaders build

$(OUT_SHADER): %.glsl.h: %.glsl
	$(SHDC) --input $^ --output $@ --slang glsl410 --format=sokol_impl -r

shaders: $(OUT_SHADER)

dirs:
	@mkdir -p $(BIN)
	@mkdir -p $(BIN)/src
	@mkdir -p $(BIN)/src/engine
	@mkdir -p $(BIN)/src/engine/geometry
	@mkdir -p $(BIN)/src/engine/material
	@mkdir -p $(BIN)/src/engine/mesh
	@mkdir -p $(BIN)/util
	@mkdir -p $(BIN)/lib

# @mkdir -p $(BIN)/libs/stb
# @mkdir -p $(BIN)/libs/soloud/src/core
# @mkdir -p $(BIN)/libs/soloud/src/audiosource/wav
# @mkdir -p $(BIN)/libs/soloud/src/filter

# Build targets
$(OBJ_CPP): $(BIN)/%.o: %.cpp
	$(CC) -o $@ -MMD -c $(CCFLAGS) $(INCFLAGS) $<

$(OBJ_OBJC): $(BIN)/%.o: %.mm
	$(CC) -x objective-c++ -o $@ -MMD -c $(CCFLAGS) $(INCFLAGS) $<

# $(OBJ_STB): $(SRC_STB)
# 	$(CC) -o $@ -MMD -c $(CCFLAGS) $(INCFLAGS) $<

build: $(OBJ_CPP) $(OBJ_OBJC)
	$(LD) -o $(OUT) $(OBJ_CPP) $(OBJ_OBJC) $(LDFLAGS)

clean:
	rm -rf $(BIN)/*

run: build
	$(OUT)

# Include dependency files if they exist
-include $(OBJ_CPP:.o=.d) $(OBJ_OBJC:.o=.d) $(OBJ_STB:.o=.d)

.PHONY: all shaders dirs build clean run
