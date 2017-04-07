#include "Renderer.h"
#include <Model.h>

Renderer::Renderer()
	: mode(MODE_DEFAULT)
{

}


Renderer::~Renderer()
{

}

void Renderer::initialize()
{
	glClearColor(0, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::render()
{
	switch (mode)
	{
	case MODE_DEFAULT:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_defualt();
		break;
	case MODE_SECOND:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_second();
		break;
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//we dont need swapbuffer(SDL_GL_swapwindow())
}

void Renderer::resize(uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
}

void Renderer::render_defualt()
{
	glClearColor(0, 1, 1, 1);
	//LOG << "render defuatl" << ENDL;
	glUseProgram(shader[SHADER_DEFUALT]);
	for (auto model : models) 
	{
		//SAHDER & MATRIX
		//ATTRIB
		for (auto mesh : model->meshs)
		{
			//

			//VAO
			glBindVertexArray(mesh->vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(NULL);

		}
	}
	glUseProgram(NULL);
}

void Renderer::render_second()
{
	glClearColor(1, 1, 0, 1);
	//LOG << "redner second" << ENDL;
}
