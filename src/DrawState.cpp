#include "DrawState.h"
#include "Graphics.h"

namespace ThePit
{
    const uint32_t px_width = 4;
    const uint32_t px_height = 4;
    uint32_t default_texture_pixels[px_width * px_height] = {
        0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000,
        0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000,
        0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF,
    };

    sg_pass default_pass = {};
    const sg_color default_clear_color = { 0.25f, 0.5f, 0.75f, 1.0f };
    const float default_clear_depth = 1.0f;
    sg_pass* GetDefaultSGPass()
    {
        static bool binit_default_pass = false;
        if (!binit_default_pass)
        {
            default_pass.action.colors[0].load_action = SG_LOADACTION_CLEAR;
            default_pass.action.colors[0].store_action = SG_STOREACTION_STORE;
            default_pass.action.colors[0].clear_value = default_clear_color;
            default_pass.action.depth.load_action = SG_LOADACTION_CLEAR;
            default_pass.action.depth.store_action = SG_STOREACTION_STORE;
            default_pass.action.depth.clear_value = default_clear_depth;
            binit_default_pass = true;
        }
        default_pass.swapchain = sglue_swapchain();
        return &default_pass;
    }

    static const int SLOT_vs_params = 0;

    DrawStateT* InitNewColorPipeline()
    {
        //sg_shader col_shader = sg_make_shader(cube_shader_desc(sg_query_backend()));
        sg_shader_desc vxcolor_desc = {};
        Graphics::GetVxColorShaderDesc(vxcolor_desc);
        sg_shader vxcolor_shader = sg_make_shader(vxcolor_desc);

        // Previously from sokol-generated .glsl.h
        static const int ATTR_vs_position = 0;
        static const int ATTR_vs_color0 = 1;

        sg_pipeline_desc pipeline_desc = {};
        pipeline_desc.layout.buffers[0].stride = sizeof(v3) + sizeof(v4);
        pipeline_desc.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
        pipeline_desc.shader = vxcolor_shader;
        pipeline_desc.index_type = SG_INDEXTYPE_UINT16;
        pipeline_desc.cull_mode = SG_CULLMODE_BACK;
        pipeline_desc.depth.write_enabled = true;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;

        DrawStateT* pnew_drawstate = new DrawStateT;
        pnew_drawstate->bind = {};
        pnew_drawstate->pip = sg_make_pipeline(&pipeline_desc);

        delete[] vxcolor_desc.vs.source;
        delete[] vxcolor_desc.fs.source;

        return pnew_drawstate;
    }

    DrawStateT* InitNewTexturePipeline()
    {
        sg_image_desc img_desc = {};
        img_desc.width = px_width;
        img_desc.height = px_height;
        img_desc.data.subimage[0][0] = SG_RANGE(default_texture_pixels);

        // Default sampler state
        sg_sampler_desc sampler_desc = {};

        //sg_shader texshader = sg_make_shader(texcube_shader_desc(sg_query_backend()));
        sg_shader_desc vxtexture_desc = {};
        Graphics::GetVxTextureShaderDesc(vxtexture_desc);
        sg_shader vxtexture_shader = sg_make_shader(vxtexture_desc);

        // Previously from sokol-generated .glsl.h
        static const int ATTR_vs_pos = 0;
        static const int ATTR_vs_texcoord0 = 1;
        static const int SLOT_tex = 0;
        static const int SLOT_smp = 0;

        sg_pipeline_desc pipeline_desc = {};
        pipeline_desc.layout.buffers[0].stride = sizeof(v3) + sizeof(v2);
        pipeline_desc.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.shader = vxtexture_shader;
        pipeline_desc.index_type = SG_INDEXTYPE_UINT16;
        pipeline_desc.cull_mode = SG_CULLMODE_BACK;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;

        DrawStateT* pnew_drawstate = new DrawStateT;
        pnew_drawstate->bind = {};
        pnew_drawstate->bind.fs.images[SLOT_tex] = sg_make_image(&img_desc);
        pnew_drawstate->bind.fs.samplers[SLOT_smp] = sg_make_sampler(&sampler_desc);

        pnew_drawstate->pip = sg_make_pipeline(&pipeline_desc);

        delete[] vxtexture_desc.vs.source;
        delete[] vxtexture_desc.fs.source;

        return pnew_drawstate;
    }

    DrawStateT* InitNewColorTexturePipeline()
    {
        sg_image_desc img_desc = {};
        img_desc.width = px_width;
        img_desc.height = px_height;
        img_desc.data.subimage[0][0] = SG_RANGE(default_texture_pixels);

        // Default sampler state
        sg_sampler_desc sampler_desc = {};

        sg_shader_desc colortexture_desc = {};
        Graphics::GetVxColorTextureShaderDesc(colortexture_desc);

        static const int ATTR_vs_pos = (0);
        static const int ATTR_vs_color0 = (1);
        static const int ATTR_vs_texcoord0 = (2);
        static const int SLOT_vs_params = (0);
        static const int SLOT_tex = (0);
        static const int SLOT_smp = (0);

        sg_pipeline_desc pipeline_desc = {};
        pipeline_desc.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
        pipeline_desc.layout.attrs[ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.shader = sg_make_shader(colortexture_desc);
        pipeline_desc.index_type = SG_INDEXTYPE_UINT16;
        pipeline_desc.cull_mode = SG_CULLMODE_BACK;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;
        pipeline_desc.label = "vxcolortexture";

        DrawStateT* new_coltex_pipeline = new DrawStateT;
        new_coltex_pipeline->bind = {};
        new_coltex_pipeline->bind.fs.images[SLOT_tex] = sg_make_image(&img_desc);
        new_coltex_pipeline->bind.fs.samplers[SLOT_smp] = sg_make_sampler(&sampler_desc);
        new_coltex_pipeline->pip = sg_make_pipeline(pipeline_desc);

        delete[] colortexture_desc.vs.source;
        delete[] colortexture_desc.fs.source;

        return new_coltex_pipeline;
    }

    void Draw(DrawStateT* draw_state, MeshDrawStateT* mesh_state, HMM_Mat4& view_proj)
    {
        THEPIT_ASSERT(nullptr != draw_state);
        THEPIT_ASSERT(nullptr != mesh_state);
        THEPIT_ASSERT(nullptr != mesh_state->geo);

        draw_state->bind.vertex_buffers[0] = mesh_state->geo->vertex_buffer;
        draw_state->bind.index_buffer = mesh_state->geo->index_buffer;

        HMM_Mat4 mvp = mesh_state->model_to_world * view_proj;
        sg_range mvp_range = SG_RANGE(mvp);

        sg_apply_pipeline(draw_state->pip);
        sg_apply_bindings(&draw_state->bind);
        sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &mvp_range);
        sg_draw(0, (int)mesh_state->geo->element_count, 1);
    }
} // namespace ThePit
