#ifndef THEPIT_MESH_H
#define THEPIT_MESH_H

#include "Common.h"
#include "Material.h"
#include "Geometry.h"

namespace ThePit
{
    // Struct to represent a 3D transformation
    struct Transform
    {
        v3 position = {};
        v3 rotation = {};  // Rotation in radians (X, Y, Z)
        v3 scale = {};     // Scale (X, Y, Z)
    };

    Transform InitDefaultTransform();

    // Struct to represent a 3D Mesh
    struct Mesh
    {
        const GeometryT* geometry = nullptr;
        const Material* material = nullptr;        // Pointer to the material data
        Transform transform = {};             // Transform data
        sg_pipeline pipeline = {};
        sg_bindings bindings = {};
    };

    // Initialize a Mesh with geometry and material
    Mesh* InitNewMesh(const GeometryT* geometry, const Material* material);

    // Draw the mesh
    void DrawMesh(const Mesh* mesh);
} // namespace ThePit

#endif  // THEPIT_ENGINE_MESH_H