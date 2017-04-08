
#version 450 core

in vec3 inColor;

uniform sampler2D diffuse_map;

in vec2 outCoords;

out vec4 fragColor;

void main()
{
	vec3 outColor = inColor;
    //gl_FragColor = vec4(outColor, 1.0);
	vec4 texColor = texture(diffuse_map, outCoords).rgba;
	fragColor = vec4(texColor);
}