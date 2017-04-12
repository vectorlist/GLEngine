#include "Input.h"
#include <Model.h>
#include <Camera.h>

void Input::event(Renderer & renderer, SDL_Window * window)
{
	//main SDL event
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			renderer.isRunninig = false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			//LOG << "key event" << ENDL;
			keyPressEvent(renderer, e);
		}
		if (e.type = SDL_MOUSEBUTTONDOWN) {
			mousePressEvent(renderer, e);
		}
	}
}

void Input::keyPressEvent(Renderer &renderer, SDL_Event &e)
{
	switch(e.key.keysym.sym)
	{
	case SDLK_1 :
		LOG << "Forward Mode" << ENDL;
		renderer.mode = RENDER_FORWARD;
		break;

	case SDLK_2:
		LOG << "Terrain Mode" << ENDL;
		renderer.mode = RENDER_TERRIAN;
		break;

	case SDLK_3:
		LOG << "Flat Mode" << ENDL;
		renderer.mode = RENDER_FLAT;
		break;

	case SDLK_ESCAPE:
		LOG << "Quit..." << ENDL;
		renderer.isRunninig = false;
		break;

	case SDLK_w:
		renderer.current_camera()->process_keyboard(FORWARD, 3.f);
		break;

	case SDLK_s:
		renderer.current_camera()->process_keyboard(BACKWARD, 3.f);
		break;

	case SDLK_d:
		renderer.current_camera()->process_keyboard(RIGHT, 3.f);
		break;
	case SDLK_a:
		renderer.current_camera()->process_keyboard(LEFT, 3.f);
		break;
	}
}

void Input::mousePressEvent(Renderer &renderer, SDL_Event &e)
{
	int x, y;
	uint32_t mouse = SDL_GetRelativeMouseState(&x, &y);
	if(mouse)
		LOG << e.motion.x << ENDL;
	
}
