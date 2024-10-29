#ifndef THEPIT_SHADER_H
#define THEPIT_SHADER_H

#include "Common.h"

namespace ThePit
{
    void GetVxColorShaderDesc(sg_shader_desc& out_desc);
    void GetVxTextureShaderDesc(sg_shader_desc& out_desc);
    void GetVxColorTextureShaderDesc(sg_shader_desc& out_desc);
    void GetVxUniformColorShaderDesc(sg_shader_desc& out_desc);
} // namespace ThePit

#endif // THEPIT_SHADER_H