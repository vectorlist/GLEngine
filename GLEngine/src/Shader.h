#pragma once

#include <config.h>
#include <string>

namespace Shader
{

	std::string codeFromFile(const char* file);
	GLuint compile(const GLchar* source, const GLenum type, const char *code);
	GLuint load(const char* vertfile, const char* fragfile);


	//error
	void error(const std::string &errorMsg);
	
}