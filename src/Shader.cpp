#include "Shader.h"
#include "Engine.h"
#include "FileUtils.h"

namespace ThePit
{
    void GetVxColorShaderDesc(sg_shader_desc& out_desc)
    {
        FileContentsT v_file{"src/glsl/vxcolor_v.glsl", nullptr};
        FileContentsT f_file{ "src/glsl/vxcolor_f.glsl", nullptr };
        ReadFileContents(&v_file);
        ReadFileContents(&f_file);

        out_desc.attrs[0].name = "position";
        out_desc.attrs[1].name = "color0";
        out_desc.vs.source = (const char*)v_file.contents;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(HMM_Mat4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file.contents;
        out_desc.fs.entry = "main";
        out_desc.label = "vxcolor";
    }

    void GetVxTextureShaderDesc(sg_shader_desc& out_desc)
    {
        FileContentsT v_file{ "src/glsl/vxtexture_v.glsl", nullptr };
        FileContentsT f_file{ "src/glsl/vxtexture_f.glsl", nullptr };
        ReadFileContents(&v_file);
        ReadFileContents(&f_file);

        out_desc.attrs[0].name = "pos";
        out_desc.attrs[1].name = "texcoord0";
        out_desc.vs.source = (const char*)v_file.contents;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(HMM_Mat4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file.contents;
        out_desc.fs.entry = "main";
        out_desc.fs.images[0].used = true;
        out_desc.fs.images[0].multisampled = false;
        out_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
        out_desc.fs.images[0].sample_type = SG_IMAGESAMPLETYPE_FLOAT;
        out_desc.fs.samplers[0].used = true;
        out_desc.fs.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
        out_desc.fs.image_sampler_pairs[0].used = true;
        out_desc.fs.image_sampler_pairs[0].image_slot = 0;
        out_desc.fs.image_sampler_pairs[0].sampler_slot = 0;
        out_desc.fs.image_sampler_pairs[0].glsl_name = "tex_smp";
        out_desc.label = "texcube_shader";
    }

    void GetVxUniformColorShaderDesc(sg_shader_desc& out_desc)
    {
        // TODO: Implement
    }
} // namespace ThePit
