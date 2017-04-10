

#version 450 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 st;
layout (location = 3) in vec3 tangent;

//frame
uniform int frame;
out float outFrame;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform float texIndex;

out vec3 outPos;
out vec3 outNormal;
out vec2 outCoords;
out mat3 TBNview;
out float texindex;

void main()
{
    
    outNormal = normal;
    float f = sin(frame * 0.02) * .3;
    vec3 newPos = position + vec3(0,0,f);
    outPos = vec3(view * model * vec4(newPos, 1.0f));
    gl_Position = proj * vec4(outPos, 1.0);
    
    //TBN to world
    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
    T = normalize(T -dot(T,N) * N);
    vec3 B = cross(T, N);
    //to frag
    //i dont get it need to inverse or not
    TBNview = transpose(inverse(mat3(view * model))) * mat3(T, B, N);
    
    //Passive
    outCoords = st;
    outFrame = frame;
    texindex = texindex;
}