#include "Engine.h"
#include "Cube.h"
#include "DrawState.h"
#include "Camera.h"
#include "glsl/cube-sapp.glsl.h"

namespace thepit
{
    GlobalState_t GlobalState;
}

void thepit::Init()
{
    sg_desc setup = {};
    setup.environment = sglue_environment();
    setup.logger.func = slog_func;
    sg_setup(&setup);

    // Create cube geometry, material, and mesh
    GeometryT* cube = InitNewCubeColorGeometry();  // Generate cube geometry
    GlobalState.cube_material = InitNewCubeMaterial();  // Initialize the material
    GlobalState.cube_mesh = InitNewMesh(cube, GlobalState.cube_material);  // Initialize mesh

    // Set the initial position of the cube
    GlobalState.cube_mesh->transform.position = { 0.0f, 0.0f, -1.0f }; // (move back slightly)

    GlobalState.pip = GlobalState.cube_mesh->pipeline;
    GlobalState.bind = GlobalState.cube_mesh->bindings;

    GlobalState.texcube_geometry = new MeshDrawT{ InitNewCubeTexGeometry() };
    GlobalState.tex_drawstate = InitNewTexturePipeline();
    GlobalState.colcube_geometry = new MeshDrawT{ GlobalState.cube_mesh->geometry };
    GlobalState.col_drawstate = InitNewColorPipeline();
}

void thepit::Frame()
{
    const HMM_Vec3 Origin{ 0.0f, 0.0f, 0.0f };
    const HMM_Vec3 CamPos{ 0.0f, 1.5f, 5.0f };
    const HMM_Vec3 UnitX{ 1.0f, 0.0f, 0.0f };
    const HMM_Vec3 UnitY{ 0.0f, 1.0f, 0.0f };

    static float rx = 0.0f;
    static float ry = 0.0f;
    const float frame_time = (float)sapp_frame_duration();
    rx += 1.0f * frame_time;
    ry += 2.0f * frame_time;

    CameraP camera_persp;
    camera_persp.LookAt(CamPos, Origin);
    HMM_Mat4 model = HMM_Rotate_RH(rx, UnitX) * HMM_Rotate_RH(ry, UnitY);
    camera_persp.mvp = HMM_Mul(camera_persp.mvp, model);

    /* NOTE: the vs_params_t struct has been code-generated by the shader-code-gen */
    sg_range mvp_range = SG_RANGE(camera_persp.mvp);

    static bool bTexture = false;
    if (bTexture)
    {
        Draw(GlobalState.tex_drawstate, GlobalState.texcube_geometry, mvp_range);
    }
    else
    {
        Draw(GlobalState.col_drawstate, GlobalState.colcube_geometry, mvp_range);
    }
}

void thepit::Cleanup()
{
	sg_shutdown();

    delete GlobalState.cube_mesh;
    delete GlobalState.cube_material;
}

void thepit::HandleEvent(const sapp_event* Event)
{
}
