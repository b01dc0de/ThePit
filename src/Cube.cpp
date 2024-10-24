#include "Cube.h"
#include "Geometry.h"

namespace thepit
{
    static const VxColor cube_vertices[] =
    {
        {{-1.0, -1.0, -1.0},   {1.0, 0.0, 0.0, 1.0}},
        {{1.0, -1.0, -1.0},   {1.0, 0.0, 0.0, 1.0}},
        {{1.0,  1.0, -1.0},   {1.0, 0.0, 0.0, 1.0}},
        {{-1.0,  1.0, -1.0},   {1.0, 0.0, 0.0, 1.0}},

        {{-1.0, -1.0,  1.0},   {0.0, 1.0, 0.0, 1.0}},
        {{1.0, -1.0,  1.0},   {0.0, 1.0, 0.0, 1.0}},
        {{1.0,  1.0,  1.0},   {0.0, 1.0, 0.0, 1.0}},
        {{-1.0,  1.0,  1.0},   {0.0, 1.0, 0.0, 1.0}},

        {{-1.0, -1.0, -1.0},   {0.0, 0.0, 1.0, 1.0}},
        {{-1.0,  1.0, -1.0},   {0.0, 0.0, 1.0, 1.0}},
        {{-1.0,  1.0,  1.0},   {0.0, 0.0, 1.0, 1.0}},
        {{-1.0, -1.0,  1.0},   {0.0, 0.0, 1.0, 1.0}},

        {{1.0, -1.0, -1.0},    {1.0, 0.5, 0.0, 1.0}},
        {{1.0,  1.0, -1.0},    {1.0, 0.5, 0.0, 1.0}},
        {{1.0,  1.0,  1.0},    {1.0, 0.5, 0.0, 1.0}},
        {{1.0, -1.0,  1.0},    {1.0, 0.5, 0.0, 1.0}},

        {{-1.0, -1.0, -1.0},   {0.0, 0.5, 1.0, 1.0}},
        {{-1.0, -1.0,  1.0},   {0.0, 0.5, 1.0, 1.0}},
        {{1.0, -1.0,  1.0},   {0.0, 0.5, 1.0, 1.0}},
        {{1.0, -1.0, -1.0},   {0.0, 0.5, 1.0, 1.0}},

        {{-1.0,  1.0, -1.0},   {1.0, 0.0, 0.5, 1.0}},
        {{-1.0,  1.0,  1.0},   {1.0, 0.0, 0.5, 1.0}},
        {{1.0,  1.0,  1.0},   {1.0, 0.0, 0.5, 1.0}},
        {{1.0,  1.0, -1.0},   {1.0, 0.0, 0.5, 1.0}}
    };

    static const TriInds cube_indices[] =
    {
        {0, 1, 2},        {0, 2, 3},
        {6, 5, 4},        {7, 6, 4},
        {8, 9, 10},       {8, 10, 11},
        {14, 13, 12},     {15, 14, 12},
        {16, 17, 18},     {16, 18, 19},
        {22, 21, 20},     {23, 22, 20}
    };

    const int cube_element_count = (int)(ARRAY_SIZE(cube_indices) * TriIdxCount);

    GeometryT* InitNewCubeGeometry()
    {
        GeometryT* pnew_geometry = new GeometryT;

        // Generate vertices
        pnew_geometry->vertices = (const float*)cube_vertices;
        pnew_geometry->indices = cube_indices;
        pnew_geometry->element_count = cube_element_count;

        sg_buffer_desc vertex_buffer_desc = {};
        vertex_buffer_desc.data = SG_RANGE(cube_vertices);
        vertex_buffer_desc.type = SG_BUFFERTYPE_VERTEXBUFFER;
        vertex_buffer_desc.usage = SG_USAGE_IMMUTABLE;  // We assume this geometry won't change

        // Set up the vertex buffer description
        pnew_geometry->vertex_buffer = sg_make_buffer(&vertex_buffer_desc);

        sg_buffer_desc index_buffer_desc = {};
        index_buffer_desc.data = SG_RANGE(cube_indices);
        index_buffer_desc.type = SG_BUFFERTYPE_INDEXBUFFER;
        index_buffer_desc.usage = SG_USAGE_IMMUTABLE;  // We assume this geometry won't change

        pnew_geometry->index_buffer = sg_make_buffer(&index_buffer_desc);

        return pnew_geometry;
    }

}