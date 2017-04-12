
#version 330 core

//uniform sampler2D diffuse_map;
//uniform sampler2D normal_map;


//from vert
in vec3 outPos;
in vec2 outCoords;

out vec4 fragColor;


void main()
{
    fragColor = vec4(vec3(outCoords,0),1);
}