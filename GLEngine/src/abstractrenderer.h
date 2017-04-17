#pragma once

#include <config.h>
#include <vector>
#include <Mesh.h>
#include <Shader.h>

class AbstractRenderer
{
public:
	AbstractRenderer() : mode(RENDER_FORWARD){}
	virtual~AbstractRenderer(){}

	std::vector<model_ptr> models;
	std::vector<terrain_ptr> terrains;
	std::vector<text_ptr> texts;

	void setRenderMode(Render_Mode m);
	void initAllShaders();
	void updateAllShader();

	uint32_t frame = 0;
	float aspect_ratio;

	Render_Mode mode;
	std::string mode_string;
	
	float fps = 0.0f;
	//Debug
	float terrain_height = 0.f;
	uint32_t terrain_id;
	GLuint shaders[SHADER_MAX_NUM];

	uint32_t width, height;

	AbstractRenderer& operator<<(model_ptr &t);
	AbstractRenderer& operator<<(terrain_ptr &t);
	AbstractRenderer& operator<<(text_ptr &t);
};

inline AbstractRenderer& AbstractRenderer::operator<<(terrain_ptr &ptr)
{
	this->terrains.push_back(ptr);
	return *this;
}

inline AbstractRenderer& AbstractRenderer::operator<<(model_ptr &ptr)
{
	this->models.push_back(ptr);
	return *this;
}

inline AbstractRenderer& AbstractRenderer::operator<<(text_ptr &ptr)
{
	this->texts.push_back(ptr);
	return *this;
}

//inline PerspectiveCamera* AbstractRenderer::current_camera()
//{
//	return cameras[0].get();
//}

inline void AbstractRenderer::setRenderMode(Render_Mode m)
{
	mode = m;
	mode_string = modeToString(mode);
}

inline void AbstractRenderer::initAllShaders()
{
	shaders[SHADER_FORWARD] = Shader::load(DIR_SHADER"forwards.vert", DIR_SHADER"forwards.frag");
	shaders[SHADER_TERRAIN] = Shader::load(DIR_SHADER"terrain.vert", DIR_SHADER"terrain.frag");
	shaders[SHADER_FLAT] = Shader::load(DIR_SHADER"flat.vert", DIR_SHADER"flat.frag");
	shaders[SHADER_PLAYER] = Shader::load(DIR_SHADER"player.vert", DIR_SHADER"player.frag");
	shaders[SHADER_TEXT] = Shader::load(DIR_SHADER"text.vert", DIR_SHADER"text.frag");

}

inline void AbstractRenderer::updateAllShader()
{

	for (auto &shader : shaders)
	{
		if (shader)
			glDeleteProgram(shader);
	}
	initAllShaders();
	LOG << "update shaders" << ENDL;
}