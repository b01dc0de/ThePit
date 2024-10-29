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
