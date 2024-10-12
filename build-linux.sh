# CKA_NOTE:
#	The following assumes a couple things about the directory structure:
#		- ../lib/sokol is where sokol's source files are located
#		- ../sokol-tools-bin has been built in the parent directory
#	Would like to change this in the future but we'll burn that bridge when we get there

SRC_FILES="src/ThePit.cpp"
OUT_DIR=out/build/linux
OUT_FILE=thepit
LIB_DIR=../lib/sokol
LINK_LIBS="-lasound -lGL -lm -lXcursor -lXi -lX11"
BUILD_FLAGS="-g -pthread"

mkdir -p $OUT_DIR

SOKOL_SHDC=../sokol-tools-bin/bin/linux/sokol-shdc
GLSL_DIR=src/glsl
SHADER_FILE=$GLSL_DIR/thepit-vxcolor.glsl

# Use Sokol shader compiler:
$SOKOL_SHDC -i $SHADER_FILE -o $SHADER_FILE.h -l glsl410

g++ $BUILD_FLAGS -o $OUT_DIR/$OUT_FILE -I $LIB_DIR $SRC_FILES $LINK_LIBS
