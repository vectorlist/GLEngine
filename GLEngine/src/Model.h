#pragma once

#include <config.h>


//test
class Mesh
{
public:
	Mesh(
		const std::vector<float> &vertex,
		const std::vector<uint32_t> *index = 0);
	~Mesh();

	const std::vector<float> &vertices;
	const std::vector<uint32_t> &indices;

	GLuint vao;

	std::vector<GLuint> vbos;
	void buildBuffer();

	bool has_ibo = true;

private:
	void releaseBuffer();
};

class Model
{
public:
	Model();
	~Model();

	std::vector<mesh_ptr> meshs;

	void addElement(mesh_ptr mesh);
	
};

inline void Model::addElement(mesh_ptr mesh)
{
	meshs.push_back(mesh);
}




