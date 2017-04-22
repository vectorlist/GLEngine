#pragma once

#include <mesh.h>

class Texture;
class SkyShader;
class EnvironmentRenderer
{
public:
	EnvironmentRenderer(SkyShader* shader, const std::vector<std::string> &faces);
	~EnvironmentRenderer();

	void render();

	Mesh mesh;
	SkyShader* shader;
	Texture* texture;
};

