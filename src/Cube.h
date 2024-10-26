#ifndef THEPIT_CUBE_H
#define THEPIT_CUBE_H

#include "Common.h"
#include "Geometry.h"

namespace thepit
{
    GeometryT* InitNewCubeColorGeometry();
    GeometryT* InitNewCubeSingleColorGeometry(const ColorT& in_color);
    GeometryT* InitNewCubeTexGeometry();
}

#endif
