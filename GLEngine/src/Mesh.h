#pragma once

#include <config.h>
#include <SDL2/SDL_image.h>
#include <Texture.h>
struct Vertex
{
	vec3f pos;
	vec3f normal;
	vec2f st;
	vec3f tangent;
	vec3f bitangent;
};

struct Maps
{
	Texture* diffuse = NULL;
	Texture* normal = NULL;
	Texture* specular = NULL;
};

#define MAP_MAX_NUM		3

class Mesh
{
public:
	Mesh(){}
	Mesh(std::vector<Vertex> vertice, std::vector<uint32_t> indices);
	Mesh(std::vector<Vertex> vertice, 
		std::vector<uint32_t> indices,
		const std::string &texture);
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint vao;

	Maps maps;

	void build_buffers();


	void setTexture(
		const std::string &filename,
		bool clamp,
		Texture_Type type);

	static Texture* loadTexture(
		const std::string &filename,
		bool clamp = true,
		Texture_Type type = TEXTURE_DIFFUSE);

	static std::vector<Texture*> global_textures;
	void render();
private:
	GLuint vbo;
	GLuint ibo;
public:
	//STATICS

};

