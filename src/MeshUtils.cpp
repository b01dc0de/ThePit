#include "MeshUtils.h"

namespace ThePit
{
    GeometryT* InitNewFloorMesh()
    {
        static const float half_floor_length = 50.0f;
        static const float floor_height_level = 10.0f;
        static const VxTexture floor_vxs[] =
        {
            {{half_floor_length, floor_height_level, half_floor_length}, {0.0f, 0.0f}},
            {{-half_floor_length, floor_height_level, half_floor_length}, {1.0f, 0.0f}},
            {{half_floor_length, floor_height_level, -half_floor_length}, {0.0f, 1.0f}},
            {{-half_floor_length, floor_height_level, -half_floor_length}, {1.0f, 1.0f}},
        };
        static const TriInds floor_ixs[] =
        {
            {2, 1, 0},
            {2, 3, 1}
        };
        GeometryT* result = new GeometryT;

        result->vertex_buffer = MakeVxBuffer((const float*)floor_vxs, sizeof(VxTexture), ARRAY_SIZE(floor_vxs));
        result->index_buffer = MakeIxBuffer(floor_ixs, ARRAY_SIZE(floor_ixs));

        result->vertices = (const float*)floor_vxs;
        result->indices = floor_ixs;
        result->element_count = (int)(ARRAY_SIZE(floor_ixs) * TriIdxCount);

        return result;
    }
} // ThePit
