#ifndef THEPIT_DEBUGGRAPHICS_H
#define THEPIT_DEBUGGRAPHICS_H

#include "Common.h"
#include "Geometry.h"

namespace ThePit
{
    enum struct DebugShapeGeometryE
    {
        Color,
        Texture,
        Unicolor,
        TypeCount
    };

    GeometryT* GetCubeGeometry(DebugShapeGeometryE in_geo_type);
    GeometryT* InitNewFloorMesh();
    GeometryT* InitNewSkyboxMesh();
}

#endif // THEPIT_DEBUGSHAPES_H