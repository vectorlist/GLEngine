#include "Shader.h"
#include <fstream>
#include <sstream>

std::string Shader::codeFromFile(const char * file)
{
	std::string source;
	std::ifstream filestream;

	filestream.exceptions(std::ifstream::badbit);

	
	filestream.open(file);

	std::stringstream stream;
	stream << filestream.rdbuf();
	filestream.close();
	source = stream.str();
	
	return source;
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
		error(info_log);
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
		error(info_log);
	}

	//we dont need shader anymore
	glDeleteShader(vert);
	glDeleteShader(frag);

	glUseProgram(program);
	
	
	return program;
}


void Shader::error(const std::string &errorMsg)
{
	LOG << "error : " << errorMsg << ENDL;
}

