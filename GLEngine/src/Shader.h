#pragma once

#include <config.h>
#include <string>

namespace Shader
{
	GLuint load(const char* vertfile, const char* fragfile);
	std::string codeFromFile(const std::string &filename);
	GLuint compile(const GLchar* source, const GLenum type, const char *code);

	void setUniform1i(GLuint &program, uint32_t data, const char* name);
	void setUniform1f(GLuint &program, float data, const char* name);
	void setUniForm2i(GLuint &program, const vec2i &data, const char* name);
	void setUniForm2f(GLuint &program, const vec2f &data, const char* name);
	void setUniForm3f(GLuint &program, const vec3f &data, const char* name);
	void setUniformMatrix4f(
		GLuint &program,
		const Matrix4x4 &mat,
		const char* name,
		bool transpose = false);

	void load_vec3f(GLint location, const vec3f &data);

}