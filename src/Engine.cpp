#include "Common.h"
#include "Engine.h"
#include "Camera.h"
#include "DebugGraphics.h"
#include "Input.h"
#include "MeshUtils.h"

namespace ThePit
{
    GlobalState_t GlobalState;

    int global_argc = 0;
    char** global_argv = nullptr;

    const glm::vec3 Origin{ 0.0f, 0.0f, 0.0f };
    const glm::vec3 CamPos{ 0.0f, 1.5f, 10.0f };

    void Init()
    {
        sg_desc setup = {};
        setup.environment = sglue_environment();
        setup.logger.func = slog_func;
        sg_setup(&setup);

        simgui_desc_t imgui_setup = {};
        imgui_setup.logger.func = slog_func;
        simgui_setup(&imgui_setup);

        GlobalState.texcube_geometry = GetCubeGeometry(DebugShapeGeometryE::Texture);
        GlobalState.tex_drawstate = InitNewTexturePipeline();
        GlobalState.colcube_geometry = GetCubeGeometry(DebugShapeGeometryE::Color);
        GlobalState.col_drawstate = InitNewColorPipeline();

        GlobalState.coltex_drawstate = InitNewColorTexturePipeline();

        GlobalState.floormesh = InitNewFloorMesh();

        glm::vec3 fps_cam_pos{ 0.0f, -2.5f, -5.0f };
        glm::vec3 fps_init_lookdir{ 0.0f, 0.0f, 1.0f };
        GlobalState.shooter.Init(fps_cam_pos, fps_init_lookdir);
        GlobalState.skyboxmesh = InitNewSkyboxMesh();

        GlobalState.unicolor_drawstate = InitNewUnicolorPipeline();
        GlobalState.unicolorcube = GetCubeGeometry(DebugShapeGeometryE::Unicolor);

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
        simgui_frame_desc_t imgui_frame_desc = {};
        imgui_frame_desc.width = sapp_width();
        imgui_frame_desc.height = sapp_height();
        imgui_frame_desc.delta_time = sapp_frame_duration();
        imgui_frame_desc.dpi_scale = sapp_dpi_scale();
        simgui_new_frame(&imgui_frame_desc);

        if(ImGui::Button("Change Draw Pass Type")) {
            curr_drawpass = (DrawPassType)(((int)curr_drawpass + 1) % (int)DrawPassType::DRAWPASS_NUM);
        }

        Input::UpdateButtonState();
        GlobalState.shooter.UpdateState();

        const glm::vec3 UnitX{ 1.0f, 0.0f, 0.0f };
        const glm::vec3 UnitY{ 0.0f, 1.0f, 0.0f };

        static float rx = 0.0f;
        static float ry = 0.0f;
        const float frame_time = (float)sapp_frame_duration();
        rx += 1.0f * frame_time;
        ry += 2.0f * frame_time;

        CameraP camera_persp;
        camera_persp.LookAt(CamPos, Origin);
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), rx, UnitX) * glm::rotate(glm::mat4(1.0f), ry, UnitY);
        glm::mat4 mvp = camera_persp.vp * model;
        sg_range mvp_range = SG_RANGE(mvp);
        glm::mat4 model_to_world = glm::mat4(1.0f);

        MeshDrawStateT colcube_meshdrawstate{ GlobalState.colcube_geometry, model_to_world };
        MeshDrawStateT unicube_meshdrawstate{ GlobalState.unicolorcube, model_to_world };
        MeshDrawStateT texcube_meshdrawstate{ GlobalState.texcube_geometry, model_to_world };
        MeshDrawStateT floor_meshdrawstate{ GlobalState.floormesh, model_to_world };
        MeshDrawStateT skybox_meshdrawstate{ GlobalState.skyboxmesh, model_to_world };
        MeshDrawStateT unicolorcube_meshdrawstate{ GlobalState.unicolorcube, glm::translate(glm::mat4(1.0f), glm::vec3{5.0f, 5.0f, 5.0f}) };
        glm::vec4 color_peachy{ 0.8f, 0.4f, 0.6f, 1.0f };
        
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
            simgui_render();
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
                DrawUnicolor(GlobalState.unicolor_drawstate, &unicube_meshdrawstate, mvp, color_peachy);
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
            DrawUnicolor(GlobalState.unicolor_drawstate, &unicolorcube_meshdrawstate, mvp, color_peachy);
        }

        static bool bDrawAxis = true;
        if (bDrawAxis)
        {
            float axis_length = 1000.0f;
            float axis_width = 0.05f;
            MeshDrawStateT xaxis_meshdrawstate{ GlobalState.unicolorcube, glm::scale(glm::mat4{1.0f}, glm::vec3{axis_length, axis_width, axis_width}) };
            MeshDrawStateT yaxis_meshdrawstate{ GlobalState.unicolorcube, glm::scale(glm::mat4{1.0f}, glm::vec3{axis_width, axis_length, axis_width}) };
            MeshDrawStateT zaxis_meshdrawstate{ GlobalState.unicolorcube, glm::scale(glm::mat4{1.0f}, glm::vec3{axis_width, axis_width, axis_length}) };

            DrawUnicolor(GlobalState.unicolor_drawstate, &xaxis_meshdrawstate, mvp, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
            DrawUnicolor(GlobalState.unicolor_drawstate, &yaxis_meshdrawstate, mvp, glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
            DrawUnicolor(GlobalState.unicolor_drawstate, &zaxis_meshdrawstate, mvp, glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });
        }

        EndFrameHelper();

        Input::ClearMouseState(); // CKA_TODO: Figure out a nicer way of doing this
    }

    void Cleanup()
    {
        simgui_shutdown();
        sg_shutdown();

        delete GlobalState.cube_mesh;
        delete GlobalState.cube_material;

        delete GlobalState.texcube_geometry;
        delete GlobalState.tex_drawstate;
        delete GlobalState.col_drawstate;
    }

    void HandleEvent(const sapp_event* Event)
    {
        simgui_handle_event(Event);
        switch (Event->type)
        {
            case SAPP_EVENTTYPE_INVALID:
            {
                THEPIT_ASSERT(false);
            } break;
            case SAPP_EVENTTYPE_KEY_DOWN:
            case SAPP_EVENTTYPE_KEY_UP:
            {
                Input::HandleKeyEvent(Event);

                // Special way to get the mouse back to os control/to use imgui is F1
                if(Event->key_code == SAPP_KEYCODE_F1 && Event->type == SAPP_EVENTTYPE_KEY_UP) {
                    GlobalState.lock_mouse = !GlobalState.lock_mouse;
                    sapp_lock_mouse(GlobalState.lock_mouse);
                }
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
                sapp_lock_mouse(GlobalState.lock_mouse);
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
