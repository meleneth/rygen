#version 130

in vec2 f_texcoord;
uniform sampler2D mytexture;

out vec4 color;

void main(void) {
    color = texture(mytexture, f_texcoord);
}