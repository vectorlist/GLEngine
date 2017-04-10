#pragma once

#include <config.h>

#define TEXTURE_NONE UINT_MAX

enum Texture_Type
{
	TEXTURE_DIFFUSE = 0,
	TEXTURE_SPECULAR,
	TEXTURE_NORMAL
};

struct Texture
{
	GLuint id;
	Texture_Type type;
	std::string path;

};