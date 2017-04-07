

#version 330 core
  
layout (location = 0) in vec2 position;

void main()
{
    gl_Position = vec4(position.x * 0.3, position.y * 0.3, 0.f, 1.0);
}