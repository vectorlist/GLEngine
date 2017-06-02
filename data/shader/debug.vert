#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 shadowSpace;
uniform mat4 shadowRelativeView;
uniform float isShadowView;
uniform float shadow_distance;

const float transDistance = 10.0f;
out frag_t{
    vec3 N;
    vec2 ST;
}frag;

out vec4 shadowCoords;

void main()
{
    vec4 world = model * vec4(position, 1.0);
    vec4 relativeToCam = view * world;
    //world view
    if(isShadowView == 0.0)
    {
        gl_Position =  proj * relativeToCam;
    }
    else{
        gl_Position =  shadowRelativeView * world;
    }
    //shadow view matrix
    //gl_Position =  shadowSpace * world;
    shadowCoords = shadowSpace * world;
    frag.N =  (model * vec4(normal, 0)).xyz;

    float distance = length(relativeToCam.xyz);
    distance = distance - (shadow_distance - transDistance);
    distance = distance / transDistance;
    shadowCoords.w = clamp(1.0 - distance, 0.0,1.0);

}