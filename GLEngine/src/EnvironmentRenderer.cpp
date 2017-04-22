#include "EnvironmentRenderer.h"
#include <loadmanager.h>
namespace 
{
	constexpr float size = 500.0f;
	std::vector<float> skyboxVertices = 
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
}


EnvironmentRenderer::EnvironmentRenderer(SkyShader* shader, const std::vector<std::string> &faces)
	: texture(LOAF_CUBE_MAP(faces))
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	for (int i = 0; i < skyboxVertices.size(); i += 3)
	{
		Vertex vertex;
		vertex.pos.x = skyboxVertices[i];
		vertex.pos.x = skyboxVertices[i + 1];
		vertex.pos.x = skyboxVertices[i + 2];
		vertex.normal = vec3f();
		vertex.st = vec2f();
		vertex.tangent = vec3f();
		vertex.bitangent = vec3f();
	}
	mesh = Mesh(vertices, indices);
}


EnvironmentRenderer::~EnvironmentRenderer()
{
}

void EnvironmentRenderer::render()
{
}
