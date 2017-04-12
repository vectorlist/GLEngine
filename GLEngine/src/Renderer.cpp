#include "Renderer.h"
#include <Model.h>
#include <Shader.h>
#include <Geometry.h>
#include <Camera.h>

Renderer::Renderer()
	: mode(RENDER_FORWARD)
{

}


Renderer::~Renderer()
{

}

void Renderer::initialize()
{
	glClearColor(0, 1, 1, 1);
	/*glEnable(GL_DEPTH_TEST);*/

}

void Renderer::render()
{
	update_uniform();
	switch (mode)
	{
	case RENDER_FORWARD:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_forward();
		break;
	case RENDER_TERRIAN:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_terrian();
		break;
	case RENDER_FLAT:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		render_flat();
		break;
	}
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBindVertexArray(0);
	glUseProgram(0);
	//we dont need swapbuffer(SDL_GL_swapwindow())
	frame++;
}

void Renderer::resize(uint32_t width, uint32_t height)
{
	aspect_ratio = float(width) / float(height);
	glViewport(0, 0, width, height);
}

void Renderer::init_uniforms()
{
	//update shared unform to all shaders
	Matrix4x4 proj = vml::perspective(45.f, aspect_ratio, 0.001f, 1000.f);
	if (!cameras.size())
		LOG_ERROR("empty camera");
	for (auto program : shaders)
	{
		glUseProgram(program);
		//set matrix
		Shader::setUniformMatrix4f(program, proj, "proj", true);
		Shader::setUniformMatrix4f(program, current_camera()->view(), "view", true);
	}
	//unbind shader
	glUseProgram(0);
}

void Renderer::update_uniform()
{
	for (auto program : shaders) {
		glUseProgram(program);
		Shader::setUniformMatrix4f(program, current_camera()->view(), "view", true);
	}
	glUseProgram(0);
}

void Renderer::render_forward()
{
	glClearColor(0.15, 0.2, 0.25, 1);

	GLuint &shader_defualt = shaders[SHADER_FORWARD];
	glUseProgram(shader_defualt);

	for (auto &model : models)
	{
		//SAHDER & MATRIX
		Matrix4x4 world;
		Shader::setUniformMatrix4f(shader_defualt, world, "model", true);
		//ATTRIB
		int id = 0;
		for (auto &mesh : model->meshes)
		{
			//Matrix
			if (id == 0) {
				Matrix4x4 m;
				m.translate(vec3f(0, 1, 0));
				Shader::setUniformMatrix4f(shader_defualt, m, "model", true);
			}

			//Diffuse
			glActiveTexture(GL_TEXTURE0);
			GLuint diffuse_id = glGetUniformLocation(shader_defualt, "diffuse_map");
			glUniform1i(diffuse_id, 0);
			glBindTexture(GL_TEXTURE_2D, mesh.maps.diffuse->id);

			////Normal
			//
			//glActiveTexture(GL_TEXTURE1);
			//GLuint normal_id = glGetUniformLocation(shader_defualt, "normal_map");
			//glUniform1i(normal_id, 1);
			//glBindTexture(GL_TEXTURE_2D, mesh->map.normal->id);

			//VAO
			glBindVertexArray(mesh.vao);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES,
				mesh.indices.size(), GL_UNSIGNED_INT, NULL);
			glBindVertexArray(NULL);
			id++;
		}

	}
	render_terrian();
	//unbind all texture
	for (uint32_t i = 0; i < MAP_MAX_NUM; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
	//unbind shader
	glUseProgram(NULL);
}

void Renderer::render_terrian()
{
	glClearColor(0.15, 0.2, 0.25, 1);

	GLuint &shader_terrain = shaders[SHADER_TERRAIN];
	glUseProgram(shader_terrain);

	Shader::setUniform1i(shader_terrain, frame, "frame");
	for (auto &geo : geometry)
	{
		//SAHDER & MATRIX
		Shader::setUniformMatrix4f(shader_terrain, geo->matrix, "model", true);

		//ATTRIB
		int id = 0;
		for (auto &mesh : geo->meshes)
		{

			glActiveTexture(GL_TEXTURE0);
			GLuint diffuse_id = glGetUniformLocation(shader_terrain, "terrain_diffuse");
			glUniform1i(diffuse_id, 0);

			glBindTexture(GL_TEXTURE_2D, mesh.maps.diffuse->id);
	
			mesh.render();
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
		for (auto &mesh : model->meshes)
		{
			//Matrix
			if (id == 1) {
				Matrix4x4 m;
				m.translate(vec3f(1, 0, 0));
				Shader::setUniformMatrix4f(flat, m, "model", true);
			}
			//VAO
			glBindVertexArray(mesh.vao);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);
			glBindVertexArray(NULL);
			id++;
		}

	}
	
	//unbind shader
	glUseProgram(NULL);
}
