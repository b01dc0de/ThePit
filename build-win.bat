@mkdir out\build\win

@set SRC_FILES=src\Main.cpp src\Cube.cpp src\DrawState.cpp src\Engine.cpp src\Geometry.cpp src\Material.cpp src\Mesh.cpp
@set OUT_DIR=out\build\win\
@set INC_LIBS=/I libs\sokol\ /I libs\

@REM CL [option...] file... [option | file]... [lib...] [@command-file] [/link link-opt...]
CL /Fe:%OUT_DIR%\ThePit.exe /Fo:%OUT_DIR% %INC_LIBS% %SRC_FILES%

:: CKA_NOTE This is the cmd that VS's CMake runs for 'x64-debug'
:: "C:\WINDOWS\system32\cmd.exe" /c "C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\2022\ENTERPRISE\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE\CMake\bin\cmake.exe"  -G "Ninja"  -DCMAKE_C_COMPILER:STRING="cl.exe" -DCMAKE_CXX_COMPILER:STRING="cl.exe" -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="W:/ThePit/out/install/x64-debug"   -DCMAKE_MAKE_PROGRAM="C:\PROGRAM FILES\MICROSOFT VISUAL STUDIO\2022\ENTERPRISE\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE\Ninja\ninja.exe" "W:\ThePit"

