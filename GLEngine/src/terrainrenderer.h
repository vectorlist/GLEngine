#pragma once

#include <config.h>

class TerrainShader;
class TerrainRenderer
{
public:
	TerrainRenderer();
	~TerrainRenderer();

	void Render(const std::vector<terrain_ptr>& terrains);

	//TerrainShader &shader;
	TerrainShader *shader;
};

