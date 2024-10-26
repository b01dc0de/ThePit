#ifndef THEPIT_DRAWSTATE_H
#define THEPIT_DRAWSTATE_H

#include "Common.h"
#include "Geometry.h"

namespace thepit
{
    // State needed to draw a specific mesh
    using MeshDrawT = GeometryT;

    // State needed for a GL draw call
    struct DrawStateT
    {
        sg_pipeline pip;
        sg_bindings bind;
    };

    sg_pass* GetDefaultSGPass();
    DrawStateT* InitNewTexturePipeline();
    DrawStateT* InitNewColorPipeline();
    void Draw(DrawStateT* InState, MeshDrawT* InMesh, sg_range& in_vsparams_range);
}

#endif // THEPIT_DRAWSTATE_H