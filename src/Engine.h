#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "Common.h"
#include "Camera.h"
#include "Graphics.h"

namespace ThePit
{
    namespace Engine
    {
        struct StateT
        {
            FPSView shooter;
            bool lock_mouse = true;
            bool playing_music = false;

            Graphics::StateT gfx;
        };
        extern StateT GlobalState;
        extern int global_argc;
        extern char** global_argv;

        void Init();
        void Frame();
        void Cleanup();
        void HandleEvent(const sapp_event* Event);

        const int WindowWidth = 1280; // 640
        const int WindowHeight = 960; // 480

    } // namespace Engine
} // namespace ThePit

#endif // ENGINE_H
