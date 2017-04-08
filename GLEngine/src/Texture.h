#pragma once

#include <config.h>

enum Texture_Type
{
	DIFFUSE = 0,
	SPECULAR,
	NORMAL
};

struct Texture
{
	GLuint id;
	Texture_Type type;
	std::string path;

};