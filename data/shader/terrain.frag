
#version 450 core

uniform sampler2D terrain_diffuse;

in vec2 outUV;
in vec3 fragColor;

void main()
{
    vec3 tex = texture(terrain_diffuse,outUV).rgb;
    gl_FragColor = vec4(tex, 1.0);
	
}