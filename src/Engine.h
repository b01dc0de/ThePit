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
		MeshDrawT* colcube_geometry = nullptr;
		DrawStateT* col_drawstate = nullptr;

		GeometryT* singlecolorcube = nullptr;

		sg_shader_desc test_vxcolor_desc;
		sg_shader_desc test_vxtexture_desc;
		//sg_shader_desc test_vxunicolor_desc;
	};
	extern GlobalState_t GlobalState;

	extern int global_argc;
	extern char** global_argv;

	void Init();
	void Frame();
	void Cleanup();
	void HandleEvent(const sapp_event* Event);

	void HandleCmdLine(int argc, char** argv);
	const char* GetProjectDir();

    const int WindowWidth = 640;
    const int WindowHeight = 480;
}

#endif // ENGINE_H
