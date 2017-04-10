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

	std::vector<Mesh*> meshs;

	void loadTerrain(
		const std::string &filename, float planeScale, float heightScale, unsigned int scale_size);

	void buildScaledMesh(int geoZ, int geoX, int perScale,
		Mesh* mesh, SDL_Surface* map);

	float getHeightPixel(int x, int z, SDL_Surface* surface);

	vec3f getNormal(int x, int z, SDL_Surface* map, float p, float h);
	
	void loadFlatTerrain();
	int x_size;
	int z_size;
private:
	float geo_scale = 100;
	//float height_scale = 1.f;

	
	//test
	bool overScale = false;

	int total_x, total_z;
	int scale_size;

public:
	Matrix4x4 matrix;
	Matrix4x4 matrix_scale;
	Matrix4x4 matrix_trans;
	vec3f tran;

};

