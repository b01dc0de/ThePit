#include "ThePit_Engine.h"

#include "glsl/thepit-triangle.glsl.h"

struct thepit_state GlobalState;

struct AppState
{
	sg_pipeline pip;
	sg_bindings bind;
	sg_pass_action pass_action;
} state;

void thepit_init(void* State)
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
	state.bind.vertex_buffers[0] = sg_make_buffer(&vbuffer_desc);

    sg_shader tri_shader = sg_make_shader(triangle_shader_desc(sg_query_backend()));

	sg_pipeline_desc tri_pipeline_desc = {};
	tri_pipeline_desc.shader = tri_shader;
	tri_pipeline_desc.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
	tri_pipeline_desc.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
	tri_pipeline_desc.label = "tri pipeline";

	state.pip = sg_make_pipeline(&tri_pipeline_desc);
	sg_pass_action tri_pass_action;
	tri_pass_action.colors[0].load_action = SG_LOADACTION_CLEAR;
	// tri_pass_action.colors[0].clear_value = {0.0f, 0.0f, 0.0f, 1.0f};
	state.pass_action = tri_pass_action;
}

void thepit_frame(void* State)
{
	sg_pass tri_draw = {};
	tri_draw.action = state.pass_action;
	tri_draw.swapchain = sglue_swapchain();
	sg_begin_pass(&tri_draw);
	sg_apply_pipeline(state.pip);
	sg_apply_bindings(&state.bind);
	sg_draw(0, 3, 1);
	sg_end_pass();
	sg_commit();
}

void thepit_cleanup(void* State)
{
	sg_shutdown();
}

void thepit_event(const sapp_event* Event, void* State)
{
}
