#ifndef THEPIT_DRAWSTATE_H
#define THEPIT_DRAWSTATE_H

#include "Common.h"
#include "Geometry.h"

namespace ThePit
{
    // State needed to draw a specific mesh
    struct MeshDrawStateT
    {
        GeometryT* geo;
        HMM_Mat4 model_to_world;
    };

    // State needed for a GL draw call
    struct DrawStateT
    {
        sg_pipeline pip;
        sg_bindings bind;
    };

    sg_pass* GetDefaultSGPass();
    DrawStateT* InitNewTexturePipeline();
    DrawStateT* InitNewColorPipeline();
    DrawStateT* InitNewColorTexturePipeline();
    void Draw(DrawStateT* draw_state, MeshDrawStateT* mesh_state, HMM_Mat4& view_proj);
} // namespace ThePit

#endif // THEPIT_DRAWSTATE_H