#pragma once

#include <config.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <Renderer.h>

class Application
{
public:
	Application(const std::string &name, int w = 800, int h = 600);
	~Application();

	bool buildWindow();
	//main loop
	void run(Renderer *renderer);

	std::string title;
	uint32_t width, height;

private:
	SDL_Window* window;
	SDL_GLContext context;

	void releaseWindow();
};

