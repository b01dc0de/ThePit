#include "Engine.h"

#include "glsl/vxcolor.glsl.h"

thepit::State thepit::GlobalState;

void thepit::Init(void* State)
{
	sg_desc graphics_desc = {};
	graphics_desc.environment = sglue_environment();
	sg_setup(&graphics_desc);

    float tri_vertices[] = {
        // positions            // colors
         0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
    };
	sg_buffer_desc vbuffer_desc = {};
	vbuffer_desc.data = SG_RANGE(tri_vertices);
	vbuffer_desc.label = "tri vertices";
	GlobalState.bind.vertex_buffers[0] = sg_make_buffer(&vbuffer_desc);

    sg_shader tri_shader = sg_make_shader(triangle_shader_desc(sg_query_backend()));

	sg_pipeline_desc tri_pipeline_desc = {};
	tri_pipeline_desc.shader = tri_shader;
	tri_pipeline_desc.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
	tri_pipeline_desc.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
	tri_pipeline_desc.label = "tri pipeline";

	GlobalState.pip = sg_make_pipeline(&tri_pipeline_desc);
	sg_pass_action tri_pass_action;
	tri_pass_action.colors[0].load_action = SG_LOADACTION_CLEAR;
	// tri_pass_action.colors[0].clear_value = {0.0f, 0.0f, 0.0f, 1.0f};
	GlobalState.pass_action = tri_pass_action;
}

void thepit::Frame(void* State)
{
	sg_pass tri_draw = {};
	tri_draw.action = GlobalState.pass_action;
	tri_draw.swapchain = sglue_swapchain();
	sg_begin_pass(&tri_draw);
	sg_apply_pipeline(GlobalState.pip);
	sg_apply_bindings(&GlobalState.bind);
	sg_draw(0, 3, 1);
	sg_end_pass();
	sg_commit();
}

void thepit::Cleanup(void* GlobalState)
{
	sg_shutdown();
}

void thepit::HandleEvent(const sapp_event* Event, void* GlobalState)
{
}
