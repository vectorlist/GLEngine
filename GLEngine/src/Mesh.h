#pragma once

#include <GL/glew.h>
#include <vec2f.h>
#include <vec3f.h>
#include <vector>
#include <memory>
struct Vertex
{
	vec3f pos;
	vec3f normal;
	vec2f st;
	vec3f tangent;
	vec3f bitangent;
};

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vertice, std::vector<uint32_t> indices);
	~Mesh();


	GLuint vao = NULL;
	uint32_t indices_size;
	void render();
private:
	void build_buffers();
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint vbo = NULL;
	GLuint ibo = NULL;

};

typedef std::shared_ptr<Mesh> mesh_ptr;
