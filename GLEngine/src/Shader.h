#pragma once

#include <shadertool.h>

class Shader
{
public:
	Shader(const char* vert, const char* frag, const char* geo = 0);
	virtual~Shader();


	GLuint id;

	void bind();
	void unbind();
	virtual void buildUniformLocations() = 0;
protected:
	GLint setUniformLocation(const char* uniformname);
	void setAttribute(GLuint index, const char* attribname);
	void setLocation1f(GLint location, float data) const;
	void setLocation1i(GLint location, int data) const;
	void setLocation2f(GLint location, const vec2f &data) const;
	void setLocation3f(GLint location, const vec3f &data) const;
	void setLocation4f(GLint location, const vec4f &data) const;
	void setLocationMatrix4f(GLint location, const Matrix4x4 &data, bool transpose = false) const;

};



