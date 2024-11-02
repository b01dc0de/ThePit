#version 410

layout(location = 0) out vec4 frag_color;
layout(location = 0) in vec4 color;

void main()
{
    frag_color = color;
}

/*
// BEGIN FS
in vec4 color;
out vec4 frag_color;

void fs_main() {
    frag_color = color;
}
// END FS
*/
