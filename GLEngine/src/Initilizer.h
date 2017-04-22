#pragma once
#include <Renderer.h>
#include <Model.h>
#include <shadertool.h>
#include <camera.h>
#include <text.h>
#include <terrain.h>
#include <loadmanager.h>
#include <player.h>
#include <entity.h>
#include <utils.h>

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
	player_ptr player = player_ptr(new Player(*boxman.get(), vec3f(0, 0, 0), 0, 0, 0));
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

	renderer.skyShader =
		std::make_shared<SkyShader>(DIR_SHADER"sky.vert", DIR_SHADER"sky.frag");
	/*----------------------------Lights ---------------------------------*/


	/*---------------------------- Scene ---------------------------------*/
	//based model
	model_ptr rock01 = model_ptr(new Model(DIR_MODEL"rock/rock01.obj", DIR_MODEL"rock/rock01.jpg"));

	renderer << rock01;

	//check terrain id
	auto terrainID = [](float x, float z)
	{
		if (x < 0.f && z > 0)  return 0;
		else if (x >= 0.f && z >= 0) return 1;  //x 0-800 z 0-800
		else if (x >= 0.0f && z < 0) return 2;  //0 -- 800 0 --- -800
		else if (x < 0.0f && z < 0) return 3;  //0 -- -800 0 --- -800
	};

	auto randomTerrainPos = [&]
	{
		//first we need -800  to 800 rand flaot
		float x = 1 - RAND_FLOAT() * 800 + 400;
		float z = 1 - RAND_FLOAT() * 800 + 400;

		//second pick terrain id
		auto id = terrainID(x, z);
		//get height y position
		float y = renderer.terrains[id]->getHeightOfTerrain(x,z);
		return vec3f(x, y, z);
 	};
	
	//TODO : mix object with random and scale texture offset selective st
	for (int i = 0; i < 100; ++i)
	{
		//instance
		vec3f rpos = randomTerrainPos();
		entity_ptr rock = entity_ptr(new Entity(*rock01.get(), 
			rpos, 0, 0, 0, 3));
		renderer << rock;
	}

	

}

inline void Initializer::initTextures(Renderer &renderer)
{
	

	
	LOG << "loaded textures     : " << LoadManager::loadedTextures.size() << ENDL;
}