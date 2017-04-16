
#version 430 core

out vec4 fragColor;
in vec2 outCoords;

uniform sampler2D diffuse_map;

void main()
{
    vec3 texColor = texture(diffuse_map, outCoords).rgb;
    fragColor = vec4(texColor,1);
}