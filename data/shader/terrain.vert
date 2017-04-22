

#version 450 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightPos;

out vec2 fragST;
out vec3 fragPos;
out vec3 fragNormal;
out vec3 fragToLight;
out vec3 fragCamera;
out float fragVisibility;

const float density = 0.0035f;
const float gradient = 5.0f;

void main()
{
    vec4 world = model * vec4(position, 1.0);
    vec4 positionRelativeToCamera = view * world;
    gl_Position = proj * positionRelativeToCamera;

    fragPos = world.xyz;
    fragNormal = normal;
    fragST = st;
    //vecxtor to light
    fragToLight = lightPos - world.xyz;
    //fragToLight = vec3(3,3,3) - world.xyz;
    //invert camera direction
    fragCamera = (inverse(view) * vec4(0,0,0,1)).xyz - world.xyz;
    float distance = length(positionRelativeToCamera.xyz);

    fragVisibility = exp(-pow((distance * density),gradient));
    //clamp to visibility 0 to 1
    fragVisibility = clamp(fragVisibility,0.0,1.0);
}