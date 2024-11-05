#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "Common.h"
#include "Camera.h"
#include "Graphics.h"

namespace ThePit
{
    struct GlobalState_t
    {
        FPSView shooter;
        bool lock_mouse = true;
        Graphics::StateT gfx;
    };
    extern GlobalState_t GlobalState;

    extern int global_argc;
    extern char** global_argv;

    void Init();
    void Frame();
    void Cleanup();
    void HandleEvent(const sapp_event* Event);

    const int WindowWidth = 1280; // 640
    const int WindowHeight = 960; // 480
} // namespace ThePit

#endif // ENGINE_H
