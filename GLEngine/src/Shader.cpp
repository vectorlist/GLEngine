#include "shader.h"

Shader::Shader(const char* vert, const char* frag, const char* geo)
	: id(ShaderTool::load(vert, frag))
{
	
}

Shader::~Shader()
{
	if(id != NULL)
		glDeleteProgram(id);
}

void Shader::bind()
{
	glUseProgram(id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

GLint Shader::setUniformLocation(const char * uniformname)
{
	return glGetUniformLocation(id,uniformname);
}

void Shader::setAttribute(GLuint index, const char * attribname)
{
	glBindAttribLocation(id, index, attribname);
}

void Shader::setLocation1f(GLint location, float data) const
{
	glUniform1f(location, data);
}

void Shader::setLocation1i(GLint location, int data) const
{
	glUniform1i(location, data);
}

void Shader::setLocation2f(GLint location, const vec2f &data) const
{
	glUniform2fv(location, 1, &data.x);
}

void Shader::setLocation3f(GLint location, const vec3f &data) const
{
	glUniform3fv(location, 1, &data.x);
}

void Shader::setLocation4f(GLint location, const vec4f &data) const
{
	glUniform4fv(location, 1, &data.x);
}

void Shader::setLocationMatrix4f(GLint location, const Matrix4x4 &data, bool transpose) const
{
	glUniformMatrix4fv(location, 1, transpose, data.constData());
}

