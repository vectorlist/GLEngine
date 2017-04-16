

#version 430 core
  
layout (location = 0) in vec4 text;     //0 1 pos   3 4 st

out vec2 outCoords;

uniform mat4 proj;
uniform int frame;

void main()
{
    gl_Position = proj * vec4(text.xy,0, 1.0);
    outCoords = text.zw;
}