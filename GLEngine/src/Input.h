#pragma once

#include <config.h>
#include <Renderer.h>
#include <SDL2/SDL.h>
#include <Camera.h>

namespace Input
{
	void event(Renderer &renderer);
	//Player PerspectiveCamera Event
	void playerEvent(Renderer &renderer);

	void keyPressEvent(Renderer &renderer, SDL_Event &e);
	void mousePressEvent(Renderer &renderer, SDL_Event &e);
	void mouseMoveEvent(Renderer &renderer, SDL_Event &e);
	void mouseReleaseEvent(Renderer &renderer, SDL_Event &e);

	
	extern bool mouse_motion;
	extern bool mouse_first_click;
}