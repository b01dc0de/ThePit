#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "Common.h"
#include "Material.h"
#include "Mesh.h"
#include "DrawState.h"

namespace thepit
{
	struct GlobalState_t
	{
		sg_pipeline pip = {};
		sg_bindings bind = {};
		sg_pass_action pass_action = {};

		Material* cube_material = nullptr;
		Mesh* cube_mesh = nullptr;

		MeshDrawT* texcube_geometry = nullptr;
		DrawStateT* tex_drawstate = nullptr;
	};
	extern GlobalState_t GlobalState;

	void Init();
	void Frame();
	void Cleanup();
	void HandleEvent(const sapp_event* Event);

    const int WindowWidth = 640;
    const int WindowHeight = 480;
}

#endif // ENGINE_H
