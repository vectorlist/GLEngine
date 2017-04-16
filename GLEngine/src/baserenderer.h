#pragma once

#include <config.h>
#include <vector>
#include <Mesh.h>

class AbstractRenderer
{
public:
	AbstractRenderer() : mode(RENDER_FORWARD){}
	virtual~AbstractRenderer(){}

	std::vector<model_ptr> models;
	std::vector<terrain_ptr> terrains;
	//std::vector<camera_ptr> cameras;
	std::vector<text_ptr> texts;

	//PerspectiveCamera* current_camera();
	void setRenderMode(Render_Mode m);

	uint32_t frame = 0;
	float aspect_ratio;

	Render_Mode mode;
	std::string mode_string;
	
	float fps = 0.0f;
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