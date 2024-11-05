#ifndef THEPIT_GRAPHICS_H
#define THEPIT_GRAPHICS_H

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

    enum struct DrawStateTypeE
    {
        Color,
        Texture,
        ColorTexture,
        Unicolor,
        Num
    };

    // State needed for a GL draw call
    struct DrawStateT
    {
        sg_pipeline pip;
        sg_bindings bind;
    };

    sg_pass* GetDefaultSGPass();
    DrawStateT* GetDrawState(DrawStateTypeE draw_state_type);
    DrawStateT* InitNewTexturePipeline();
    DrawStateT* InitNewColorPipeline();
    DrawStateT* InitNewColorTexturePipeline();
    DrawStateT* InitNewUnicolorPipeline();
    void Draw(DrawStateT* draw_state, MeshDrawStateT* mesh_state, glm::mat4& view_proj);
    void DrawUnicolor(DrawStateT* draw_state, MeshDrawStateT* mesh_state, glm::mat4& view_proj, glm::vec4& in_color);

    namespace Graphics
    {
        struct StateT
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

            void Init();
            void DrawFrame(const glm::mat4& vp);
            void Term();
        };
    } // namespace Graphics

} // namespace ThePit

#endif // THEPIT_GRAPHICS_H