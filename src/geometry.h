#ifndef THEPIT_ENGINE_GEOMETRY_H
#define THEPIT_ENGINE_GEOMETRY_H
 
#include "Common.h"

struct GeometryStruct {
    const float* vertices;
    const uint16_t* indices;
    size_t vertex_count;
    sg_buffer vertex_buffer;
    sg_buffer index_buffer;
};

#endif // THEPIT_ENGINE_GEOMETRY_H