#include "Renderer.h"
#include <Model.h>
#include <shadertool.h>
#include <camera.h>
#include <text.h>
#include <terrain.h>
#include <player.h>
#include <texture.h>
#include <loadmanager.h>

float Renderer::FOV = 70.f;
float Renderer::NEAR_PLANE = 0.1f;
uint32_t Renderer::width = 0;
uint32_t Renderer::height = 0;

Renderer::Renderer()
	: AbstractRenderer()
{

}


Renderer::~Renderer()
{
	for (auto &texture : LoadManager::loadedTextures) {
		glDeleteTextures(1, &texture->id);
	}
	
}

void Renderer::initialize()
{
	glClearColor(0.15, 0.2, 0.25, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	auto text = text_ptr(new Text(FILE_TEXT_SEGOEUI, 16));
	*this << text;
}

void Renderer::render()
{
	//main render
	updateUniforms();

	switch (mode)
	{
	case RENDER_FORWARD:
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderEntities();
		break;
	case RENDER_TERRIAN:
		break;
	case RENDER_FLAT:
		break;
	}
	
	/*render_text();*/
	glBindVertexArray(0);
	glUseProgram(0);
	frame++;
}

void Renderer::resize(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
	aspect_ratio = float(width) / float(height);
	//projection.proj = vml::perspective(45.f, aspect_ratio, 0.001f, 1000.f);
	camera->setProjection(45.0f, aspect_ratio, 0.001f, 1000.f);
	projection.text = vml::ortho(0.f, (float)width, 0.f, (float)height);
	glViewport(0, 0, width, height);
}

void Renderer::initUniforms()
{
	//init attrib to all shader
	//test
	float f = sin(frame * 0.03) * 3.3;
	light.position = vec3f(f, 10, 3);
	light.color = vec3f(0.9 , 0.87, 0.7);
	light.attenuation = vec3f(5, 0, 0);
	vec3f skyColor = vec3f(0.8, 0.85, 0.9);

	/*auto pp = vml::ortho(-10, 10, -10, 10, 1, 10.f);
	auto ppp = pp * vml::lookAt(vec3f(5, 5, 5), vec3f(0), vec3f(0, 1, 0));*/
	//FORWARD
	forwardShader->bind();
	forwardShader->setProjectionMatrix(camera->projectionMatrix());
	forwardShader->setLightColor(light.color);
	forwardShader->setLightpos(light.position);
	forwardShader->setSkyColor(skyColor);
	forwardShader->unbind();
	//TERRAIN
	terrainShader->bind();
	terrainShader->setProjectionMatrix(camera->projectionMatrix());
	terrainShader->setLightColor(light.color);
	terrainShader->setLightpos(light.position);
	terrainShader->setSkyColor(skyColor);
	terrainShader->unbind();
	//ENVIRONMENT
	skyShader->bind();
	skyShader->setProjectionMatrix(camera->projectionMatrix());
	skyShader->setFogColor(skyColor);
	skyShader->unbind();


}

void Renderer::updateUniforms()
{
	forwardShader->bind();
	forwardShader->setViewMatrix(camera->viewMatrix());
	forwardShader->unbind();
	
	terrainShader->bind();
	terrainShader->setViewMatrix(camera->viewMatrix());
	terrainShader->unbind();

	skyShader->bind();
	skyShader->setViewMatrix(camera->viewMatrix());
	skyShader->unbind();
}

void Renderer::renderEntities()
{
	forwardShader->bind();

	for (auto &e : entities)
	{
		const Model& model = e->model;
		//SAHDER & MATRIX
		Matrix4x4 model_matrix;
		model_matrix = vml::transform(e->position(), e->rx(), e->ry(), e->rz(), e->scale());
		forwardShader->setModelMatrix(model_matrix);
		//ATTRIB
		//float f = sin(frame * 0.1);
		//forwardShader->setLightColor(vec3f(f, f, 0));

			//Diffuse
		glActiveTexture(GL_TEXTURE0);
		//GLuint diffuse_id = glGetUniformLocation(forwardShader->id, "diffuse_texture");
		glUniform1i(forwardShader->loc.textureDiffuse, 0);
		glBindTexture(GL_TEXTURE_2D, model.textures.diffuse->id);

		////Normal
		//
		//glActiveTexture(GL_TEXTURE1);
		//GLuint normal_id = glGetUniformLocation(shader_defualt, "normal_map");
		//glUniform1i(normal_id, 1);
		//glBindTexture(GL_TEXTURE_2D, mesh->map.normal->id);

		//VAO
		glBindVertexArray(model.vao());
		glDrawElements(GL_TRIANGLES, model.indices_size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(NULL);
			
		

	}
	for (uint32_t i = 0; i < 4; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
	forwardShader->unbind();
}

void Renderer::renderText()
{
	GLuint shader = shaders[SHADER_TEXT];
	glUseProgram(shader);

	ShaderTool::setUniformMatrix4f(shader, projection.text, "proj", true);		
	ShaderTool::setUniform1i(shader, frame, "frame");
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
		auto h = std::to_string(terrain_height);
		auto id = std::to_string(terrain_id);
		text->render(shader, std::string("Player Posotion : ")
			.append(x).append(", ")
			.append(y).append(", ").append(z), 20, 80, 1, vec3f(1, 1, 1));
		text->render(shader, std::string("Terrain Height : ").append(h), 20, 100, 1, vec3f(1, 1, 1));
		text->render(shader, std::string("Terrain ID : ").append(id), 20, 120, 1, vec3f(1, 1, 1));
		

	}
	glUseProgram(NULL);
}
