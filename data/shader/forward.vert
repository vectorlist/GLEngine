

#version 450 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;
layout (location = 3) in vec3 tangent;

uniform int frame;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 inColor;
out vec2 outCoords;
out mat3 tangentSpance;

void main()
{
	outCoords = st;
	inColor = normal;
	float f = sin(frame * 0.02) * .3;
	mat4 mvp = proj * view * model;
    gl_Position = mvp * vec4(position + vec3(0,0,f), 1.0);
}