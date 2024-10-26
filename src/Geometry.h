#ifndef THEPIT_GEOMETRY_H
#define THEPIT_GEOMETRY_H
 
#include "Common.h"

namespace thepit
{
    // Vertex format for v3 position + v4 color
#pragma pack(push, 1)
    struct PosT
    {
        float x;
        float y;
        float z;
    };
    struct ColorT
    {
        float r;
        float g;
        float b;
        float a;
    };
    struct TexUVT
    {
        float u;
        float v;
    };

    struct VxColor
    {
        PosT pos;
        ColorT color;
    };
    struct VxTexture
    {
        PosT pos;
        TexUVT uv;
    };
#pragma pack(pop)

    using IdxT = uint16_t;
    static const int TriIdxCount = 3;
    struct TriInds
    {
        IdxT a;
        IdxT b;
        IdxT c;
    };

    struct GeometryT {
        const float* vertices;
        const TriInds* indices;
        size_t element_count;
        sg_buffer vertex_buffer;
        sg_buffer index_buffer;
    };

    sg_buffer MakeVxBuffer(const float* p_vxs, size_t vx_size, size_t vx_count);
    sg_buffer MakeIxBuffer(const TriInds* p_inds, size_t ix_count);
}

#endif // THEPIT_ENGINE_GEOMETRY_H