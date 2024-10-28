#include "Engine.h"
#include "Camera.h"
#include "Cube.h"
#include "DrawState.h"
#include "Input.h"
#include "MeshUtils.h"
#include "Shader.h"
#include <string>

namespace thepit
{
    GlobalState_t GlobalState;

	int global_argc = 0;
	char** global_argv = nullptr;

    const HMM_Vec3 Origin{ 0.0f, 0.0f, 0.0f };
    const HMM_Vec3 CamPos{ 0.0f, 1.5f, 10.0f };
}

void thepit::Init()
{
    sg_desc setup = {};
    setup.environment = sglue_environment();
    setup.logger.func = slog_func;
    sg_setup(&setup);

    GeometryT* cube = InitNewCubeColorGeometry();

    GlobalState.texcube_geometry = InitNewCubeTexGeometry();
    GlobalState.tex_drawstate = InitNewTexturePipeline();
    GlobalState.colcube_geometry = cube;
    GlobalState.col_drawstate = InitNewColorPipeline();

    ColorT red_color = { 1.0f, 0.0f, 0.0f, 1.0f };
    GlobalState.singlecolorcube = InitNewCubeSingleColorGeometry(red_color);
    GlobalState.floormesh = InitNewFloorMesh();

    v3 fps_cam_pos{ 0.0f, -2.5f, -5.0f };
    v3 fps_init_lookdir{ 0.0f, 0.0f, 1.0f };
    GlobalState.shooter.Init(fps_cam_pos, fps_init_lookdir);

    sapp_lock_mouse(true);
}

enum struct DrawPassType
{
    DRAWPASS_COLOR,
    DRAWPASS_SINGLECOLOR,
    DRAWPASS_TEXTURE,
    DRAWPASS_NUM
};
static DrawPassType curr_drawpass = DrawPassType::DRAWPASS_COLOR;

void thepit::Frame()
{
    Input::UpdateButtonState();
    GlobalState.shooter.UpdateState();

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
    HMM_Mat4 mvp = HMM_Mul(camera_persp.vp, model);
    sg_range mvp_range = SG_RANGE(mvp);
    
    static bool bFPS = true;
    if (bFPS)
    {
        mvp = GlobalState.shooter.GetMVP();
        mvp_range = SG_RANGE(mvp);
    }
    
    auto BeginFrameHelper = []() -> void
    {
        sg_begin_pass(GetDefaultSGPass());
    };

    auto EndFrameHelper = []() -> void
    {
        sg_end_pass();
        sg_commit();
    };

    BeginFrameHelper();

    switch (curr_drawpass)
    {
        case DrawPassType::DRAWPASS_COLOR:
        {
            Draw(GlobalState.col_drawstate, GlobalState.colcube_geometry, mvp_range);
        } break;
        case DrawPassType::DRAWPASS_SINGLECOLOR:
        {
            Draw(GlobalState.col_drawstate, GlobalState.singlecolorcube, mvp_range);
        } break;
        case DrawPassType::DRAWPASS_TEXTURE:
        {
            Draw(GlobalState.tex_drawstate, GlobalState.texcube_geometry, mvp_range);
        } break;
        default:
        {
            THEPIT_ASSERT(false);
        } break;
    }
    static bool bFloor = true;
    if (bFloor)
    {
        Draw(GlobalState.tex_drawstate, GlobalState.floormesh, mvp_range);
    }

    EndFrameHelper();

    Input::ClearMouseState(); // CKA_TODO: Figure out a nicer way of doing this
}

void thepit::Cleanup()
{
    sg_shutdown();

    delete GlobalState.cube_mesh;
    delete GlobalState.cube_material;

    delete GlobalState.texcube_geometry;
    delete GlobalState.tex_drawstate;
    delete GlobalState.col_drawstate;
}

void thepit::HandleEvent(const sapp_event* Event)
{
    auto HandleDemoSpacebar = [&](const sapp_event* Event) -> void
    {
        if (SAPP_EVENTTYPE_KEY_DOWN == Event->type && 0 == Event->key_repeat && SAPP_KEYCODE_SPACE == Event->key_code)
        {
            curr_drawpass = (DrawPassType)(((int)curr_drawpass + 1) % (int)DrawPassType::DRAWPASS_NUM);
        }
    };

    switch (Event->type)
    {
        case SAPP_EVENTTYPE_KEY_DOWN:
        case SAPP_EVENTTYPE_KEY_UP:
        {
            HandleDemoSpacebar(Event);
            Input::HandleKeyEvent(Event);
        } break;
        case SAPP_EVENTTYPE_MOUSE_MOVE:
        case SAPP_EVENTTYPE_MOUSE_ENTER:
        case SAPP_EVENTTYPE_MOUSE_LEAVE:
        case SAPP_EVENTTYPE_MOUSE_SCROLL:
        case SAPP_EVENTTYPE_MOUSE_DOWN:
        case SAPP_EVENTTYPE_MOUSE_UP:
        {
            Input::HandleMouseEvent(Event);
        } break;
        default: { } break;
    }
}

void thepit::HandleCmdLine(int argc, char** argv)
{
	global_argc = argc;
	global_argv = argv;
}

// CKA_NOTE: This currently tries to find the base project directory using a naive method
//      - This function parses for the first instance of 'ThePit' in the executable filename
//      - If thepit executable file is '/home/username/wrk/ThePit/out/build/platform/thepit'
//      - Then this function would return "/home/username/wrk/ThePit"
const char* thepit::GetProjectDir()
{
    static const char* project_name = "ThePit";
    static const char* project_dir = nullptr;
    static std::string project_dir_str;
    if (!project_dir)
    {
        THEPIT_ASSERT(0 < global_argc);
        project_dir_str = global_argv[0];
        size_t ThePitDir = project_dir_str.find(project_name);
        project_dir_str = project_dir_str.substr(0, ThePitDir + strlen(project_name));
        project_dir = project_dir_str.c_str();
    }
    return project_dir;
}

