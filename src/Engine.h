#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include <stdio.h>
// #include "Common.h"
#include "../libs/sokol/sokol_gfx.h"
#include "../libs/sokol/sokol_glue.h"
#include "engine/geometry/cube.h"
#include "engine/material/material.h"
#include "engine/mesh/mesh.h"

struct sapp_event;

namespace thepit
{
	struct State
	{
		sg_pipeline pip;
		sg_bindings bind;
		sg_pass_action pass_action;
    	Material cube_material;
		Mesh cube_mesh;
		float rx, ry;
	};
	extern State GlobalState;

	void Init(void* State);
	void Frame(void* State);
	void Cleanup(void* State);
	void HandleEvent(const sapp_event* Event, void* State);
}

#endif // ENGINE_H
