
#version 330 core

uniform sampler2D diffuse_map;
//uniform sampler2D normal_map;


//from vert
in vec3 outPos;
in vec2 outCoords;

out vec4 outColor;


void main()
{
    vec3 texColor = texture(diffuse_map, outCoords).rgb;
    outColor = vec4(vec3(texColor),1);
}