#pragma once

#include <mesh.h>
#include <Camera.h>

struct TEST
{

};

class Texture;
class SkyShader;
class EnvironmentRenderer
{
public:
	EnvironmentRenderer();
	~EnvironmentRenderer();

	void render(const Camera &camera);

	void loadCubeMap(const std::vector<float> &data);
	/*Mesh* mesh;*/
	GLuint vao;
	GLuint vbo;
	uint32_t vertices_count;
	SkyShader* shader;
	Texture* texture;
};

