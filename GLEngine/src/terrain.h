#pragma once
#include <config.h>
#include <string>
#include <Mesh.h>
#include <matrix4x4.h>

#define		TERRIAN_SIZE  800.f
#define		TERRAIN_FLAT_VERTEX_SIZE		128
#define		MAX_HEIGHT  40.0f
#define		MAX_PIXEL_COLOR  16777216.0f
#define		MAX_PIXEL_COLOR_RGB 256.f * 256.f * 256.f

class Terrain {
public:
	Terrain::Terrain(float x, float z,
		const std::string &texture_path, 
		std::string height_map_path = "");

	Mesh generateTerrain(
		const std::string &texture_path,
		const std::string& height_map_path);
	Mesh generateFlatTerrain(
		const std::string &texture_path);
	
	float getHeightOfTerrain(float worldX, float worldZ) const;

	Mesh mesh;
	Matrix4x4 matrix;
	float barryCentric(vec3f p1, vec3f p2,
		vec3f p3, vec2f pos) const;

	float get_x()const;
	float get_z()const;
	vec3f get_relative_pos() const;
private:
	std::vector<std::vector<float>> heights_;
	

	float	relative_x;
	float	relative_z;

	
	vec3f get_normal(unsigned int x, unsigned int z,
		SDL_Surface* map);
	float get_height(unsigned int x, unsigned int z, 
		SDL_Surface* map);

};


inline float Terrain::get_x()const { return relative_x; }
inline float Terrain::get_z()const { return relative_z; }
inline vec3f Terrain::get_relative_pos() const 
{ 
	return vec3f(relative_x, 0.0f, relative_z);
}