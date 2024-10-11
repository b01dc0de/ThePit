@mkdir out\build\win

@set SRC_FILES="src\ThePit.cpp" "src\ThePit_Engine.cpp"
@set OUT_DIR="out\build\win\\"
@set LIB_DIR="..\lib\sokol\\"

@REM CL [option...] file... [option | file]... [lib...] [@command-file] [/link link-opt...]
CL /Fe:%OUT_DIR% /Fo:%OUT_DIR% /I %LIB_DIR% %SRC_FILES%

