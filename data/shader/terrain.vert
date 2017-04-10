

#version 450 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 outUV;
out vec3 fragColor;
uniform int frame;

void main()
{
    float f = sin(frame * 0.005) * 3.3;
    vec3 newPos = position + vec3(0,0,f);
    outUV = st;
    fragColor = normal;
    gl_Position = proj * view * model * vec4(newPos, 1.0);
}