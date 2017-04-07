#include "Model.h"





Mesh::Mesh(const std::vector<float>& vertex,
	const std::vector<uint32_t> *index)
	: vertices(vertex), indices(*index)
{
	//if (indices.size() == 0) has_ibo = false;
	buildBuffer();
}

Mesh::~Mesh()
{
	releaseBuffer();
}

void Mesh::buildBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo for 2d atm
	GLuint vertex_vbo;
	glGenBuffers(1, &vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() * 2) * sizeof(float),
		vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	////add vbo
	//vbos.push_back(vertex_vbo);

	//finish vao bounding
	glBindVertexArray(0);

	//add vbo
	vbos.push_back(vertex_vbo);
}

void Mesh::releaseBuffer()
{
	glDeleteVertexArrays(1, &vao);
	if (vbos.size() == 0) return;
	glDeleteBuffers(vbos.size(), vbos.data());
}


Model::Model()
{
}


Model::~Model()
{
}