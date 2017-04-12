
#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitTangent;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


out vec3 outPos;

out vec2 outCoords;


void main()
{
    
    //outPos = vec3(view * model * vec4(position, 1.0f));
    gl_Position = proj * view * model * vec4(position, 1.0);
    
    //Passive
    outCoords = st;

}