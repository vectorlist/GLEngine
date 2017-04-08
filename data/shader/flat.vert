

#version 450 core
  
layout (location = 0) in vec3 position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position + vec3(0,0,0), 1.0);
}