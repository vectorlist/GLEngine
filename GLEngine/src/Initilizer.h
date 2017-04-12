#pragma once
#include <Renderer.h>
#include <Model.h>
#include <Shader.h>
#include <Geometry.h>
#include <Camera.h>

namespace Initializer
{
	void initCamera(Renderer &renderer);
	void initScene(Renderer &renderer);
	void initTextures(Renderer &renderer);
}

inline void Initializer::initCamera(Renderer &renderer)
{
	camera_ptr camera = camera_ptr(new Camera(vec3f(0, 20, 20)));
	renderer.cameras.push_back(camera);
}

inline void Initializer::initScene(Renderer &renderer)
{

	//model_ptr model= model_ptr(new Model(DIR_MODEL"plane.obj"));
	//model_ptr model_1 = model_ptr(new Model(DIR_MODEL"stone.obj"));
	//renderer.addElement(model);
	//renderer.addElement(model_1);
	geometry_ptr geo = geometry_ptr(new Geometry);
	//geo->loadTerrain(DIR_HEIGHT"height_map_1024.jpg", 2, 100, 1024,0.05f);
	geo->loadTerrain(DIR_HEIGHT"height_map_256.jpg", 2, 100, 256, 0.05f);
	geo->loadFlatTerrain(100, 100,20);
	geo->matrix.translate(vec3f(0, -.5, 0));
	renderer.addElement(geo);

	renderer.shaders[SHADER_FORWARD] = Shader::load(DIR_SHADER"forwards.vert", DIR_SHADER"forwards.frag");
	renderer.shaders[SHADER_TERRAIN] = Shader::load(DIR_SHADER"terrain.vert", DIR_SHADER"terrain.frag");
	renderer.shaders[SHADER_FLAT] = Shader::load(DIR_SHADER"flat.vert", DIR_SHADER"flat.frag");
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
	for (auto &geo : renderer.geometry) {
		for (auto &mesh : geo->meshes) {
			if (mesh.maps.diffuse == NULL) {
				mesh.setTexture(FILE_DEFAULT_DIFFUSE, false, TEXTURE_DIFFUSE);
			}
			terrain_mesh_count++;
		}
	}
	LOG << "loaded mesh         : " << terrain_mesh_count << ENDL;
	LOG << "loaded terrain mesh : " << terrain_mesh_count << ENDL;
	LOG << "loaded textures     : " << Mesh::global_textures.size() << ENDL;
}