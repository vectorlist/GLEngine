

#version 430 core
  
//layout (location = 0) in vec3 position;
in vec3 position;

uniform mat4 proj;
uniform mat4 view;

out vec3 fragST;

void main()
{
    gl_Position = proj * view  * vec4(position, 1.0);
    fragST = position;
}