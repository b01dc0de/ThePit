cmake_minimum_required (VERSION 3.8)

project ("ThePit")

set(SRC_DIR src)
set(SRC_FILES ${SRC_DIR}/Main.cpp)
add_executable (ThePit ${SRC_FILES})

set(LIB_SOKOL_DIR ./libs/sokol)
target_include_directories(ThePit PUBLIC ${LIB_SOKOL_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThePit PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
