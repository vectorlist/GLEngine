
#version 430 core

in vec3 fragST;

uniform samplerCube cubeMap;
uniform vec3 fogColor;

out vec4 outColor;
//TODO : replace uniform var
const float lower = 100.0f;
const float upper = 20.f;
void main()
{
    vec4 texColor = texture(cubeMap, fragST);
    //outColor = vec4(1,1,0, 1.0);
    //vec3 fogColor = vec3(0.7,0.75,0.8);
    float factor = (fragST.y - lower) / (upper - lower);
    //clamp to 0 to 1
    factor = clamp(factor,0.0,1.0); 

    outColor = mix(vec4(fogColor, 1.0), texColor, factor);
	
}