#pragma once

#include <config.h>
#include <Texture.h>
#include <SDL2/SDL_image.h>
struct Vertex
{
	vec3f pos;
	vec3f normal;
	vec2i st;
	vec3f tangent;
};

#define VBO_VERTEX		0
#define VBO_NORAML		1
#define VBO_ST			2
#define VBO_TANGENT		3
#define VBO_NUM			4

struct Maps
{
	Texture* diffuse;
	Texture* normal;
	Texture* specualr;
};

#define MAP_MAX_NUM		3

class Mesh
{
public:
	Mesh();
	~Mesh();

	std::vector<float> vertices, normals, st, tangent;
	//const std::vector<Vertex> &vertices;
	std::vector<uint32_t> indices;

	GLuint vao;

	Maps map;
	GLuint vbos[VBO_NUM];
	GLuint ibo;
	//GLuint vbo;
	void buildBuffer();

	bool has_ibo = true;

	static Texture* load(const std::string &filename, bool clamp = true);
private:
	void releaseBuffer();

public:
	static std::vector<Texture*> global_textures;
};

