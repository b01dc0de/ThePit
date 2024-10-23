#ifndef THEPIT_ENGINE_MESH_H
#define THEPIT_ENGINE_MESH_H

#include "Common.h"
#include "../material/material.h"
#include "../geometry/geometry.h"
#include "../material/cube-sapp.glsl.h"


// Struct to represent a 3D transformation
struct Transform {
    float position[3];
    float rotation[3];  // Rotation in radians (X, Y, Z)
    float scale[3];     // Scale (X, Y, Z)
};

// Struct to represent a 3D Mesh
struct Mesh {
    const GeometryStruct* geometry;  // Pointer to the geometry data
    const Material* material;        // Pointer to the material data
    Transform transform;             // Transform data
    sg_pipeline pipeline;
    sg_bindings bindings;
};

// Initialize a Mesh with geometry and material
Mesh mesh_init(const GeometryStruct* geometry, const Material* material);

// Draw the mesh
void mesh_draw(const Mesh* mesh);

#endif  // THEPIT_ENGINE_MESH_H