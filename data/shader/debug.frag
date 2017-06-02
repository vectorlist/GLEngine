
#version 430 core

in frag_t{
    vec3 N;
    vec2 ST;
}frag;

uniform sampler2D shadowMap;
uniform vec3 sun;
out vec4 outColor;
in vec4 shadowCoords;
void main()
{
    //shadow test
    float bias = 0.002;
    float lightFactor = 1.0;

   // float nearObejct = texture(shadowMap, shadowCoords.xy).r;
    //if(nearObejct < shadowCoords.z - bias){
    //    lightFactor = 0.5f;
   // }
    float object = texture(shadowMap, shadowCoords.xy).r;
    if(shadowCoords.z > object){
        lightFactor = 1.0 - (shadowCoords.w *0.4);
    }
    vec3 L = normalize(sun);
    vec3 N = normalize(frag.N);
    float NdotL = max(dot(N, L),0.0);
    vec3 color = vec3(0.6,0.58,0.55) * NdotL;
    vec4 texColor = texture(shadowMap, frag.ST);
    vec3 ambient = vec3(0.2,0.22,0.24);
    //outColor = ambient + vec4(color,1) * lightFactor;
    vec3 total = (ambient + color) * lightFactor;
    outColor = vec4(total, 1);
}
