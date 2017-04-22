#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
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

struct CubeTexture
{
	GLuint id;
	uint32_t id_index;
};

typedef std::shared_ptr<Texture> texture_ptr;
