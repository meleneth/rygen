#version 130

in vec2 vertexPosition_modelspace;

in vec2 texcoord;
out vec2 f_texcoord;

uniform mat4 MVP;


void main(){
    f_texcoord = texcoord;

    vec4 v = vec4(vertexPosition_modelspace, 0.0, 1.0);
    gl_Position = MVP * v;
}
