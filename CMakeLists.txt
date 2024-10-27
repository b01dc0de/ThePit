cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("ThePit")

set(SRC_DIR src)
set(SRC_FILES
		${SRC_DIR}/Main.cpp
		${SRC_DIR}/Camera.cpp
		${SRC_DIR}/Cube.cpp
		${SRC_DIR}/DrawState.cpp
		${SRC_DIR}/Engine.cpp
		${SRC_DIR}/FileUtils.cpp
		${SRC_DIR}/Geometry.cpp
		${SRC_DIR}/Input.cpp
		${SRC_DIR}/Material.cpp
		${SRC_DIR}/Mesh.cpp
		${SRC_DIR}/MeshUtils.cpp
		${SRC_DIR}/Shader.cpp)

add_executable(ThePit ${SRC_FILES})

set(LIB_SOKOL_DIR ./libs/sokol)
target_include_directories(ThePit PUBLIC ${LIB_SOKOL_DIR})

if (WIN32)
endif ()
if (APPLE)
endif ()
if (UNIX AND NOT APPLE)
	target_link_libraries(ThePit -lasound -lGL -lm -lXcursor -lXi -lX11)
endif ()
