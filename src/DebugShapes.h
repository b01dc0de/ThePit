#ifndef THEPIT_DEBUGSHAPES_H
#define THEPIT_DEBUGSHAPES_H

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
}

#endif // THEPIT_DEBUGSHAPES_H