#include "mesh.h"
#define SOKOL_DEBUG

Mesh mesh_init(const GeometryStruct* geometry, const Material* material) {
    Mesh mesh;
    mesh.geometry = geometry;
    mesh.material = material;

    mesh.bindings = (sg_bindings) {
        .vertex_buffers[0] = geometry->vertex_buffer,
        .index_buffer = geometry->index_buffer
    };

    auto shader_pip = (sg_pipeline_desc){
        .layout = {
            /* test to provide buffer stride, but no attr offsets */
            .buffers[0].stride = 28,
            .attrs = {
                [ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3,
                [ATTR_vs_color0].format   = SG_VERTEXFORMAT_FLOAT4
            }
        },
        .shader = material->shader,
        .index_type = SG_INDEXTYPE_UINT16,
        .cull_mode = SG_CULLMODE_BACK,
        .depth = {
            .write_enabled = true,
            .compare = SG_COMPAREFUNC_LESS_EQUAL,
        },
        .label = "cube-pipeline"
    };
    mesh.pipeline = sg_make_pipeline(&shader_pip);

    mesh.transform = (Transform){
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
        .scale = {1.0f, 1.0f, 1.0f}
    };

    return mesh;
}

void mesh_draw(const Mesh* mesh) {
    // Check if the geometry is valid
    if (!mesh || !mesh->geometry || !mesh->geometry->vertices) {
        // printf("Error: Invalid mesh or geometry\n");
        return;
    }

    sg_apply_pipeline(mesh->pipeline);
    sg_apply_bindings(mesh->bindings);

    // Apply bindings and draw the geometry
    sg_draw(0, mesh->geometry->vertex_count, 1);
}
