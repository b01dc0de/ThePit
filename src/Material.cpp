#include "Material.h"
#include "glsl/cube-sapp.glsl.h"

namespace thepit
{
    // Initialize the material by creating the shader and pipeline
    Material* InitNewCubeMaterial()
    {
        return new Material{ sg_make_shader(cube_shader_desc(sg_query_backend())) };
    }
}