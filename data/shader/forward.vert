

#version 430 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 fragST;
out vec3 fragNormal;
out vec3 fragLightPos;
out float fragVisibility;
out vec3 fragCamera;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec3 lightPos;

const float density = 0.0035f;
const float gradient = 5.0f;

void main()
{
    vec4 world = model * vec4(position,1.0);

    vec4 positionRelativeToCam = view * world;
    gl_Position = proj * positionRelativeToCam;
    fragNormal = (model * vec4(normal,0)).xyz;
    fragLightPos = lightPos - world.xyz;
    fragST = st;
    fragCamera = (inverse(view) * vec4(0,0,0,1)).xyz - world.xyz;

    float distance = length(positionRelativeToCam.xyz);

    fragVisibility = exp(-pow(distance * density, gradient));
    fragVisibility = clamp(fragVisibility, 0.0, 1.0);
}
