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

/*
// BEGIN VS
uniform vs_params {
    mat4 mvp;
};

in vec4 pos;
in vec2 texcoord0;

out vec2 uv;

void vs_main() {
    gl_Position = mvp * pos;
    uv = texcoord0 * 5.0;
}
// END VS
*/
