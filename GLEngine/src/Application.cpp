#include "Application.h"
#include <Input.h>
#include <Performance.h>
#include <Camera.h>
#include <player.h>
#include <loadmanager.h>

TimePoint Application::last_frame_time;
Seconds Application::delta;

Application::Application(const std::string & name, int w, int h)
	: title(name), width(w), height(h)
{
	buildWindow();
}

Application::~Application()
{
	if (window) {
		releaseWindow();
	}
}

bool Application::buildWindow()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);

	if (!window)
	{
		LOG_ERROR("failed to create window");
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	context = SDL_GL_CreateContext(window);

	//glew for application
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		LOG_ERROR("failed to init glew");
		return false;
	}
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_GL_SwapWindow(window);

	last_frame_time = Clock::now();
	contextInfo();
	return true;
}

void Application::contextInfo()
{
	GLint  frag_block;
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &frag_block);
	auto device = glGetString(GL_RENDERER);
	auto glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint max_buffer_size;
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max_buffer_size);

	max_buffer_size = max_buffer_size * sizeof(float);
	LOG << "Video Device	           : " << device << ENDL;
	LOG << "GLSL Version               : " << glsl << ENDL;
	LOG << "Max Fragment Uniform Block : " << frag_block << ENDL;
	LOG << "Max Vertex buffer size     : " << max_buffer_size << ENDL;
}

void Application::run(
	Renderer &renderer,
	TerrainRenderer &terrainRednerer,
	EnvironmentRenderer &environRenderer,
	ShadowRenderer &shadowRenderer)
{
	

	renderer.initialize();					//clear color and setting
	renderer.resize(width, height);			//for viewport
	renderer.initUniforms();				//update uniform to all shader
	renderer.isRunninig = true;

	Camera& camera = *renderer.camera;
	Player& player = camera.player();


	//test shadow 
	auto debugShader = LOAD_SHADER(DIR_SHADER"debug.vert", DIR_SHADER"debug.frag");
	//ShadowRenderer shadowRenderer(camera);

	uint32_t frame = 0;
	while (renderer.isRunninig)
	{
		//im not sure it need
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Performance::begin(Counter_Type::FPS);
		/*--------------- EVENT --------------------*/
		Input::playerEvent(renderer);

		/*--------------- MOVEMENT -----------------*/
		player.moveProcess(renderer.terrains);
		camera.moveProcess();
		renderer.terrain_height = player.debug_height;
		renderer.terrain_id = player.debug_terrain_id;
		renderer.updateUniforms();
		/*---------------- TEST -----------------*/
		vec3f sun(10, 10, 8);

		shadowRenderer.render(renderer.entities, sun, player.position());
		//re buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		debug(debugShader, camera, shadowRenderer.getShadowMap(), sun,
			shadowRenderer.getShadowMatrix(),
			shadowRenderer.getShadowRelativeMatrix(),
			renderer.entities, renderer.terrains,
			renderer.isShadowView);
//#define _RENDER		
		/*-------------- RENDER -------------------*/
#ifdef _RENDER
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.render();								//render forwar entities
		terrainRednerer.shader = renderer.terrainShader.get();
		terrainRednerer.Render(renderer.terrains);		//render terrtains
		
		environRenderer.shader = renderer.skyShader.get();
		environRenderer.render(camera);					//render environment

		
#endif //_RENDER

		renderer.renderText();
		/*------------ RESET SWAPCHAIN ------------*/
		swap_update();						//set global frame time and swap window buffer
		Performance::end(Counter_Type::FPS);
		renderer.fps = Performance::get_fps(Counter_Type::FPS);
		frame++;
	}
	releaseWindow();
}


void Application::releaseWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Seconds Application::get_current_time_seconds()
{ 
	return delta; 
}

void Application::swap_update()
{
	SDL_GL_SwapWindow(window);			//swap buffer
	auto current_frame = Clock::now();
	delta = current_frame - last_frame_time;
	last_frame_time = current_frame;
}

void Application::debug(
	GLuint shader,
	Camera &camera,
	GLuint texture,
	const vec3f &sun,
	const Matrix4x4 shadowProjectionView,
	const Matrix4x4 shadowRelativeView,
	std::vector<entity_ptr> &es,
	std::vector<terrain_ptr> &ts,
	float isShadowView)
{
	glUseProgram(shader);
	ShaderTool::setUniformMatrix4f(shader, camera.projectionMatrix(), "proj", true);
	ShaderTool::setUniformMatrix4f(shader, camera.viewMatrix(), "view", true);
	ShaderTool::setUniformMatrix4f(shader, shadowProjectionView, "shadowSpace", true);
	ShaderTool::setUniformMatrix4f(shader, shadowRelativeView, "shadowRelativeView", true);
	ShaderTool::setUniForm3f(shader, sun, "sun");
	ShaderTool::setUniform1i(shader, 0, "shadowMap");
	ShaderTool::setUniform1f(shader, isShadowView, "isShadowView");
	ShaderTool::setUniform1f(shader, ShadowBBox::SHADOW_DISTANCE, "shadow_distance");

	//texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	for (auto &e : es)
	{
		const Model& model = e->model;
		//SAHDER & MATRIX
		Matrix4x4 model_matrix;
		model_matrix = vml::transform(e->position(), e->rx(), e->ry(), e->rz(), e->scale());
		ShaderTool::setUniformMatrix4f(shader, model_matrix, "model", true);
		//VAO
		glBindVertexArray(model.vao());
		glDrawElements(GL_TRIANGLES, model.indices_size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(NULL);
	}

	for (auto &t : ts)
	{
		const Mesh& mesh = *t->mesh;
		
		//SAHDER & MATRIX
		ShaderTool::setUniformMatrix4f(shader, t->matrix, "model", true);
		//VAO
		glBindVertexArray(mesh.vao);
		glDrawElements(GL_TRIANGLES, mesh.indices_size, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(NULL);
	}
	glUseProgram(0);

}

