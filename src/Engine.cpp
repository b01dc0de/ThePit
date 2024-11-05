#include "Common.h"
#include "Engine.h"
#include "Camera.h"
#include "DebugGraphics.h"
#include "Input.h"

namespace ThePit
{
    GlobalState_t GlobalState;

    int global_argc = 0;
    char** global_argv = nullptr;

    const glm::vec3 Origin{ 0.0f, 0.0f, 0.0f };
    const glm::vec3 CamPos{ 0.0f, 1.5f, 10.0f };

    void Init()
    {
        glm::vec3 fps_cam_pos{ 0.0f, -2.5f, -5.0f };
        glm::vec3 fps_init_lookdir{ 0.0f, 0.0f, 1.0f };
        GlobalState.shooter.Init(fps_cam_pos, fps_init_lookdir);

        GlobalState.gfx.Init();

        sapp_lock_mouse(true);
    }

    void Frame()
    {
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

        static bool bFPS = true;
        if (bFPS)
        {
            mvp = GlobalState.shooter.GetMVP();
            mvp_range = SG_RANGE(mvp);
        }

        GlobalState.gfx.DrawFrame(mvp);

        Input::ClearMouseState(); // CKA_TODO: Figure out a nicer way of doing this
    }

    void Cleanup()
    {
        GlobalState.gfx.Term();
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
