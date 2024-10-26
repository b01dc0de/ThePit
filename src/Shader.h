#ifndef THEPIT_SHADER_H
#define THEPIT_SHADER_H

#include "Common.h"

namespace thepit
{
    void GetVxColorShaderDesc(sg_shader_desc& out_desc);
    void GetVxTextureShaderDesc(sg_shader_desc& out_desc);
    void GetVxUniformColorShaderDesc(sg_shader_desc& out_desc);
}

#endif // THEPIT_SHADER_H