#ifndef THEPIT_GRAPHICS_H
#define THEPIT_GRAPHICS_H

#include "Common.h"

namespace ThePit
{
namespace Graphics
{
void GetVxColorShaderDesc(sg_shader_desc& out_desc);
void GetVxTextureShaderDesc(sg_shader_desc& out_desc);
void GetVxColorTextureShaderDesc(sg_shader_desc& out_desc);
void GetVxUniformColorShaderDesc(sg_shader_desc& out_desc);
} // namespace Graphics
} // namespace ThePit

#endif // THEPIT_GRAPHICS_H