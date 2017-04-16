#include "Application.h"
#include <Input.h>
#include <Performance.h>
#include <Camera.h>
#include <player.h>

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
	//IMG_Init(IMG_INIT_PNG);
	//IMG_Init(IMG_INIT_JPG);
	//
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);

	if (!window)
	{
		LOG_ERROR("failed to create window");
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	context = SDL_GL_CreateContext(window);

	//glew for application
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		LOG_ERROR("failed to init glew");
		return false;
	}
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_GL_SwapWindow(window);				//init swap buffer
											/*if (SDL_GL_SetSwapInterval(0) != 0) {
											printf("WARNING: Unable to disable vsync, %s\n", SDL_GetError());
											LOG_ERROR("damn");
											}*/
	last_frame_time = Clock::now();
	return true;
}

void Application::run(Renderer *renderer)
{
	if (!renderer) return;

	renderer->initialize();					//clear color and setting
	renderer->resize(width, height);			//for viewport
	renderer->init_view_matrix();				//update uniform to all shader

	renderer->isRunninig = true;
	//auto current_time = Clock::now();
	PlayerCamera* camera = renderer->camera;
	Player* player = &renderer->camera->player;
	while (renderer->isRunninig)
	{
	
		//Performance::begin(Counter_Type::FPS);
		//Input::event(*renderer);	//event hanler
		Input::playerEvent(*renderer);
		
		player->moving(*renderer->terrains[0].get());
		camera->move();
		
		renderer->render();					//render each
		player->render(renderer);
		
		swap_update();						//set global frame time and swap window buffer
	
		//renderer->fps = Performance::get_fps(Counter_Type::FPS);
	}
	releaseWindow();
}


void Application::releaseWindow()
{
	//IMG_Quit();
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
