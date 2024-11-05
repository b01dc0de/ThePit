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

    GeometryT* InitNewSkyboxMesh()
    {
        static const float skybox_size = 500.0f;

        static const NormT FrontNorm{ 0.0f, 0.0f, -1.0f };
        static const NormT BackNorm{ 0.0f, 0.0f, 1.0f };
        static const NormT TopNorm{ 0.0f, -1.0f, 0.0f };
        static const NormT BotNorm{ 0.0f, 1.0f, 0.0f };
        static const NormT LeftNorm{ -1.0f, 0.0f, 0.0f };
        static const NormT RightNorm{ 1.0f, 0.0f, 0.0f };

        static const ColorT front_color{1.0f, 1.0f, 1.0f, 1.0f};
        static const ColorT back_color{0.25f, 0.25f, 0.25f, 1.0f};
        static const ColorT top_color{1.0f, 0.0f, 0.0f, 1.0f};
        static const ColorT bot_color{0.0f, 1.0f, 0.0f, 1.0f};
        static const ColorT left_color{0.0f, 0.0f, 1.0f, 1.0f};
        static const ColorT right_color{1.0f, 0.0f, 1.0f, 1.0f};

        VxColorTexture cubetexture_vxs[] = {
            { {-skybox_size, -skybox_size, -skybox_size}, front_color, {0.0f, 0.0f}},
            { {skybox_size, -skybox_size, -skybox_size}, front_color, {1.0f, 0.0f} },
            { { skybox_size,  skybox_size, -skybox_size}, front_color, {1.0f, 1.0f} },
            { {-skybox_size,  skybox_size, -skybox_size}, front_color, {0.0f, 1.0f} },

            { {-skybox_size, -skybox_size,  skybox_size}, back_color, {0.0f, 0.0f} },
            { { skybox_size, -skybox_size,  skybox_size}, back_color, {1.0f, 0.0f} },
            { { skybox_size,  skybox_size,  skybox_size}, back_color, {1.0f, 1.0f} },
            { {-skybox_size,  skybox_size,  skybox_size}, back_color, {0.0f, 1.0f} },

            { {-skybox_size, -skybox_size, -skybox_size}, top_color, {0.0f, 0.0f} },
            { {-skybox_size,  skybox_size, -skybox_size}, top_color, {1.0f, 0.0f} },
            { {-skybox_size,  skybox_size,  skybox_size}, top_color, {1.0f, 1.0f} },
            { {-skybox_size, -skybox_size,  skybox_size}, top_color, {0.0f, 1.0f} },

            { { skybox_size, -skybox_size, -skybox_size}, bot_color, {0.0f, 0.0f} },
            { { skybox_size,  skybox_size, -skybox_size}, bot_color, {1.0f, 0.0f} },
            { { skybox_size,  skybox_size,  skybox_size}, bot_color, {1.0f, 1.0f} },
            { { skybox_size, -skybox_size,  skybox_size}, bot_color, {0.0f, 1.0f} },

            { {-skybox_size, -skybox_size, -skybox_size}, left_color, {0.0f, 0.0f} },
            { {-skybox_size, -skybox_size,  skybox_size}, left_color, {1.0f, 0.0f} },
            { { skybox_size, -skybox_size,  skybox_size}, left_color, {1.0f, 1.0f} },
            { { skybox_size, -skybox_size, -skybox_size}, left_color, {0.0f, 1.0f} },

            { {-skybox_size,  skybox_size, -skybox_size}, right_color, {0.0f, 0.0f} },
            { {-skybox_size,  skybox_size,  skybox_size}, right_color, {1.0f, 0.0f} },
            { { skybox_size,  skybox_size,  skybox_size}, right_color, {1.0f, 1.0f} },
            { { skybox_size,  skybox_size, -skybox_size}, right_color, {0.0f, 1.0f} },
        };

        static const TriInds skybox_inds[] =
        {
            {0, 2, 1},        {0, 3, 2},
            {6, 4, 5},        {7, 4, 6},
            {8, 10, 9},       {8, 11, 10},
            {14, 12, 13},     {15, 12, 14},
            {16, 18, 17},     {16, 19, 18},
            {22, 20, 21},     {23, 20, 22}
        };

        GeometryT* result = new GeometryT;
        result->vertex_buffer = MakeVxBuffer((const float*)cubetexture_vxs, sizeof(VxColorTexture), ARRAY_SIZE(cubetexture_vxs));
        result->index_buffer = MakeIxBuffer(skybox_inds, ARRAY_SIZE(skybox_inds));
        result->vertices = (const float*)cubetexture_vxs;
        result->indices = skybox_inds;
        result->element_count = (int)(ARRAY_SIZE(skybox_inds) * TriIdxCount);
        return result;
    }
} // namespace ThePit
