#include "Shader.h"
#include "Engine.h"

namespace thepit
{
    char* ReadGLSLFile(const char* glsl_filename)
    {
        static const int max_len_filename = 256;
        char filename_buff[max_len_filename];
        sprintf(filename_buff, "%s/%s", GetProjectDir(), glsl_filename);

        // TODO: Handle this correctly without absolute path
        char* Result = nullptr;

        FILE* glsl_file = nullptr;
        glsl_file = fopen(filename_buff, "rb");
        THEPIT_ASSERT(nullptr != glsl_file);
        if (glsl_file)
        {
            fseek(glsl_file, 0, SEEK_END);
            long file_size = ftell(glsl_file);
            fseek(glsl_file, 0, SEEK_SET);

            Result = new char[file_size + 1];
            size_t read_bytes = fread(Result, sizeof(char), file_size, glsl_file);
            THEPIT_ASSERT(read_bytes == file_size);
            Result[file_size] = '\0';

            fclose(glsl_file);
        }

        return Result;
    }


    void GetVxColorShaderDesc(sg_shader_desc& out_desc)
    {
        // TODO: Handle this correctly without absolute path
        char* v_file_src = ReadGLSLFile("src/glsl/vxcolor_v.glsl");
        char* f_file_src = ReadGLSLFile("src/glsl/vxcolor_f.glsl");

        out_desc.attrs[0].name = "position";
        out_desc.attrs[1].name = "color0";
        out_desc.vs.source = (const char*)v_file_src;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(HMM_Mat4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file_src;
        out_desc.fs.entry = "main";
        out_desc.label = "vxcolor";
    }

    void GetVxTextureShaderDesc(sg_shader_desc& out_desc)
    {
        char* v_file_src = ReadGLSLFile("src/glsl/vxtexture_v.glsl");
        char* f_file_src = ReadGLSLFile("src/glsl/vxtexture_f.glsl");

        out_desc.attrs[0].name = "pos";
        out_desc.attrs[1].name = "texcoord0";
        out_desc.vs.source = (const char*)v_file_src;
        out_desc.vs.entry = "main";
        out_desc.vs.uniform_blocks[0].size = sizeof(HMM_Mat4);
        out_desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
        out_desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
        out_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
        out_desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
        out_desc.fs.source = (const char*)f_file_src;
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
        char* glsl_file = ReadGLSLFile("W:\\ThePit\\src\\glsl\\base_vxcolor.glsl");
        (void)out_desc;
    }
}
