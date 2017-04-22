#include <Mesh.h>

//it must be Shader_Type Index

Mesh::Mesh()
{
	//dothing
}

Mesh::Mesh(std::vector<Vertex> vertice, std::vector<uint32_t> indices)
{
	this->vertices = vertice;
	this->indices = indices;
	build_buffers();
}

Mesh::~Mesh()
{

	if(vao)
		glDeleteVertexArrays(1, &vao);
	if(vbo)
		glDeleteBuffers(1, &vbo);
	if(ibo)
		glDeleteBuffers(1, &ibo);
}

void Mesh::build_buffers()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ibo);

	glBindVertexArray(this->vao);

	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::st));
	// Vertex Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::tangent));
	// Vertex Bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::bitangent));

	glBindVertexArray(0);

	indices_size = indices.size();
	vertices.clear();
	indices.clear();
}

void Mesh::render()
{
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indices_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
