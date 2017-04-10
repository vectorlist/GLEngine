#include "Shader.h"
#include <fstream>
#include <sstream>

std::string Shader::codeFromFile(const std::string &filename)
{
	std::string bits;
	std::ifstream filestream(filename, std::ios::in);
	if (!filestream.is_open())
	{
		std::string err = "failed to load file : ";
		err.append(filename);
		LOG_ERROR(err);
	}
	
	std::string line = "";
	while (!filestream.eof())
	{
		std::getline(filestream, line);
		bits.append(line + "\n");
	}
	filestream.close();
	return bits;
}

GLuint Shader::compile(const GLchar *code, const GLenum type, const char* path)
{
	GLint success;
	GLchar info_log[512];

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		LOG_SHADER_ERROR(path,info_log);
	}

	return shader;
}

GLuint Shader::load(const char * vertpath, const char * fragpath)
{
	std::string vertCode = codeFromFile(vertpath);
	std::string fragCode = codeFromFile(fragpath);

	GLuint vert = compile(vertCode.c_str(), GL_VERTEX_SHADER, vertpath);
	GLuint frag = compile(fragCode.c_str(), GL_FRAGMENT_SHADER, fragpath);

	GLuint program = glCreateProgram();

	glAttachShader(program, vert);
	glAttachShader(program, frag);

	glLinkProgram(program);

	GLint success;
	GLchar info_log[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, info_log);
		LOG_ERROR(info_log);
	}

	//we dont need shader anymore
	glDeleteShader(vert);
	glDeleteShader(frag);

	glUseProgram(program);
	
	return program;
}

void Shader::setUniform1i(GLuint &program, uint32_t data, const char* name)
{
	glUniform1i(glGetUniformLocation(program, name), data);
}

void Shader::setUniform1f(GLuint &program, float data, const char* name)
{
	glUniform1f(glGetUniformLocation(program, name), data);
}

void Shader::setUniForm2i(GLuint &program, const vec2i &data, const char* name)
{
	glUniform2i(glGetUniformLocation(program, name), data.x,data.y);
}

void Shader::setUniForm2f(GLuint &program, const vec2f &data, const char* name)
{
	glUniform2f(glGetUniformLocation(program, name), data.x, data.y);
}

void Shader::setUniForm3f(GLuint &program, const vec3f &data, const char* name)
{
	glUniform3f(glGetUniformLocation(program, name), data.x, data.y, data.z);
}

void Shader::setUniformMatrix4f(GLuint &program, const Matrix4x4 &mat, const char* name, bool transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, transpose, mat.constData());
}