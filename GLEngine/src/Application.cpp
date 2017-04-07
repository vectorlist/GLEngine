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
	//
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	
	if (!window)
	{
		LOG << "failed to create window" << ENDL;
		return false;
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	context = SDL_GL_CreateContext(window);
	
	//glew for application
	glewExperimental = GL_TRUE;
	glewInit();
	
	return true;
}

void Application::run(Renderer *renderer)
{
	if (!renderer) return;
	
	renderer->initialize();					//clear color and setting
	renderer->resize(width, height);			//for viewport

	SDL_GL_SwapWindow(window);				//init swap buffer

	renderer->isRunninig = true;
	while (renderer->isRunninig)
	{
		Input::event(*renderer, window);	//event hanler
		renderer->render();					//render each
		SDL_GL_SwapWindow(window);			//swap buffer
	}
}

void Application::releaseWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
