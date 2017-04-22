#include "EnvironmentRenderer.h"
#include <loadmanager.h>
namespace 
{
	constexpr float size = 500.f;
	const std::vector<float> skyboxVertices = 
	{
		// Positions          
		-size,  size, -size,
		-size, -size, -size,
		size, -size, -size,
		size, -size, -size,
		size,  size, -size,
		-size,  size, -size,

		-size, -size,  size,
		-size, -size, -size,
		-size,  size, -size,
		-size,  size, -size,
		-size,  size,  size,
		-size, -size,  size,

		size, -size, -size,
		size, -size,  size,
		size,  size,  size,
		size,  size,  size,
		size,  size, -size,
		size, -size, -size,

		-size, -size,  size,
		-size,  size,  size,
		size,  size,  size,
		size,  size,  size,
		size, -size,  size,
		-size, -size,  size,

		-size,  size, -size,
		size,  size, -size,
		size,  size,  size,
		size,  size,  size,
		-size,  size,  size,
		-size,  size, -size,

		-size, -size, -size,
		-size, -size,  size,
		size, -size, -size,
		size, -size, -size,
		-size, -size,  size,
		size, -size,  size
	};

	const std::vector<vec3f> cube_vertices
	{
		vec3f(-1.0,  1.0,  1.0),
		vec3f(-1.0, -1.0,  1.0),
		vec3f(1.0, -1.0,  1.0),
		vec3f(1.0,  1.0,  1.0),
		vec3f(-1.0,  1.0, -1.0),
		vec3f(-1.0, -1.0, -1.0),
		vec3f(1.0, -1.0, -1.0),
		vec3f(1.0,  1.0, -1.0)
	};

	const std::vector<uint32_t> cube_indices
	{
		0, 1, 2, 3,
		3, 2, 6, 7,
		7, 6, 5, 4,
		4, 5, 1, 0,
		0, 3, 7, 4,
		1, 2, 6, 5,
	};
}

const std::vector<std::string> cubefaces = {
	DIR_CUBEMAP"right.jpg",
	DIR_CUBEMAP"left.jpg",
	DIR_CUBEMAP"top.jpg",
	DIR_CUBEMAP"bottom.jpg",
	DIR_CUBEMAP"back.jpg",
	DIR_CUBEMAP"front.jpg"
};


EnvironmentRenderer::EnvironmentRenderer()
	: texture(LOAF_CUBE_MAP(cubefaces))
{
	loadCubeMap(skyboxVertices);
}


EnvironmentRenderer::~EnvironmentRenderer()
{
	if (vao)
		glDeleteVertexArrays(1,&vao);
	if (vbo)
		glDeleteBuffers(1, &vbo);
}

void EnvironmentRenderer::render(const Camera &camera)
{
	shader->bind();
	glBindVertexArray(vao);
	//attrib index we didnt define attribvertexpointer
	//so allow to enalbe attrib array as "in vec3 position" no location = 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, vertices_count/3);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader->unbind();
}

void EnvironmentRenderer::loadCubeMap(const std::vector<float>& data)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	//we dont use it attrib vertext array now
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	vertices_count = data.size();

}

