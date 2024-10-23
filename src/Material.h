#ifndef THEPIT_MATERIAL_H
#define THEPIT_MATERIAL_H

#include "Common.h"

namespace thepit
{
    // Struct to store material data
    struct Material
    {
        sg_shader shader;       // The shader program
    };

    Material InitCubeMaterial();
}

#endif
