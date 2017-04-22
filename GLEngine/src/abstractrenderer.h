#pragma once

#include <config.h>
#include <vector>
#include <Mesh.h>
#include <shader.h>

class AbstractRenderer
{
public:
	AbstractRenderer() : mode(RENDER_FORWARD){}
	virtual~AbstractRenderer(){}

	std::vector<model_ptr> models;
	std::vector<entity_ptr> entities;
	std::vector<terrain_ptr> terrains;
	std::vector<text_ptr> texts;

	struct
	{
		Matrix4x4 proj;
		Matrix4x4 text;
	}projection;

	void setRenderMode(Render_Mode m);
	bool isRunninig = false;
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
	AbstractRenderer& operator<<(entity_ptr &e);
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

inline AbstractRenderer& AbstractRenderer::operator<<(entity_ptr &e)
{
	this->entities.push_back(e);
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

