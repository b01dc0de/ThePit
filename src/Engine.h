#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "Common.h"
#include "Camera.h"
#include "Graphics.h"

namespace ThePit
{
    struct GlobalState_t
    {
        DrawStateT* tex_drawstate = nullptr;
        DrawStateT* col_drawstate = nullptr;
        DrawStateT* coltex_drawstate = nullptr;
        DrawStateT* unicolor_drawstate = nullptr;

        GeometryT* texcube_geometry = nullptr;
        GeometryT* colcube_geometry = nullptr;
        GeometryT* unicolorcube = nullptr;

        GeometryT* floormesh = nullptr;
        GeometryT* skyboxmesh = nullptr;

        FPSView shooter;
        bool lock_mouse = true;
    };
    extern GlobalState_t GlobalState;

    extern int global_argc;
    extern char** global_argv;

    void Init();
    void Frame();
    void Cleanup();
    void HandleEvent(const sapp_event* Event);

    //const int WindowWidth = 640;
    //const int WindowHeight = 480;
    const int WindowWidth = 1280;
    const int WindowHeight = 960;
} // namespace ThePit

#endif // ENGINE_H
