#include "Mesh.h"
#include "glsl/cube-sapp.glsl.h"

namespace thepit
{
    Transform InitDefaultTransform()
    {
        Transform result;
        result.position = { 0.0f, 0.0f, 0.0f };
        result.rotation = { 0.0f, 0.0f, 0.0f };
        result.scale = { 1.0f, 1.0f, 1.0f };
        return result;
    }

    Mesh* InitNewMesh(const GeometryT* geometry, const Material* material)
    {
        Mesh* pmesh = new Mesh{};
        pmesh->geometry = geometry;
        pmesh->material = material;
        pmesh->bindings = {};
        pmesh->bindings.vertex_buffers[0] = geometry->vertex_buffer;
        pmesh->bindings.index_buffer = geometry->index_buffer;

        sg_pipeline_desc shader_pip = {};
        /* test to provide buffer stride, but no attr offsets */
        shader_pip.layout.buffers[0].stride = sizeof(v3) + sizeof(v4);
        shader_pip.layout.attrs[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3;
        shader_pip.layout.attrs[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4;
        shader_pip.shader = material->shader;
        shader_pip.index_type = SG_INDEXTYPE_UINT16;
        shader_pip.cull_mode = SG_CULLMODE_BACK;
        shader_pip.depth.write_enabled = true;
        shader_pip.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        shader_pip.label = "cube-pipeline";
        pmesh->pipeline = sg_make_pipeline(&shader_pip);

        pmesh->transform = InitDefaultTransform();

        return pmesh;
    }

    void DrawMesh(const Mesh* mesh)
    {
        // Check if the geometry is valid
        if (!mesh || !mesh->geometry || !mesh->geometry->vertices)
        {
            // printf("Error: Invalid mesh or geometry\n");
            return;
        }

        sg_apply_pipeline(mesh->pipeline);
        sg_apply_bindings(mesh->bindings);

        // Apply bindings and draw the geometry
        sg_draw(0, mesh->geometry->element_count, 1);
    }
}
