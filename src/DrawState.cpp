#include "DrawState.h"
#include "glsl/texcube-sapp.glsl.h"

namespace thepit
{
    DrawStateT* InitNewColorPipeline()
    {
        return nullptr;
    }

    const uint32_t px_width = 4;
    const uint32_t px_height = 4;
    uint32_t pixels[px_width * px_height] = {
        0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000,
        0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFF000000,
        0xFF000000, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF,
    };

    DrawStateT* InitNewTexturePipeline()
    {
        sg_image_desc img_desc = {};
        img_desc.width = px_width;
        img_desc.height = px_height;
        img_desc.data.subimage[0][0] = SG_RANGE(pixels);

        // Default sampler state
        sg_sampler_desc sampler_desc = {};

        sg_shader texshader = sg_make_shader(texcube_shader_desc(sg_query_backend()));

        sg_pipeline_desc pipeline_desc = {};
        pipeline_desc.layout.attrs[ATTR_vs_pos].format = SG_VERTEXFORMAT_FLOAT3;
        pipeline_desc.layout.attrs[ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.shader = texshader;
        pipeline_desc.index_type = SG_INDEXTYPE_UINT16;
        pipeline_desc.cull_mode = SG_CULLMODE_BACK;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;

        DrawStateT* pnew_drawstate = new DrawStateT;
        pnew_drawstate->bind = {};
        pnew_drawstate->bind.fs.images[SLOT_tex] = sg_make_image(&img_desc);
        pnew_drawstate->bind.fs.samplers[SLOT_smp] = sg_make_sampler(&sampler_desc);

        pnew_drawstate->pip = sg_make_pipeline(&pipeline_desc);

        pnew_drawstate->pass = {};
        pnew_drawstate->pass.colors[0].load_action = SG_LOADACTION_CLEAR;
        pnew_drawstate->pass.colors[0].clear_value = { 0.25f, 0.5f, 0.75f, 1.0f };

        return pnew_drawstate;
    }


    void Draw(DrawStateT* InState, MeshDrawT* InMesh, sg_range& in_vsparams_range)
    {
        if (!InState || !InMesh) { return; } // TODO: Actually handle this as an error

        InState->bind.vertex_buffers[0] = InMesh->geometry->vertex_buffer;
        InState->bind.index_buffer = InMesh->geometry->index_buffer;

        sg_pass draw_pass = {};
        draw_pass.action = InState->pass;
        draw_pass.swapchain = sglue_swapchain();
        sg_begin_pass(&draw_pass);
        sg_apply_pipeline(InState->pip);
        sg_apply_bindings(&InState->bind);
        sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &in_vsparams_range);
        sg_draw(0, (int)InMesh->geometry->element_count, 1);
        sg_end_pass();
        sg_commit();
    }
}
