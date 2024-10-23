#include "material.h"
#include "glsl/cube-sapp.glsl.h"

// Initialize the material by creating the shader and pipeline
Material material() {
    Material material;

    material.shader = sg_make_shader(cube_shader_desc(sg_query_backend()));
    return material;
}