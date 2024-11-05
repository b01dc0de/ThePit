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
        glm::mat4 model_to_world;
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
    DrawStateT* InitNewUnicolorPipeline();
    void Draw(DrawStateT* draw_state, MeshDrawStateT* mesh_state, glm::mat4& view_proj);
    void DrawUnicolor(DrawStateT* draw_state, MeshDrawStateT* mesh_state, glm::mat4& view_proj, glm::vec4& in_color);
} // namespace ThePit

#endif // THEPIT_DRAWSTATE_H