#include "mesh.h"
#define SOKOL_DEBUG

Mesh mesh_init(const GeometryStruct* geometry, const Material* material)
{
    Mesh mesh = {};
    mesh.geometry = geometry;
    mesh.material = material;
    mesh.bindings.vertex_buffers[0] = geometry->vertex_buffer;
    mesh.bindings.index_buffer = geometry->index_buffer;

    sg_pipeline_desc shader_pip = {};
    /* test to provide buffer stride, but no attr offsets */
    shader_pip.layout.buffers[0].stride = 28;
    shader_pip.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
    shader_pip.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
    shader_pip.shader = material->shader;
    shader_pip.index_type = SG_INDEXTYPE_UINT16;
    shader_pip.cull_mode = SG_CULLMODE_BACK;
    shader_pip.depth.write_enabled = true;
    shader_pip.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
    shader_pip.label = "cube-pipeline";
    mesh.pipeline = sg_make_pipeline(&shader_pip);

    { // TODO: Clean this up
        mesh.transform = {};
        mesh.transform.position[0] = 0.0f;
        mesh.transform.position[1] = 0.0f;
        mesh.transform.position[2] = 0.0f;

        mesh.transform.rotation[0] = 0.0f;
        mesh.transform.rotation[1] = 0.0f;
        mesh.transform.rotation[2] = 0.0f;

        mesh.transform.scale[0] = 1.0f;
        mesh.transform.scale[1] = 1.0f;
        mesh.transform.scale[2] = 1.0f;
    }

    return mesh;
}

void mesh_draw(const Mesh* mesh)
{
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
