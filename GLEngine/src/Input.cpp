#include "Input.h"

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
		else if (e.type == SDL_KEYDOWN)
		{
			LOG << "key event" << ENDL;
			keyPressEvent(renderer, e);
		}
	}
}

void Input::keyPressEvent(Renderer &renderer, SDL_Event &e)
{
	switch(e.key.keysym.sym)
	{
	case SDLK_1 :
		renderer.mode = MODE_DEFAULT;
		break;

	case SDLK_2:
		renderer.mode = MODE_SECOND;
		break;
	}
}
