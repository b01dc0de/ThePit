#include "Cube.h"
#include "Geometry.h"

namespace ThePit
{
    ColorT color_yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
    ColorT color_white{ 1.0f, 1.0f, 1.0f, 1.0f };
    ColorT color_green{ 0.0f, 1.0f, 0.0f, 1.0f };
    ColorT color_blue{ 0.0f, 0.0f, 1.0f, 1.0f };
    ColorT color_red{ 1.0f, 0.0f, 0.0f, 1.0f };
    ColorT color_orange{ 1.0f, 0.5f, 0.0f, 1.0f };
    static const VxColor cubecolor_vxs[] =
    {
        { {-1.0, -1.0, -1.0},  color_green },
        { {1.0, -1.0, -1.0},   color_green },
        { {1.0,  1.0, -1.0},   color_green },
        { {-1.0,  1.0, -1.0},  color_green },

        { {-1.0, -1.0, 1.0},    color_blue },
        { {1.0, -1.0,  1.0},    color_blue },
        { {1.0,  1.0,  1.0},    color_blue },
        { {-1.0,  1.0,  1.0},   color_blue },

        { {-1.0, -1.0, -1.0},   color_orange },
        { {-1.0,  1.0, -1.0},   color_orange },
        { {-1.0,  1.0,  1.0},   color_orange },
        { {-1.0, -1.0,  1.0},   color_orange },

        { {1.0, -1.0, -1.0},    color_red },
        { {1.0,  1.0, -1.0},    color_red },
        { {1.0,  1.0,  1.0},    color_red },
        { {1.0, -1.0,  1.0},    color_red },

        { {-1.0, -1.0, -1.0},   color_white },
        { {-1.0, -1.0,  1.0},   color_white },
        { {1.0, -1.0,  1.0},    color_white },
        { {1.0, -1.0, -1.0},    color_white },

        { {-1.0,  1.0, -1.0},   color_yellow },
        { {-1.0,  1.0,  1.0},   color_yellow },
        { {1.0,  1.0,  1.0},    color_yellow },
        { {1.0,  1.0, -1.0},    color_yellow }
    };

    VxTexture cubetexture_vxs[] = {
        /* pos                  uvs */
        { -1.0f, -1.0f, -1.0f,  0.0f, 0.0f },
        {  1.0f, -1.0f, -1.0f,  1.0f, 0.0f },
        {  1.0f,  1.0f, -1.0f,  1.0f, 1.0f },
        { -1.0f,  1.0f, -1.0f,  0.0f, 1.0f },

        { -1.0f, -1.0f,  1.0f,  0.0f, 0.0f },
        {  1.0f, -1.0f,  1.0f,  1.0f, 0.0f },
        {  1.0f,  1.0f,  1.0f,  1.0f, 1.0f },
        { -1.0f,  1.0f,  1.0f,  0.0f, 1.0f },

        { -1.0f, -1.0f, -1.0f,  0.0f, 0.0f },
        { -1.0f,  1.0f, -1.0f,  1.0f, 0.0f },
        { -1.0f,  1.0f,  1.0f,  1.0f, 1.0f },
        { -1.0f, -1.0f,  1.0f,  0.0f, 1.0f },

        {  1.0f, -1.0f, -1.0f,  0.0f, 0.0f },
        {  1.0f,  1.0f, -1.0f,  1.0f, 0.0f },
        {  1.0f,  1.0f,  1.0f,  1.0f, 1.0f },
        {  1.0f, -1.0f,  1.0f,  0.0f, 1.0f },

        { -1.0f, -1.0f, -1.0f,  0.0f, 0.0f },
        { -1.0f, -1.0f,  1.0f,  1.0f, 0.0f },
        {  1.0f, -1.0f,  1.0f,  1.0f, 1.0f },
        {  1.0f, -1.0f, -1.0f,  0.0f, 1.0f },

        { -1.0f,  1.0f, -1.0f,  0.0f, 0.0f },
        { -1.0f,  1.0f,  1.0f,  1.0f, 0.0f },
        {  1.0f,  1.0f,  1.0f,  1.0f, 1.0f },
        {  1.0f,  1.0f, -1.0f,  0.0f, 1.0f },
    };

    VxMin cubeunicolor_vxs[] =
    {
        {-1.0, -1.0, -1.0},
        {1.0, -1.0, -1.0},
        {1.0,  1.0, -1.0},
        {-1.0,  1.0, -1.0},

        {-1.0, -1.0, 1.0},
        {1.0, -1.0,  1.0},
        {1.0,  1.0,  1.0},
        {-1.0,  1.0,  1.0},

        {-1.0, -1.0, -1.0},
        {-1.0,  1.0, -1.0},
        {-1.0,  1.0,  1.0},
        {-1.0, -1.0,  1.0},

        {1.0, -1.0, -1.0},
        {1.0,  1.0, -1.0},
        {1.0,  1.0,  1.0},
        {1.0, -1.0,  1.0},

        {-1.0, -1.0, -1.0},
        {-1.0, -1.0,  1.0},
        {1.0, -1.0,  1.0},
        {1.0, -1.0, -1.0},

        {-1.0,  1.0, -1.0},
        {-1.0,  1.0,  1.0},
        {1.0,  1.0,  1.0},
        {1.0,  1.0, -1.0},
    };

    static const TriInds cube_inds[] =
    {
        {0, 1, 2},        {0, 2, 3},
        {6, 5, 4},        {7, 6, 4},
        {8, 9, 10},       {8, 10, 11},
        {14, 13, 12},     {15, 14, 12},
        {16, 17, 18},     {16, 18, 19},
        {22, 21, 20},     {23, 22, 20}
    };


    GeometryT* InitNewCubeColorGeometry()
    {
        GeometryT* pnew_geometry = new GeometryT;

        // Generate vertices
        pnew_geometry->vertices = (const float*)cubecolor_vxs;
        pnew_geometry->indices = cube_inds;
        pnew_geometry->element_count = (int)(ARRAY_SIZE(cube_inds) * TriIdxCount);

        sg_buffer_desc vertex_buffer_desc = {};
        vertex_buffer_desc.data = SG_RANGE(cubecolor_vxs);
        vertex_buffer_desc.type = SG_BUFFERTYPE_VERTEXBUFFER;
        vertex_buffer_desc.usage = SG_USAGE_IMMUTABLE;  // We assume this geometry won't change

        // Set up the vertex buffer description
        pnew_geometry->vertex_buffer = sg_make_buffer(&vertex_buffer_desc);

        sg_buffer_desc index_buffer_desc = {};
        index_buffer_desc.data = SG_RANGE(cube_inds);
        index_buffer_desc.type = SG_BUFFERTYPE_INDEXBUFFER;
        index_buffer_desc.usage = SG_USAGE_IMMUTABLE;  // We assume this geometry won't change

        pnew_geometry->index_buffer = sg_make_buffer(&index_buffer_desc);

        return pnew_geometry;
    }

    GeometryT* InitNewCubeSingleColorGeometry(const ColorT& in_color)
    {
        static VxColor cubesinglecolor_vxs[ARRAY_SIZE(cubecolor_vxs)];
        static bool bcubesinglecolor_init = false;
        if (!bcubesinglecolor_init)
        {
            for (int vx_idx = 0; vx_idx < ARRAY_SIZE(cubecolor_vxs); vx_idx++)
            {
                cubesinglecolor_vxs[vx_idx].pos = cubecolor_vxs[vx_idx].pos;
                cubesinglecolor_vxs[vx_idx].color = in_color;
            }
            bcubesinglecolor_init = true;
        }

        GeometryT* pnew_geometry = new GeometryT;
        pnew_geometry->vertices = (const float*)cubesinglecolor_vxs;
        pnew_geometry->indices = cube_inds;
        pnew_geometry->element_count = ARRAY_SIZE(cube_inds) * TriIdxCount;

        pnew_geometry->vertex_buffer = MakeVxBuffer
        (
            (const float*)cubesinglecolor_vxs,
            sizeof(VxColor),
            ARRAY_SIZE(cubesinglecolor_vxs)
        );
        pnew_geometry->index_buffer = MakeIxBuffer
        (
            cube_inds,
            ARRAY_SIZE(cube_inds)
        );

        return pnew_geometry;
    }

    GeometryT* InitNewCubeTexGeometry()
    {
        sg_buffer_desc vxbuff_desc = {};
        vxbuff_desc.data = SG_RANGE(cubetexture_vxs);
        vxbuff_desc.type = SG_BUFFERTYPE_VERTEXBUFFER;
        vxbuff_desc.usage = SG_USAGE_IMMUTABLE;

        sg_buffer_desc ixbuff_desc = {};
        ixbuff_desc.data = SG_RANGE(cube_inds);
        ixbuff_desc.type = SG_BUFFERTYPE_INDEXBUFFER;
        ixbuff_desc.usage = SG_USAGE_IMMUTABLE;

        GeometryT* pnew_geometry = new GeometryT;
        pnew_geometry->vertices = (const float*)cubetexture_vxs;
        pnew_geometry->indices = cube_inds;
        pnew_geometry->element_count = (int)(ARRAY_SIZE(cube_inds) * TriIdxCount);

        pnew_geometry->vertex_buffer = sg_make_buffer(&vxbuff_desc);
        pnew_geometry->index_buffer = sg_make_buffer(&ixbuff_desc);

        return pnew_geometry;
    }

    GeometryT* InitNewCubeUnicolor()
    {
        sg_buffer_desc vxbuff_desc = {};
        vxbuff_desc.data = SG_RANGE(cubeunicolor_vxs);
        vxbuff_desc.type = SG_BUFFERTYPE_VERTEXBUFFER;
        vxbuff_desc.usage = SG_USAGE_IMMUTABLE;

        sg_buffer_desc ixbuff_desc = {};
        ixbuff_desc.data = SG_RANGE(cube_inds);
        ixbuff_desc.type = SG_BUFFERTYPE_INDEXBUFFER;
        ixbuff_desc.usage = SG_USAGE_IMMUTABLE;

        GeometryT* pnew_geometry = new GeometryT;
        pnew_geometry->vertices = (const float*)cubeunicolor_vxs;
        pnew_geometry->indices = cube_inds;
        pnew_geometry->element_count = ARRAY_SIZE(cube_inds) * TriIdxCount;

        pnew_geometry->vertex_buffer = MakeVxBuffer
        (
            (const float*)cubeunicolor_vxs,
            sizeof(VxColor),
            ARRAY_SIZE(cubeunicolor_vxs)
        );
        pnew_geometry->index_buffer = MakeIxBuffer
        (
            cube_inds,
            ARRAY_SIZE(cube_inds)
        );

        return pnew_geometry;
    }
} // namespace ThePit