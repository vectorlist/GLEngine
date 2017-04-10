#pragma once

#include <config.h>
#include <vector>

class Renderer
{
public:
	Renderer();
	~Renderer();

	//condition
	bool isRunninig = false;

	//---------- pass OpenGL func  ----------
	void initialize();
	void render();
	void resize(uint32_t width, uint32_t height);
	//------------ Uniforms -----------------
	void updateUniforms();


	Render_Mode mode;
	
	std::vector<model_ptr> models;
	std::vector<geometry_ptr> geometry;
	GLuint shaders[SHADER_MAX_NUM];

	/*Render_Mode mode;*/
	void addElement(model_ptr &models);
	void addElement(geometry_ptr &geo);

	void setRenderMode(Render_Mode m);
private:
	//redner mode
	void render_forward();
	void render_terrian();
	void render_flat();

	//Setting
	uint32_t frame = 0;
	float aspect_ratio;
	
};

inline void Renderer::addElement(model_ptr &model)
{
	//models.push_back(std::move(model)); //unique ptr
	models.push_back(model);
}

inline void Renderer::addElement(geometry_ptr &geo)
{
	//models.push_back(std::move(model)); //unique ptr
	geometry.push_back(geo);
}

inline void Renderer::setRenderMode(Render_Mode m)
{
	mode = m;
}

