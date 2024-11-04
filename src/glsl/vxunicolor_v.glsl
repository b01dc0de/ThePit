#version 410

uniform vec4 vs_params[5];
layout(location = 0) in vec4 pos;
layout(location = 0) out vec4 color;

void main()
{
	gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * pos;
	color = vs_params[4];
}
