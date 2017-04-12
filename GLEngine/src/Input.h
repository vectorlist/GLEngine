#pragma once

#include <config.h>
#include <Renderer.h>
#include <SDL2/SDL.h>

namespace Input
{
	void event(Renderer &renderer, SDL_Window* window);
	void keyPressEvent(Renderer &renderer, SDL_Event &e);
	void mousePressEvent(Renderer &renderer, SDL_Event &e);
}