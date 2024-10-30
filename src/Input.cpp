#include "Input.h"

namespace ThePit
{

    static const int max_active_buttons = 8;
    ButtonStateT active_buttons[max_active_buttons];

#define ENABLE_INPUT_DBGPRINT() (THEPIT_CONFIG_DEBUG() && 0)
#if ENABLE_INPUT_DBGPRINT()
    #define INPUT_DBGPRINT(...) DBG_LOGF(__VA_ARGS)
#else // ENABLE_INPUT_DBGPRINT()
    #define INPUT_DBGPRINT(...) THEPIT_NOOP()
#endif // ENABLE_INPUT_DBGPRINT()

    bool Input::GetButtonState(sapp_keycode key)
    {
        bool result = false;
        for (int idx = 0; idx < max_active_buttons; idx++)
        {
            if (key == active_buttons[idx].key)
            {
                result = active_buttons[idx].state > 0;
                break;
            }
        }
        return result;
    }

    void Input::UpdateButtonState()
    {
        for (int idx = 0; idx < max_active_buttons; idx++)
        {
            if (SAPP_KEYCODE_INVALID != active_buttons[idx].key)
            {
                INPUT_DBGPRINT("\t\t++active_buttons[%d].state (%d) (Key: %d)\n", idx, active_buttons[idx].state, active_buttons[idx].key);
                active_buttons[idx].state++;
            }
        }
    }

    MouseStateT global_mouse_state;

    void Input::GetMouseDelta(float& out_dx, float& out_dy)
    {
        out_dx = global_mouse_state.dx;
        out_dy = global_mouse_state.dy;
    }

    void Input::ClearMouseState()
    {
        global_mouse_state.dx = 0.0f;
        global_mouse_state.dy = 0.0f;
    }

    void Input::HandleMouseEvent(const sapp_event* in_event)
    {
        THEPIT_ASSERT(in_event);
        switch (in_event->type)
        {
            case SAPP_EVENTTYPE_MOUSE_MOVE:
            case SAPP_EVENTTYPE_MOUSE_ENTER:
            case SAPP_EVENTTYPE_MOUSE_LEAVE:
            case SAPP_EVENTTYPE_MOUSE_SCROLL:
            case SAPP_EVENTTYPE_MOUSE_DOWN:
            case SAPP_EVENTTYPE_MOUSE_UP:
            {
                global_mouse_state.dx = in_event->mouse_dx;
                global_mouse_state.dy = in_event->mouse_dy;
            } break;
            default:
            {
                global_mouse_state.dx = 0.0f;
                global_mouse_state.dy = 0.0f;
            } break;
        }
    }

    void Input::HandleKeyEvent(const sapp_event* in_event)
    {
        static bool b_init = false;
        if (!b_init)
        {
            b_init = true;
            for (int idx = 0; idx < max_active_buttons; idx++)
            {
                active_buttons[idx].key = SAPP_KEYCODE_INVALID;
                active_buttons[idx].state = 0;
            }
        }

        THEPIT_ASSERT(in_event);
        THEPIT_ASSERT(SAPP_EVENTTYPE_KEY_DOWN == in_event->type || SAPP_EVENTTYPE_KEY_UP == in_event->type);
        bool button_down = SAPP_EVENTTYPE_KEY_DOWN == in_event->type;
        sapp_keycode key = in_event->key_code;
        bool key_state = GetButtonState(key);
        THEPIT_ASSERT(SAPP_KEYCODE_INVALID != key);
        if (button_down && !key_state)
        {
            for (int idx = 0; idx < max_active_buttons; idx++)
            {
                if (SAPP_KEYCODE_INVALID == active_buttons[idx].key)
                {
                    INPUT_DBGPRINT("\t\tSet active_buttons[%d].state == 1, (Key: %d)\n", idx, active_buttons[idx].key);
                    active_buttons[idx].key = key;
                    active_buttons[idx].state = 1;
                    break;
                }
            }
        }
        else if (!button_down && key_state)
        {
            for (int idx = 0; idx < max_active_buttons; idx++)
            {
                if (key == active_buttons[idx].key)
                {
                    INPUT_DBGPRINT("\t\tCleared active_buttons[%d], (Key: %d)\n", idx, active_buttons[idx].key);
                    active_buttons[idx].key = SAPP_KEYCODE_INVALID;
                    active_buttons[idx].state = 0;
                    break;
                }
            }
        }
    }
} // namespace ThePit