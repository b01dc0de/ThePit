#version 410

uniform sampler2D tex_smp;

layout(location = 0) out vec4 frag_color;
layout(location = 0) in vec2 uv;

void main()
{
	frag_color = texture(tex_smp, uv);
}

/*
// BEGIN FS
uniform texture2D tex;
uniform sampler smp;

in vec2 uv;
out vec4 frag_color;

void fs_main() {
    frag_color = texture(sampler2D(tex,smp), uv);
}
// END FS
*/

