#ifndef THEPIT_INPUT_H
#define THEPIT_INPUT_H

#include "Common.h"

namespace ThePit
{
    struct ButtonStateT
    {
        sapp_keycode key;
        int state;
    };

    struct MouseStateT
    {
        float dx = 0.0f;
        float dy = 0.0f;
    };

    struct Input
    {
        static bool GetButtonState(sapp_keycode key);
        static void UpdateButtonState();
        static void HandleKeyEvent(const sapp_event* in_event);

        static void GetMouseDelta(float& out_dx, float& out_dy);
        static void ClearMouseState();
        static void HandleMouseEvent(const sapp_event* in_event);
    };
} // namespace ThePit

#endif // THEPIT_INPUT_H