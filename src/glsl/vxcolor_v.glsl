#version 410

uniform vec4 vs_params[4];
layout(location = 0) in vec4 position;
layout(location = 0) out vec4 color;
layout(location = 1) in vec4 color0;

void main()
{
	gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * position;
	color = color0;
}

/*
// BEGIN VS
uniform vs_params {
    mat4 mvp;
};

in vec4 position;
in vec4 color0;

out vec4 color;

void vs_main() {
    gl_Position = mvp * position;
    color = color0;
}
// END VS
*/
