cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("ThePit")

set(SRC_DIR src)
set(SRC_FILES ${SRC_DIR}/Main.cpp ${SRC_DIR}/Cube.cpp ${SRC_DIR}/Engine.cpp ${SRC_DIR}/Geometry.cpp ${SRC_DIR}/Material.cpp ${SRC_DIR}/Mesh.cpp)
add_executable (ThePit ${SRC_FILES})

set(LIB_SOKOL_DIR ./libs/sokol)
target_include_directories(ThePit PUBLIC ${LIB_SOKOL_DIR})
