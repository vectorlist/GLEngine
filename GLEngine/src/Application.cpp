#include "Application.h"
#include <Input.h>

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
	SDL_Init(SDL_INIT_VIDEO);
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

	glEnable(GL_DEPTH_TEST);

	SDL_GL_SwapWindow(window);				//init swap buffer
											/*if (SDL_GL_SetSwapInterval(0) != 0) {
											printf("WARNING: Unable to disable vsync, %s\n", SDL_GetError());
											LOG_ERROR("damn");
											}*/
	return true;
}

void Application::run(Renderer *renderer)
{
	if (!renderer) return;

	renderer->initialize();					//clear color and setting
	renderer->resize(width, height);			//for viewport
	renderer->init_uniforms();				//update uniform to all shader

	//SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	renderer->isRunninig = true;
	while (renderer->isRunninig)
	{
		Input::event(*renderer, window);	//event hanler
		//Input::mouseEvent(*renderer);
		renderer->render();					//render each
		SDL_GL_SwapWindow(window);			//swap buffer
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
