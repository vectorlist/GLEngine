

#version 450 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightPos;

out vec2 outUV;
out vec2 relativeUV;
out vec3 fragPos;
out vec3 fragNormal;
out vec3 fragLightPos;
uniform int frame;

void main()
{
    
    //numRows = 2.0;
    //offset = vec2(800,800);
    vec4 worldPosition = model * vec4(position, 1.0);
    vec4 positionRelativeToCamera = view * worldPosition;
    gl_Position = proj * positionRelativeToCamera;

    //pass out
    //fragPos = worldPosition.xyz;
    fragPos = worldPosition.xyz;
    fragNormal = normal;
    outUV = st * 30;
    relativeUV = st;
    fragLightPos = lightPos;
}