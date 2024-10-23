#ifndef THEPIT_MATH_H
#define THEPIT_MATH_H

#include "Common.h"

#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct vs_params_t {
    HMM_Mat4 mvp;
} vs_params_t;
#pragma pack(pop)

#endif // THEPIT_MATH_H