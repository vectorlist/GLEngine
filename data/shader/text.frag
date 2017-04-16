
#version 430 core

out vec4 outColor;

uniform sampler2D text;                 //GL_TEXTURE0
uniform vec3 text_color;
//test


in vec2 outCoords;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, outCoords).r);
    outColor = vec4(text_color, 1.0) * sampled;
}  