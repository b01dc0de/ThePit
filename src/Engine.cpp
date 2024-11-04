#include "Engine.h"
#include "Camera.h"
#include "Cube.h"
#include "DrawState.h"
#include "Input.h"
#include "MeshUtils.h"
#include <string>

namespace ThePit
{
    GlobalState_t GlobalState;

    int global_argc = 0;
    char** global_argv = nullptr;

    const HMM_Vec3 Origin{ 0.0f, 0.0f, 0.0f };
    const HMM_Vec3 CamPos{ 0.0f, 1.5f, 10.0f };

    void Init()
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

        GlobalState.coltex_drawstate = InitNewColorTexturePipeline();

        ColorT red_color = { 1.0f, 0.0f, 0.0f, 1.0f };
        GlobalState.singlecolorcube = InitNewCubeSingleColorGeometry(red_color);
        GlobalState.floormesh = InitNewFloorMesh();

        v3 fps_cam_pos{ 0.0f, -2.5f, -5.0f };
        v3 fps_init_lookdir{ 0.0f, 0.0f, 1.0f };
        GlobalState.shooter.Init(fps_cam_pos, fps_init_lookdir);
        GlobalState.skyboxmesh = InitNewSkyboxMesh();

        GlobalState.unicolor_drawstate = InitNewUnicolorPipeline();
        GlobalState.unicolorcube = InitNewCubeColorGeometry();

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

    void Frame()
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
        HMM_Mat4 model_to_world = HMM_M4D(1.0f);

        MeshDrawStateT colcube_meshdrawstate{ GlobalState.colcube_geometry, model_to_world };
        MeshDrawStateT singlecolorcube_meshdrawstate{ GlobalState.singlecolorcube, model_to_world };
        MeshDrawStateT texcube_meshdrawstate{ GlobalState.texcube_geometry, model_to_world };
        MeshDrawStateT floor_meshdrawstate{ GlobalState.floormesh, model_to_world };
        MeshDrawStateT skybox_meshdrawstate{ GlobalState.skyboxmesh, model_to_world };
        MeshDrawStateT unicolorcube_meshdrawstate{ GlobalState.unicolorcube, HMM_Translate(HMM_Vec3{5.0f, 25.0f, 5.0f}) };
        
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
                Draw(GlobalState.col_drawstate, &colcube_meshdrawstate, mvp);
            } break;
            case DrawPassType::DRAWPASS_SINGLECOLOR:
            {
                Draw(GlobalState.col_drawstate, &singlecolorcube_meshdrawstate, mvp);
            } break;
            case DrawPassType::DRAWPASS_TEXTURE:
            {
                Draw(GlobalState.tex_drawstate, &texcube_meshdrawstate, mvp);
            } break;
            default:
            {
                THEPIT_ASSERT(false);
            } break;
        }
        static bool bFloor = true;
        if (bFloor)
        {
            Draw(GlobalState.tex_drawstate, &floor_meshdrawstate, mvp);
        }
        static bool bSkybox = true;
        if (bSkybox)
        {
            Draw(GlobalState.coltex_drawstate, &skybox_meshdrawstate, mvp);
        }
        static bool bUnicolorCube = true;
        if (bUnicolorCube)
        {
            DrawUnicolor(GlobalState.unicolor_drawstate, &unicolorcube_meshdrawstate, mvp);
        }

        EndFrameHelper();

        Input::ClearMouseState(); // CKA_TODO: Figure out a nicer way of doing this
    }

    void Cleanup()
    {
        sg_shutdown();

        delete GlobalState.cube_mesh;
        delete GlobalState.cube_material;

        delete GlobalState.texcube_geometry;
        delete GlobalState.tex_drawstate;
        delete GlobalState.col_drawstate;
    }

    void HandleEvent(const sapp_event* Event)
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
            case SAPP_EVENTTYPE_INVALID:
            {
                THEPIT_ASSERT(false);
            } break;
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
            case SAPP_EVENTTYPE_RESTORED:
            case SAPP_EVENTTYPE_FOCUSED:
            case SAPP_EVENTTYPE_RESUMED:
            {
                sapp_lock_mouse(true);
            } break;
            case SAPP_EVENTTYPE_CHAR:
            case SAPP_EVENTTYPE_TOUCHES_BEGAN:
            case SAPP_EVENTTYPE_TOUCHES_MOVED:
            case SAPP_EVENTTYPE_TOUCHES_ENDED:
            case SAPP_EVENTTYPE_TOUCHES_CANCELLED:
            case SAPP_EVENTTYPE_RESIZED:
            case SAPP_EVENTTYPE_ICONIFIED:
            case SAPP_EVENTTYPE_UNFOCUSED:
            case SAPP_EVENTTYPE_SUSPENDED:
            case SAPP_EVENTTYPE_QUIT_REQUESTED:
            case SAPP_EVENTTYPE_CLIPBOARD_PASTED:
            case SAPP_EVENTTYPE_FILES_DROPPED:
            default:
            {
                // Unhandled
            } break;
        }
    }
} // namespace ThePit
