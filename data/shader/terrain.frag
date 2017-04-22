
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

uniform sampler2D textureBackground;
uniform sampler2D textureR;
uniform sampler2D textureG;
uniform sampler2D textureB;
uniform sampler2D textureBlend;

uniform vec3 lightColor;
//uniform vec3 lightPos;
uniform vec3 skyColor;

in vec2 fragST;
in vec3 fragPos;
in vec3 fragNormal;
in vec3 fragToLight;
in vec3 fragCamera;
in float fragVisibility;

out vec4 outColor;

void main()
{
    vec4 texBlend = texture(textureBlend, fragST);
    float backgroundAmount = 1 - (texBlend.r + texBlend.g + texBlend.b);
    vec2 tiledST = fragST * 40;
    vec4 texBackground = texture(textureBackground, tiledST) * backgroundAmount;
    vec4 texR = texture(textureR, tiledST) * texBlend.r;
    vec4 texG = texture(textureG, tiledST) * texBlend.g;
    vec4 texB = texture(textureB, tiledST) * texBlend.b;

    vec4 totalColor = texBackground + texR + texG + texB;

    //light
    vec3 unitNormal = normalize(fragNormal);
    vec3 unitVectorToCamera = normalize(fragCamera);
    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);
    
    vec3 attenuation = vec3(5,0,0);
    float distance = length(fragToLight);
    float attFactor = attenuation.x + attenuation.y * distance + attenuation.z * distance * distance;
    vec3 unitLightVector = normalize(fragToLight);

    float NdotL = dot(unitNormal , unitLightVector);
    float brightness = max(NdotL, 0.0f);
    vec3 diffuse = brightness * lightColor / attFactor;
    totalDiffuse += diffuse;
    
    
    vec3 lightDir = -unitLightVector;
    vec3 reflectLightDir = reflect(lightDir, unitNormal);

    float specularFactor = dot(reflectLightDir, unitVectorToCamera);
    specularFactor = max(specularFactor, 0.0);

    float shinesss = 1;
    float reflectivity = 1.f;
    float dampedFactor = pow(specularFactor, shinesss);
    vec3 specular = (dampedFactor * reflectivity * lightColor) / attFactor;
    totalSpecular += specular;

    totalDiffuse = max(totalDiffuse, 0.4);

    //1 layer output
    outColor = totalColor * vec4(totalDiffuse,1) + vec4(totalSpecular,1);


    //test 
    vec3 skyColor = vec3(0.7,0.8,0.9);
    //2 layer output
    //mix(mycolor, original, value);
    outColor = mix(vec4(skyColor,1), outColor, fragVisibility);
    

	
}