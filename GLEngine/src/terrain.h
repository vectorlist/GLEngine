#pragma once

#include <config.h>
#include <string>
#include <Mesh.h>
#include <matrix4x4.h>
#include <SDL2/SDL_image.h>

struct TerrainTexure
{
	Texture* background;
	Texture* textureR;
	Texture* textureG;
	Texture* textureB;
	Texture* textureBlend;
};

struct TerrainCreateInfo
{
	float x;
	float z;
	TerrainTexure textures;
	std::string heightFilePath;
};

class Terrain {
public:
	Terrain(const TerrainCreateInfo &info);
	~Terrain();
	
	float getHeightOfTerrain(float worldX, float worldZ) const;

	Mesh* mesh;
	Matrix4x4 matrix;
	TerrainTexure textures;
	float get_x()const;
	float get_z()const;
	vec3f get_relative_pos() const;

private:
	std::vector<std::vector<float>> heights;
	Mesh* generateTerrain(const std::string& height_map_path);
	Mesh* generateFlatTerrain();

	float	relative_x;
	float	relative_z;

	
	vec3f get_normal(unsigned int x, unsigned int z,
		SDL_Surface* map);
	float get_height(unsigned int x, unsigned int z, 
		SDL_Surface* map);

	static float barryCentric(
		vec3f p1, const vec3f p2,
		vec3f p3, const vec2f pos);

};


inline float Terrain::get_x()const { return relative_x; }
inline float Terrain::get_z()const { return relative_z; }
inline vec3f Terrain::get_relative_pos() const 
{ 
	return vec3f(relative_x, 0.0f, relative_z);
}

