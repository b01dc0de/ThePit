#include "Common.h"
#include "Engine.h"
#include "Camera.h"
#include "DebugGraphics.h"
#include "Input.h"
#include "AudioManager.h"

namespace ThePit
{
    namespace Engine
    {
        StateT GlobalState;

        int global_argc = 0;
        char** global_argv = nullptr;

        void Init()
        {
            glm::vec3 fps_cam_pos{ 0.0f, -2.5f, -5.0f };
            glm::vec3 fps_init_lookdir{ 0.0f, 0.0f, 1.0f };
            Engine::GlobalState.shooter.Init(fps_cam_pos, fps_init_lookdir);

            Engine::GlobalState.gfx.Init();

            AudioManager::init_audio_manager();
            AudioManager::load(ThePit::AUDIO_ASSETS::MUSIC, "sounds/GIRL-HELL-1999.mp3");
            AudioManager::load(ThePit::AUDIO_ASSETS::SHOOT, "gun-gunshot-01.mp3");

            sapp_lock_mouse(true);
        }

        void Frame()
        {
            Input::UpdateButtonState();
            Engine::GlobalState.shooter.UpdateState();

            glm::mat4 mvp = Engine::GlobalState.shooter.GetMVP();
            glm::mat4 model_to_world = glm::mat4(1.0f);

            Engine::GlobalState.gfx.DrawFrame(mvp);

            Input::ClearMouseState(); // CKA_TODO: Figure out a nicer way of doing this
        }

        void Cleanup()
        {
            Engine::GlobalState.gfx.Term();
            AudioManager::deinit_audio_manager();
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
                    if (Event->key_code == SAPP_KEYCODE_F1 && Event->type == SAPP_EVENTTYPE_KEY_UP) {
                        Engine::GlobalState.lock_mouse = !Engine::GlobalState.lock_mouse;
                        sapp_lock_mouse(Engine::GlobalState.lock_mouse);
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
                    sapp_lock_mouse(Engine::GlobalState.lock_mouse);
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

    } // namespace Engine
} // namespace ThePit
