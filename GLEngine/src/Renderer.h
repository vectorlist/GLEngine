#pragma once

#include <abstractrenderer.h>
#include <vector>
#include <Mesh.h>
#include <light.h>
#include <forwardshader.h>
#include <terrainshader.h>
#include <skyshader.h>



class Camera;
class Renderer : public AbstractRenderer
{
public:
	Renderer();
	~Renderer();

	//condition

	//---------- pass OpenGL func  ----------
	void initialize();
	void render();
	void resize(uint32_t width, uint32_t height);
	void renderText();
	
	//Light uniform_light;
	//TODO : replace to UBO
	UBOLight light;
	std::shared_ptr<ForwardShader>	forwardShader;
	std::shared_ptr<TerrainShader>	terrainShader;
	std::shared_ptr<SkyShader>		skyShader;

	camera_ptr camera;
	player_ptr player;

	void initUniforms();
	void updateUniforms();
	void rebuildShaders();

	//STATIC
	static float FOV;
	static float NEAR_PLANE;
	static uint32_t width;
	static uint32_t height;
	
	float isShadowView = 0.0f;
private:
	//redner mode
	void renderEntities();


};



inline void Renderer::rebuildShaders()
{
	LOG << "rebuild shaders..." << ENDL;
	forwardShader.reset();
	terrainShader.reset();
	skyShader.reset();

	if (!forwardShader) {
		forwardShader =
			std::make_shared<ForwardShader>
			(DIR_SHADER"forward.vert", DIR_SHADER"forward.frag");
	}
		
	if (!terrainShader) {
		terrainShader =
			std::make_shared<TerrainShader>
			(DIR_SHADER"terrain.vert", DIR_SHADER"terrain.frag");
	}
	
	if (!skyShader) {
		skyShader =
			std::make_shared<SkyShader>(DIR_SHADER"sky.vert", DIR_SHADER"sky.frag");
	}
	initUniforms();
}