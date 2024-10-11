cmake_minimum_required (VERSION 3.8)

project ("ThePit")

set(SOURCE_DIR src)
set(SOURCE_FILES ${SOURCE_DIR}/ThePit.cpp ${SOURCE_DIR}/ThePit.h)
add_executable (ThePit ${SOURCE_FILES})

set(LIB_SOKOL_DIR ../lib/sokol)
target_include_directories(ThePit PUBLIC ${LIB_SOKOL_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ThePit PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
