//------------------------------------------------------------------------------
//  Shader code for texcube-sapp sample.
//
//  NOTE: This source file also uses the '#pragma sokol' form of the
//  custom tags.
//------------------------------------------------------------------------------
#pragma sokol @ctype mat4 hmm_mat4

#pragma sokol @vs vs
uniform vs_params {
    mat4 mvp;
};

in vec4 pos;
in vec2 texcoord0;

out vec2 uv;

void main() {
    gl_Position = mvp * pos;
    uv = texcoord0 * 5.0;
}
#pragma sokol @end

#pragma sokol @fs fs
uniform texture2D tex;
uniform sampler smp;

in vec2 uv;
out vec4 frag_color;

void main() {
    frag_color = texture(sampler2D(tex,smp), uv);
}
#pragma sokol @end

#pragma sokol @program texcube vs fs
