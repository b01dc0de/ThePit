cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("ThePit")

set(IMGUI_SRC_DIR libs/imgui)
set(IMGUI_SRC_FILES
		${IMGUI_SRC_DIR}/imgui.cpp
		${IMGUI_SRC_DIR}/imgui_draw.cpp
		${IMGUI_SRC_DIR}/imgui_tables.cpp
		${IMGUI_SRC_DIR}/imgui_widgets.cpp)

set(SRC_DIR src)
set(SRC_FILES
		${SRC_DIR}/Main.cpp
		${SRC_DIR}/Camera.cpp
		${SRC_DIR}/DebugGraphics.cpp
		${SRC_DIR}/Engine.cpp
		${SRC_DIR}/FileUtils.cpp
		${SRC_DIR}/Geometry.cpp
		${SRC_DIR}/Graphics.cpp
		${SRC_DIR}/Input.cpp
		${SRC_DIR}/Log.cpp)

add_executable(ThePit ${SRC_FILES} ${IMGUI_SRC_FILES})

set(LIB_SOKOL_DIR ./libs/sokol)
set(LIB_GLM_DIR ./libs/glm)
set(LIB_IMGUI_DIR ./libs/imgui)
target_include_directories(ThePit PUBLIC ${LIB_SOKOL_DIR} ${LIB_GLM_DIR} ${LIB_IMGUI_DIR})

if (WIN32)
endif ()
if (APPLE)
endif ()
if (UNIX AND NOT APPLE)
	target_link_libraries(ThePit -lasound -lGL -lm -lXcursor -lXi -lX11)
endif ()
