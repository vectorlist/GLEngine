#pragma once
#include <Renderer.h>
#include <Model.h>
#include <Shader.h>
#include <camera.h>
#include <text.h>
#include <terrain.h>

namespace Initializer
{
	void initCamera(Renderer &renderer, PlayerCamera &camera);
	void initScene(Renderer &renderer);
	void initTextures(Renderer &renderer);
}

//must be local in main
inline void Initializer::initCamera(Renderer &renderer, PlayerCamera &camera)
{
	//Perspective Camera
	//renderer.camera.perspective = new PerspectiveCamera(vec3f(6.8, 5.3, 24.7));

	//Player Camera
	renderer.camera = &camera;
}

inline void Initializer::initScene(Renderer &renderer)
{
	//auto m0 = model_ptr(new Model(DIR_MODEL"box.obj"));
	//renderer << m0;

	auto t0 = terrain_ptr(new Terrain(-1, 0, DIR_TEXTURE"glass.jpg",
		DIR_HEIGHT"height_map_64_t.jpg"));
	auto t1 = terrain_ptr(new Terrain(0, 0, DIR_TEXTURE"desert_diffuse.jpg",
		DIR_HEIGHT"height_map_64_t.jpg"));

	auto t2 = terrain_ptr(new Terrain(0, -1, DIR_TEXTURE"dirt01.jpg",
		DIR_HEIGHT"height_map_64_t.jpg"));
	auto t3 = terrain_ptr(new Terrain(-1, -1, DIR_TEXTURE_TERRAIN"desert01.jpg",
	DIR_HEIGHT"height_map_64_t.jpg"));
	//test flat
	/*auto t0 = terrain_ptr(new Terrain(-1, 0, DIR_TEXTURE"glass.jpg"));
	auto t1 = terrain_ptr(new Terrain(0, 0, DIR_TEXTURE"desert_diffuse.jpg"));

	auto t2 = terrain_ptr(new Terrain(0, -1, DIR_TEXTURE"dirt01.jpg"));
	auto t3 = terrain_ptr(new Terrain(-1, -1, DIR_TEXTURE"glass.jpg"));*/
	renderer << t0 << t1 << t2 << t3;

	renderer.shaders[SHADER_FORWARD] = Shader::load(DIR_SHADER"forwards.vert", DIR_SHADER"forwards.frag");
	renderer.shaders[SHADER_TERRAIN] = Shader::load(DIR_SHADER"terrain.vert", DIR_SHADER"terrain.frag");
	renderer.shaders[SHADER_FLAT] = Shader::load(DIR_SHADER"flat.vert", DIR_SHADER"flat.frag");
	renderer.shaders[SHADER_TEXT] = Shader::load(DIR_SHADER"text.vert", DIR_SHADER"text.frag");
	renderer.shaders[SHADER_PLAYER] = Shader::load(DIR_SHADER"player.vert", DIR_SHADER"player.frag");
}

inline void Initializer::initTextures(Renderer &renderer)
{
	int mesh_count = 0;
	for (auto &model : renderer.models) {
		for (auto &mesh : model->meshes) {
			if (mesh.maps.diffuse == NULL) {
				mesh.setTexture(FILE_DEFAULT_DIFFUSE, false, TEXTURE_DIFFUSE);
			}
			mesh_count++;
		}
	}
	int terrain_mesh_count = 0;
	for (auto &terrain : renderer.terrains) {
		
		auto& mesh = terrain->mesh;
		if (mesh.maps.diffuse == NULL) {
			mesh.setTexture(FILE_DEFAULT_DIFFUSE, false, TEXTURE_DIFFUSE);
		}
		terrain_mesh_count++;
	}
	LOG << "loaded mesh         : " << terrain_mesh_count << ENDL;
	LOG << "loaded terrain mesh : " << terrain_mesh_count << ENDL;
	LOG << "loaded textures     : " << Mesh::global_textures.size() << ENDL;
}