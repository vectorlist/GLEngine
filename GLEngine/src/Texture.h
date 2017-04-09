#pragma once

#include <config.h>

enum Texture_Type
{
	DIFFUSE = 0,
	SPECULAR,
	NORMAL
};

#define TEXTURE_NONE UINT_MAX

struct Texture
{
	GLuint id = TEXTURE_NONE;
	Texture_Type type;
	std::string path;

};