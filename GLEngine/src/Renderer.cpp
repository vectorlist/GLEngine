#include "Renderer.h"
#include <Model.h>
#include <Shader.h>

Renderer::Renderer()
	: mode(MODE_FORWARD)
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
	case MODE_FORWARD:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_forward();
		break;
	case MODE_FLAT:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_flat();
		break;
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//we dont need swapbuffer(SDL_GL_swapwindow())
	frame++;
}

void Renderer::resize(uint32_t width, uint32_t height)
{
	aspect_ratio = float(width) / float(height);
	glViewport(0, 0, width, height);
}

void Renderer::updateUniforms()
{
	//update shared unform to all shaders
	Matrix4x4 proj = vml::perspective(45.f, aspect_ratio, 0.001f, 1000.f);
	Matrix4x4 view;
	//view.translate(vec3f(0, 0, -1));
	view = vml::lookAt(vec3f(0.2, 1, 3), vec3f(0, 0, 0), vec3f(0, 1, 0));
	for (auto program : shaders)
	{
		//set matrix
		Shader::setUniformMatrix4f(program,proj,"proj",true);
		Shader::setUniformMatrix4f(program, view, "view", true);
	}
}

void Renderer::render_forward()
{
	glClearColor(0.15, 0.2, 0.25, 1);
	
	GLuint &shader_defualt = shaders[SHADER_FORWARD];
	glUseProgram(shader_defualt);

	Shader::setUniform1i(shader_defualt, frame, "frame");
	for (auto &model : models) 
	{
		//SAHDER & MATRIX
		Matrix4x4 world;
		Shader::setUniformMatrix4f(shader_defualt, world, "model", true);
		//ATTRIB

		int id = 0;
		for (auto &mesh : model->meshs)
		{
			//Matrix
			if (id == 1) {
				Matrix4x4 m;
				m.translate(vec3f(1, 0, 0));
				Shader::setUniformMatrix4f(shader_defualt, m, "model", true);
				Shader::setUniform1i(shader_defualt, frame+100, "frame");
			}

			//Texture Map
			glActiveTexture(GL_TEXTURE0);
			GLuint diffuse_id = glGetUniformLocation(shader_defualt, "diffuse_map");
			glUniform1i(diffuse_id, 0);
			
			glBindTexture(GL_TEXTURE_2D, mesh->map.diffuse->id);
			//VAO
			glBindVertexArray(mesh->vao);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, NULL);
			glBindVertexArray(NULL);
			id++;
		}

	}
	//unbind all texture
	for (uint32_t i = 0; i < MAP_MAX_NUM; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
	//unbind shader
	glUseProgram(NULL);
}

void Renderer::render_flat()
{
	glClearColor(.44, .4, .1, 1);
	//ref for performace
	GLuint &flat = shaders[SHADER_FLAT];
	if (flat < 0) return;
	glUseProgram(flat);

	//Shader::setUniform1i(shader_defualt, frame, "frame");
	for (auto &model : models)
	{
		//SAHDER & MATRIX
		Matrix4x4 world;
		Shader::setUniformMatrix4f(flat, world, "model", true);
		//ATTRIB

		int id = 0;
		for (auto &mesh : model->meshs)
		{
			//Matrix
			if (id == 1) {
				Matrix4x4 m;
				m.translate(vec3f(1, 0, 0));
				Shader::setUniformMatrix4f(flat, m, "model", true);
			}
			//VAO
			glBindVertexArray(mesh->vao);
			glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, NULL);
			glBindVertexArray(NULL);
			id++;
		}

	}
	
	//unbind shader
	glUseProgram(NULL);
}
