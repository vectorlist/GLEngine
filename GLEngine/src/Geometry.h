#pragma once

#include <config.h>
//#include <SDL2/SDL.h>
enum Map_Type
{
	RGB8 =1,
	RGBA8,
	RGB16,
	RGBA16,
	RGB32,
	RGBA32
};

class SDL_Surface;
class Geometry
{
public:
	Geometry();
	~Geometry();

	/*std::vector<mesh_ptr> meshs;*/
	std::vector<Mesh*> meshs;

	//terrain
	/*void loadHeightMap(
		const std::string &filename, int scale = 1000);*/

	void loadTerrain(
		const std::string &filename, float planeScale, float heightScale, unsigned int scale_size);

	/*void buildScaledMesh(int geoZ, int geoX, int perScale,
		Mesh* mesh, SDL_Surface* map);*/
	void buildScaledMesh(int geoZ, int geoX, int perScale,
		Mesh* mesh, SDL_Surface* map);

	// get pixel for height value
	float getHeightPixel(int x, int z, SDL_Surface* surface);

	//test
	vec3f calculateNormal(int x, int z, SDL_Surface* map, float p, float h);
	
	void buildFlatTerrain();

private:
	float geo_scale = 100;
	//float height_scale = 1.f;

	int x_size;
	int z_size;
	
	//test
	bool overScale = false;

	int total_x, total_z;
	int scale_size;

};

