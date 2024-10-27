#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "Common.h"
#include "Material.h"
#include "Mesh.h"
#include "DrawState.h"
#include "Camera.h"

namespace thepit
{
	struct GlobalState_t
	{
		Material* cube_material = nullptr;
		Mesh* cube_mesh = nullptr;

		MeshDrawT* texcube_geometry = nullptr;
		DrawStateT* tex_drawstate = nullptr;
		MeshDrawT* colcube_geometry = nullptr;
		DrawStateT* col_drawstate = nullptr;

		GeometryT* singlecolorcube = nullptr;

		FPSView shooter;
	};
	extern GlobalState_t GlobalState;

	extern int global_argc;
	extern char** global_argv;

	void Init();
	void Frame();
	void Cleanup();
	void HandleKeyEvent(const sapp_event* Event);

	void HandleCmdLine(int argc, char** argv);
	const char* GetProjectDir();

    const int WindowWidth = 640;
    const int WindowHeight = 480;
}

#endif // ENGINE_H
