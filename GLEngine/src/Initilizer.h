#pragma once
#include <Renderer.h>
#include <Model.h>
#include <shadertool.h>
#include <camera.h>
#include <text.h>
#include <terrain.h>
#include <loadmanager.h>
#include <player.h>

namespace Initializer
{
	void initCamera(Renderer &renderer);
	void initScene(Renderer &renderer);
	void initTextures(Renderer &renderer);
}

//must be local in main
inline void Initializer::initCamera(Renderer &renderer)
{
	model_ptr boxman = model_ptr(new Model(DIR_MODEL"boxman/boxman.obj",
		DIR_MODEL"boxman/boxman.jpg"));

	/*model_ptr boxman = model_ptr(new Model(DIR_MODEL"stone.obj",
		DIR_MODEL"boxman/boxman.jpg"));*/
	renderer << boxman;
	player_ptr player = player_ptr(new Player(*boxman.get(), vec3f(0, 0, 0), 0, 0, 0,5));
	renderer.player = player;
	renderer << (entity_ptr)player;
	camera_ptr camera = camera_ptr(new Camera(*player.get()));
	renderer.camera = camera;
}

inline void Initializer::initScene(Renderer &renderer)
{
	//renderer.initAllShaders();


	/*--------------------------- Terrain --------------------------------*/
	TerrainTexure terrain_textures{};
	terrain_textures.background = LOAD_TEXTURE(DIR_TEXTURE_TERRAIN"grass02.jpg");
	terrain_textures.textureR = LOAD_TEXTURE(DIR_TEXTURE_TERRAIN"sand01.jpg");
	terrain_textures.textureG = LOAD_TEXTURE(DIR_TEXTURE_TERRAIN"sand02.jpg");
	terrain_textures.textureB = LOAD_TEXTURE(DIR_TEXTURE_TERRAIN"dirt01.jpg");
	terrain_textures.textureBlend = LOAD_TEXTURE_CLAMP(DIR_TEXTURE_TERRAIN"blend00/blend_03.jpg");

	TerrainCreateInfo terrainInfo{};
	terrainInfo.x = -1;
	terrainInfo.z = 0;
	terrainInfo.heightFilePath = DIR_HEIGHT"height_map_64_t.jpg";
	terrainInfo.textures = terrain_textures;

	auto t0 = terrain_ptr(new Terrain(terrainInfo));
	terrainInfo.x = 0;
	terrainInfo.z = 0;
	terrainInfo.textures.textureBlend = LOAD_TEXTURE_CLAMP(DIR_TEXTURE_TERRAIN"blend00/blend_04.jpg");
	auto t1 = terrain_ptr(new Terrain(terrainInfo));
	terrainInfo.x = 0;
	terrainInfo.z = -1;
	terrainInfo.textures.textureBlend = LOAD_TEXTURE_CLAMP(DIR_TEXTURE_TERRAIN"blend00/blend_02.jpg");
	auto t2 = terrain_ptr(new Terrain(terrainInfo));
	terrainInfo.x = -1;
	terrainInfo.z = -1;
	terrainInfo.textures.textureBlend = LOAD_TEXTURE_CLAMP(DIR_TEXTURE_TERRAIN"blend00/blend_01.jpg");
	auto t3 = terrain_ptr(new Terrain(terrainInfo));
	
	renderer << t0 << t1 << t2 << t3;

	/*-----------------------------------------------------------------------*/
	renderer.forwardShader = 
		std::make_shared<ForwardShader>(DIR_SHADER"forward.vert", DIR_SHADER"forward.frag");

	renderer.shaders[SHADER_TEXT] = ShaderTool::load(DIR_SHADER"text.vert", DIR_SHADER"text.frag");
	renderer.terrainShader =
		std::make_shared<TerrainShader>(DIR_SHADER"terrain.vert", DIR_SHADER"terrain.frag");

	/*----------------------------Lights ---------------------------------*/
;

	/*std::vector<GLuint> enabled_uniforms_shader{ renderer.shaders[SHADER_TERRAIN] };
	renderer.uniform_light.setLight();
	renderer.uniform_light.initLightUniform(enabled_uniforms_shader);*/



}

inline void Initializer::initTextures(Renderer &renderer)
{
	

	
	LOG << "loaded textures     : " << LoadManager::loadedTextures.size() << ENDL;
}