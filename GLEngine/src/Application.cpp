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

void Application::run(Renderer &renderer, TerrainRenderer &terrainRednerer)
{
	

	renderer.initialize();					//clear color and setting
	renderer.resize(width, height);			//for viewport
	renderer.initUniforms();				//update uniform to all shader
	renderer.isRunninig = true;

	Camera& camera = *renderer.camera;
	Player& player = camera.player();

	while (renderer.isRunninig)
	{
	
		Performance::begin(Counter_Type::FPS);
		/*--------------- EVENT --------------------*/
		Input::playerEvent(renderer);
		
		
		/*--------------- MOVEMENT -----------------*/
		player.moveProcess(renderer.terrains);
		camera.moveProcess();
		renderer.terrain_height = player.debug_height;
		renderer.terrain_id = player.debug_terrain_id;
		
		/*-------------- RENDER -------------------*/
		renderer.render();								//render forwar entities
		terrainRednerer.shader = renderer.terrainShader.get();
		terrainRednerer.Render(renderer.terrains);		//render terrtains
		

		renderer.renderText();
		/*------------ RESET SWAPCHAIN ------------*/
		swap_update();						//set global frame time and swap window buffer
		Performance::end(Counter_Type::FPS);
		renderer.fps = Performance::get_fps(Counter_Type::FPS);
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
