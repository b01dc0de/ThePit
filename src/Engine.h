#ifndef THEPIT_ENGINE_H
#define THEPIT_ENGINE_H

#include "Common.h"
#include "Material.h"
#include "Mesh.h"
#include "DrawState.h"
#include "Camera.h"

namespace ThePit
{
    struct GlobalState_t
    {
        Material* cube_material = nullptr;
        Mesh* cube_mesh = nullptr;

        GeometryT* texcube_geometry = nullptr;
        DrawStateT* tex_drawstate = nullptr;
        GeometryT* colcube_geometry = nullptr;
        DrawStateT* col_drawstate = nullptr;

        DrawStateT* coltex_drawstate = nullptr;

        GeometryT* singlecolorcube = nullptr;
        GeometryT* floormesh = nullptr;
        GeometryT* skyboxmesh = nullptr;

        FPSView shooter;
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
