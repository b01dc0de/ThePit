# CKA_NOTE:
#	The following assumes a couple things about the directory structure:
#		- ../lib/sokol is where sokol's source files are located
#		- ../sokol-tools-bin has been built in the parent directory
#	Would like to change this in the future but we'll burn that bridge when we get there

SRC_FILES="src/Main.cpp"
OUT_DIR=out/build/mac
OUT_FILE=thepit
LIB_DIR=./libs/sokol
BUILD_FLAGS="-g -pthread -O3 -fno-rtti -fno-exceptions -fPIC -x objective-c"
LINK_LIBS="-framework OpenGL -framework Foundation -framework Metal -framework QuartzCore -framework AppKit -framework AudioToolbox"
mkdir -p $OUT_DIR

SOKOL_SHDC=../sokol-tools-bin/bin/osx/sokol-shdc
GLSL_DIR=src/glsl
SHADER_FILE=$GLSL_DIR/vxcolor.glsl

# Use Sokol shader compiler:
$SOKOL_SHDC -i $SHADER_FILE -o $SHADER_FILE.h -l glsl410

g++ $BUILD_FLAGS -o $OUT_DIR/$OUT_FILE -I$LIB_DIR -I$(brew --prefix llvm)/include -L$(brew --prefix llvm)/lib $LINK_LIBS $SRC_FILES
