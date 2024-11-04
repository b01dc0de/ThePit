#ifndef THEPIT_CUBE_H
#define THEPIT_CUBE_H

#include "Common.h"
#include "Geometry.h"

namespace ThePit
{
    GeometryT* InitNewCubeColorGeometry();
    GeometryT* InitNewCubeSingleColorGeometry(const ColorT& in_color);
    GeometryT* InitNewCubeTexGeometry();
    GeometryT* InitNewCubeUnicolor();
} // namespace ThePit

#endif
