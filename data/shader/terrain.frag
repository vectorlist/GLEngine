
#version 450 core

//struct Light {
 //   vec3 light01;
 //   vec3 light02;
//};
//uniform Light light;
struct UBOLight
{
	vec3 position;   
	vec3 color;		
	float intensity;	
};

// Uniform block named InstanceBlock, follows std140 alignment rules
layout (std140, binding = 0) uniform light_block {
  UBOLight uboInstance [3];
};

uniform sampler2D terrain_diffuse01;
uniform sampler2D terrain_diffuse02;

in vec2 outUV;
in vec2 relativeUV;
in vec3 fragPos;
in vec3 fragNormal;
in vec3 fragLightPos;

out vec4 outColor;

vec3 testShading(vec3 l, vec3 n)    //lightpos normal
{
    float distance = length(l - fragPos);
    vec3 lightDir = normalize(l - fragPos);
    float d = max(dot(normalize(n), lightDir),0.0);
    vec3 diffuse = d * vec3(1,1,1);
    return diffuse;
}

void main()
{
    vec4 tex = texture(terrain_diffuse01,outUV).rgba;
    vec4 tex2 = texture(terrain_diffuse02, relativeUV).rgba;
    float alpha = texture(terrain_diffuse02, relativeUV).a;
    vec3 result;
 
    result += testShading(fragLightPos, fragNormal);
    
    outColor = tex * tex2 * alpha;
    //outColor = vec4(result,1); 
    //outColor = tex2;
	
}