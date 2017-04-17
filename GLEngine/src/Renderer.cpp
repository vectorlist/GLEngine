#include "Renderer.h"
#include <Model.h>
#include <Shader.h>
#include <camera.h>
#include <text.h>
#include <terrain.h>
#include <player.h>

Renderer::Renderer()
	: AbstractRenderer()
{

}


Renderer::~Renderer()
{

}

void Renderer::initialize()
{
	glClearColor(0, 1, 1, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	auto text = text_ptr(new Text(FILE_TEXT_SEGOEUI, 16));
	*this << text;
}

void Renderer::render()
{
	//update all shader view matrix
	update_view_matrix();

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
	
	render_text();
	glBindVertexArray(0);
	glUseProgram(0);
	frame++;
}

void Renderer::resize(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
	aspect_ratio = float(width) / float(height);
	//text_proj = vml::ortho(0.f, (float)width, 0.f, (float)height);
	glViewport(0, 0, width, height);
}

void Renderer::init_view_matrix()
{

	//update shared unform to all shaders
	projection.proj = vml::perspective(45.f, aspect_ratio, 0.001f, 1000.f);
	projection.text = vml::ortho(0.f, (float)width, 0.f, (float)height);
	
	for (auto program : shaders)
	{
		//text shader dont need to view mat
		if (program == shaders[SHADER_TEXT]) continue;
		if (program == shaders[SHADER_PLAYER])
		{
			LOG << "add player shader uniforms" << ENDL;
		}
		glUseProgram(program);
		//set matrix
		Shader::setUniformMatrix4f(program, projection.proj, "proj", true);
		Shader::setUniformMatrix4f(program, camera->viewMatrix(), "view", true);
	}
	//unbind shader
	glUseProgram(0);
}

void Renderer::update_view_matrix()
{
	for (auto program : shaders) {
		glUseProgram(program);
		Shader::setUniformMatrix4f(program, camera->viewMatrix(), "view", true);
	}
	glUseProgram(0);
}

void Renderer::render_forward()
{
	glClearColor(0.15, 0.2, 0.3, 1);
	glPolygonMode(GL_FRONT, GL_LINE);
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
	//render_terrian();
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

	//Shader::setUniform1i(shader_terrain, frame, "frame");
	for (auto &terrain : terrains)
	{
		Mesh& mesh = terrain->mesh;
		//SAHDER & MATRIX
		Shader::setUniformMatrix4f(shader_terrain, terrain->matrix, "model", true);

		glActiveTexture(GL_TEXTURE0);
		GLuint diffuse_id = glGetUniformLocation(shader_terrain, "terrain_diffuse");
		glUniform1i(diffuse_id, 0);

		glBindTexture(GL_TEXTURE_2D, mesh.maps.diffuse->id);
	
		mesh.render();		

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

void Renderer::render_text()
{
	GLuint shader = shaders[SHADER_TEXT];
	glUseProgram(shader);

	Shader::setUniformMatrix4f(shader, projection.text, "proj", true);		
	Shader::setUniform1i(shader, frame, "frame");
	//way to expensive
	for (auto& text : texts) {
		if (!text->enable) continue;

		text->render(shader, std::string("Mode : ").append(mode_string),20,20,1,vec3f(1,1,1));
		text->render(shader, std::string("FPS : ").append(std::to_string(fps)), 20, 40, 1, vec3f(1, 1, 1));
		text->render(shader, std::string("Camera Position : ")
			.append(std::to_string(camera->position().x)).append(", ")
			.append(std::to_string(camera->position().y)).append(", ")
			.append(std::to_string(camera->position().z)),
			20, 60, 1, vec3f(1, 1, 1));

		auto x = std::to_string(camera->player().position().x);
		auto y = std::to_string(camera->player().position().y);
		auto z = std::to_string(camera->player().position().z);
		auto h = std::to_string(height_terrain);
		text->render(shader, std::string("Player Posotion : ")
			.append(x).append(", ")
			.append(y).append(", ").append(z), 20, 80, 1, vec3f(1, 1, 1));
		text->render(shader, std::string("Height Terrain : ").append(h), 20, 100, 1, vec3f(1, 1, 1));
		

	}
	glUseProgram(NULL);
}
