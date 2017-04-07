#pragma once

#include <config.h>
#include <vector>

enum Render_Mode
{
	MODE_DEFAULT = 0,
	MODE_SECOND
};


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
	//---------------------------------------
	Render_Mode mode;
	
	std::vector<model_ptr> models;
	GLuint shader[SHADER_MAX_NUM];

	/*Render_Mode mode;*/
	void addElement(model_ptr &models);
private:
	//redner mode
	void render_defualt();
	void render_second();
};

inline void Renderer::addElement(model_ptr &model)
{
	//models.push_back(std::move(model)); //unique ptr
	models.push_back(model);
}

