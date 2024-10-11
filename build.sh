SRC_FILES="src/ThePit.cpp src/ThePit_Engine.cpp"
OUT_DIR=out/build/linux
OUT_FILE=thepit
LIB_DIR=../lib/sokol
LINK_LIBS="-lX11 -lXcursor -lXi -lGL"

mkdir -p $OUT_DIR

g++ -g -o $OUT_DIR/$OUT_FILE -I $LIB_DIR $SRC_FILES $LINK_LIBS
