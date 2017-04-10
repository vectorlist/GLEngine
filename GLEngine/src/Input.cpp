#include "Input.h"
#include <Model.h>
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
			//LOG << "key event" << ENDL;
			keyPressEvent(renderer, e);
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

	case SDLK_t:
		LOG << "switch texture" << ENDL;
		for (auto m : renderer.models) {
			if (m->texswitch < 3.f)
				m->texswitch += 1.f;
			else
				m->texswitch = -1.f;
			LOG << m->texswitch << ENDL;;
		}
	}
	

}
