#ifndef THEPIT_ENGINE_MATERIAL_H
#define THEPIT_ENGINE_MATERIAL_H

#include "Common.h"

// Struct to store material data
typedef struct {
    sg_shader shader;       // The shader program
} Material;

Material material();
void material_bind(const Material* material);

#endif
