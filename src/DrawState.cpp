#include "DrawState.h"
#include "Shader.h"
//#include "glsl/cube-sapp.glsl.h"
//#include "glsl/texcube-sapp.glsl.h"

namespace thepit
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
        GetVxColorShaderDesc(vxcolor_desc);
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
        GetVxTextureShaderDesc(vxtexture_desc);
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

    void Draw(DrawStateT* InState, MeshDrawT* InMesh, sg_range& in_vsparams_range)
    {
        THEPIT_ASSERT(nullptr != InState);
        THEPIT_ASSERT(nullptr != InMesh);

        InState->bind.vertex_buffers[0] = InMesh->vertex_buffer;
        InState->bind.index_buffer = InMesh->index_buffer;

        sg_apply_pipeline(InState->pip);
        sg_apply_bindings(&InState->bind);
        sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &in_vsparams_range);
        sg_draw(0, (int)InMesh->element_count, 1);
    }
}
