#include "DebugGraphics.h"

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

    VxBase cubeunicolor_vxs[] =
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

    static const TriInds cube_ixs[] =
    {
        {0, 1, 2},        {0, 2, 3},
        {6, 5, 4},        {7, 6, 4},
        {8, 9, 10},       {8, 10, 11},
        {14, 13, 12},     {15, 14, 12},
        {16, 17, 18},     {16, 18, 19},
        {22, 21, 20},     {23, 22, 20}
    };

    struct DebugShapeManagerT
    {
        GeometryT* cube_color = nullptr;
        GeometryT* cube_texture = nullptr;
        GeometryT* cube_unicolor = nullptr;
    } DebugShapeManager;

    GeometryT* GetCubeGeometry(DebugShapeGeometryE in_geo_type)
    {
        GeometryT* result = nullptr;

        switch (in_geo_type)
        {
            case DebugShapeGeometryE::Color:
            {
                if (nullptr == DebugShapeManager.cube_color)
                {
                    GeometryT* new_geo = new GeometryT;

                    new_geo->vertices = (const float*)cubecolor_vxs;
                    new_geo->indices = cube_ixs;
                    new_geo->element_count = (int)(ARRAY_SIZE(cube_ixs) * TriIdxCount);

                    new_geo->vertex_buffer = MakeVxBuffer(
                        (const float*)cubecolor_vxs,
                        sizeof(VxColor),
                        ARRAY_SIZE(cubecolor_vxs)
                    );
                    new_geo->index_buffer = MakeIxBuffer(cube_ixs, ARRAY_SIZE(cube_ixs));

                    DebugShapeManager.cube_color = new_geo;
                }
                result = DebugShapeManager.cube_color;
            } break;
            case DebugShapeGeometryE::Texture:
            {
                if (nullptr == DebugShapeManager.cube_texture)
                {
                    GeometryT* new_geo = new GeometryT;

                    new_geo->vertices = (const float*)cubetexture_vxs;
                    new_geo->indices = cube_ixs;
                    new_geo->element_count = (int)(ARRAY_SIZE(cube_ixs) * TriIdxCount);

                    new_geo->vertex_buffer = MakeVxBuffer(
                        (const float*)cubetexture_vxs,
                        sizeof(VxTexture),
                        ARRAY_SIZE(cubetexture_vxs)
                    );
                    new_geo->index_buffer = MakeIxBuffer(
                        cube_ixs,
                        ARRAY_SIZE(cube_ixs)
                    );

                    DebugShapeManager.cube_texture = new_geo;
                }
                result = DebugShapeManager.cube_texture;
            } break;
            case DebugShapeGeometryE::Unicolor:
            {
                if (nullptr == DebugShapeManager.cube_unicolor)
                {
                    GeometryT* new_geo = new GeometryT;

                    new_geo->vertices = (const float*)cubeunicolor_vxs;
                    new_geo->indices = cube_ixs;
                    new_geo->element_count = ARRAY_SIZE(cube_ixs) * TriIdxCount;

                    new_geo->vertex_buffer = MakeVxBuffer
                    (
                        (const float*)cubeunicolor_vxs,
                        sizeof(VxBase),
                        ARRAY_SIZE(cubeunicolor_vxs)
                    );
                    new_geo->index_buffer = MakeIxBuffer
                    (
                        cube_ixs,
                        ARRAY_SIZE(cube_ixs)
                    );

                    DebugShapeManager.cube_unicolor = new_geo;
                }
                result = DebugShapeManager.cube_unicolor;
            } break;
            default:
            {
                THEPIT_ASSERT(false);
            } break;
        }
        
        return result;
    }
} // namespace ThePit
