#pragma once
/*
    #version:1# (machine generated, don't edit!)

    Generated by sokol-shdc (https://github.com/floooh/sokol-tools)

    Cmdline:
        sokol-shdc -i .\texcube-sapp.glsl -o .\texcube-sapp.glsl.h -l glsl410

    Overview:
    =========
    Shader program: 'texcube':
        Get shader desc: texcube_shader_desc(sg_query_backend());
        Vertex shader: vs
            Attributes:
                ATTR_vs_pos => 0
                ATTR_vs_texcoord0 => 1
            Uniform block 'vs_params':
                C struct: vs_params_t
                Bind slot: SLOT_vs_params => 0
        Fragment shader: fs
            Image 'tex':
                Image type: SG_IMAGETYPE_2D
                Sample type: SG_IMAGESAMPLETYPE_FLOAT
                Multisampled: false
                Bind slot: SLOT_tex => 0
            Sampler 'smp':
                Type: SG_SAMPLERTYPE_FILTERING
                Bind slot: SLOT_smp => 0
            Image Sampler Pair 'tex_smp':
                Image: tex
                Sampler: smp
*/
#if !defined(SOKOL_GFX_INCLUDED)
#error "Please include sokol_gfx.h before texcube-sapp.glsl.h"
#endif
#if !defined(SOKOL_SHDC_ALIGN)
#if defined(_MSC_VER)
#define SOKOL_SHDC_ALIGN(a) __declspec(align(a))
#else
#define SOKOL_SHDC_ALIGN(a) __attribute__((aligned(a)))
#endif
#endif
#define ATTR_vs_pos (0)
#define ATTR_vs_texcoord0 (1)
#define SLOT_vs_params (0)
#define SLOT_tex (0)
#define SLOT_smp (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct vs_params_t {
    HMM_Mat4 mvp;
} vs_params_t;
#pragma pack(pop)
/*
    #version 410

    uniform vec4 vs_params[4];
    layout(location = 0) in vec4 pos;
    layout(location = 0) out vec2 uv;
    layout(location = 1) in vec2 texcoord0;

    void main()
    {
        gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * pos;
        uv = texcoord0 * 5.0;
    }

*/
static const uint8_t vs_source_glsl410[280] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x34,0x31,0x30,0x0a,0x0a,0x75,0x6e,
    0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x34,0x5d,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,
    0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x69,0x6e,
    0x20,0x76,0x65,0x63,0x34,0x20,0x70,0x6f,0x73,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,
    0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,
    0x6f,0x75,0x74,0x20,0x76,0x65,0x63,0x32,0x20,0x75,0x76,0x3b,0x0a,0x6c,0x61,0x79,
    0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x31,
    0x29,0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x32,0x20,0x74,0x65,0x78,0x63,0x6f,0x6f,
    0x72,0x64,0x30,0x3b,0x0a,0x0a,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,
    0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,
    0x69,0x6f,0x6e,0x20,0x3d,0x20,0x6d,0x61,0x74,0x34,0x28,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x30,0x5d,0x2c,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,
    0x6d,0x73,0x5b,0x31,0x5d,0x2c,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,
    0x5b,0x32,0x5d,0x2c,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x33,
    0x5d,0x29,0x20,0x2a,0x20,0x70,0x6f,0x73,0x3b,0x0a,0x20,0x20,0x20,0x20,0x75,0x76,
    0x20,0x3d,0x20,0x74,0x65,0x78,0x63,0x6f,0x6f,0x72,0x64,0x30,0x20,0x2a,0x20,0x35,
    0x2e,0x30,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
/*
    #version 410

    uniform sampler2D tex_smp;

    layout(location = 0) out vec4 frag_color;
    layout(location = 0) in vec2 uv;

    void main()
    {
        frag_color = texture(tex_smp, uv);
    }

*/
static const uint8_t fs_source_glsl410[175] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x34,0x31,0x30,0x0a,0x0a,0x75,0x6e,
    0x69,0x66,0x6f,0x72,0x6d,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,
    0x74,0x65,0x78,0x5f,0x73,0x6d,0x70,0x3b,0x0a,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,
    0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x6f,
    0x75,0x74,0x20,0x76,0x65,0x63,0x34,0x20,0x66,0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,
    0x6f,0x72,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,
    0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x69,0x6e,0x20,0x76,0x65,0x63,0x32,
    0x20,0x75,0x76,0x3b,0x0a,0x0a,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,
    0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x72,0x61,0x67,0x5f,0x63,0x6f,0x6c,
    0x6f,0x72,0x20,0x3d,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x28,0x74,0x65,0x78,
    0x5f,0x73,0x6d,0x70,0x2c,0x20,0x75,0x76,0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
static inline const sg_shader_desc* texcube_shader_desc(sg_backend backend) {
    if (backend == SG_BACKEND_GLCORE) {
        static sg_shader_desc desc;
        static bool valid;
        if (!valid) {
            valid = true;
            desc.attrs[0].name = "pos";
            desc.attrs[1].name = "texcoord0";
            desc.vs.source = (const char*)vs_source_glsl410;
            desc.vs.entry = "main";
            desc.vs.uniform_blocks[0].size = 64;
            desc.vs.uniform_blocks[0].layout = SG_UNIFORMLAYOUT_STD140;
            desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
            desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
            desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
            desc.fs.source = (const char*)fs_source_glsl410;
            desc.fs.entry = "main";
            desc.fs.images[0].used = true;
            desc.fs.images[0].multisampled = false;
            desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
            desc.fs.images[0].sample_type = SG_IMAGESAMPLETYPE_FLOAT;
            desc.fs.samplers[0].used = true;
            desc.fs.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
            desc.fs.image_sampler_pairs[0].used = true;
            desc.fs.image_sampler_pairs[0].image_slot = 0;
            desc.fs.image_sampler_pairs[0].sampler_slot = 0;
            desc.fs.image_sampler_pairs[0].glsl_name = "tex_smp";
            desc.label = "texcube_shader";
        }
        return &desc;
    }
    return 0;
}