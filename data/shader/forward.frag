
#version 430 core

uniform sampler2D textureDiffuse;

out vec4 outColor;
uniform vec3 lightColor;
uniform vec3 skyColor;

in float fragVisibility;
in vec3 fragNormal;
in vec3 fragLightPos;
in vec3 fragCamera;
in vec2 fragST;


void main()
{
    vec4 textureColor = texture(textureDiffuse, fragST);
    
    vec3 unitNormal = normalize(fragNormal);
    vec3 unitVectorToCamera = normalize(fragCamera);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    //DIFFUSE
    vec3 attenuation = vec3(0,5,0);
    float distance = length(fragLightPos);
    float attfactor = attenuation.x + attenuation.y * distance + attenuation.z *
    distance * distance;

    vec3 unitLightVector = normalize(fragLightPos);
    float NdotL = dot(unitNormal , unitLightVector);
    float brightness = max(NdotL, 0.0f);
    vec3 lightDir = -unitLightVector;
    vec3 reflectedLightDir = reflect(lightDir, unitNormal);
    
    //SPECULAR
    float specularFactor = dot(reflectedLightDir, unitVectorToCamera);
    specularFactor = max(specularFactor, 0.0);

    float shininess = 4;
    float reflectivity = 30.0f;
    float dampedFactor = pow(specularFactor, shininess);

    vec3 diffuse = brightness * lightColor/attfactor;
    totalDiffuse += diffuse;
    vec3 specular = dampedFactor * reflectivity * lightColor / attfactor;
    totalSpecular += specular;

    totalDiffuse = max(totalDiffuse, 0.4);
    
    outColor = vec4(totalDiffuse,1) * textureColor + vec4(totalSpecular,1);

    outColor = mix(vec4(skyColor, 1.0), outColor, fragVisibility);
}