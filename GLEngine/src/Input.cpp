#include "Input.h"
#include <Model.h>
#include <camera.h>

namespace Input 
{
	bool mouse_motion = false;
	bool mouse_first_click = false;

	void event(Renderer & renderer)
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
				keyPressEvent(renderer, e);
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				mousePressEvent(renderer, e);
			}
			else if (e.type == SDL_MOUSEMOTION) {
				mouseMoveEvent(renderer, e);
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				mouseReleaseEvent(renderer, e);
			}
		}
	}

	void playerEvent(Renderer & renderer)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				renderer.isRunninig = false;
				break;
			case SDL_MOUSEMOTION:
				renderer.camera->mouseMoveEvent(e.motion.xrel, e.motion.yrel);	//relative mouse
				break;
			case SDL_MOUSEWHEEL:
				renderer.camera->mouseWheelEvent(e.wheel.y);
				break;
			case SDL_KEYDOWN:
				keyPressEvent(renderer, e);
				break;
			/*case SDL_MOUSEBUTTONDOWN:
				mousePressEvent(renderer, e);
				break;
			case SDL_MOUSEBUTTONUP: 
				mouseReleaseEvent(renderer, e);
				break;*/
				
			default:
				break;
			}
			
		}
	}

	void keyPressEvent(Renderer &renderer, SDL_Event &e)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_1:
			//LOG << "Forward Mode" << ENDL;
			renderer.setRenderMode(RENDER_FORWARD);
			break;

		case SDLK_2:
			//LOG << "Terrain Mode" << ENDL;
			renderer.setRenderMode(RENDER_TERRIAN);
			break;

		case SDLK_3:
			//LOG << "Flat Mode" << ENDL;
			renderer.setRenderMode(RENDER_FLAT);
			break;

		case SDLK_ESCAPE:
			LOG << "Quit..." << ENDL;
			renderer.isRunninig = false;
			break;
		case SDLK_F5:
			//renderer << model_ptr(new Model(DIR_MODEL"box.obj"));
			renderer.rebuildShaders();
			break;

		case SDLK_5:
			//renderer << model_ptr(new Model(DIR_MODEL"box.obj"));
			if (renderer.isShadowView == 0.0f) {
				renderer.isShadowView = 1.0f;
			}
			else
				renderer.isShadowView = 0.0f;
			break;
		/*case SDLK_w:
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
			break;*/
		}
	}

	void mousePressEvent(Renderer &renderer, SDL_Event &e)
	{
		mouse_motion = true;
		mouse_first_click = true;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	void mouseMoveEvent(Renderer &renderer, SDL_Event &e)
	{
		if (mouse_motion) {
			int x, y;
			SDL_GetRelativeMouseState(&x, &y);
			if (mouse_first_click) {
				mouse_first_click = false;
				return;
			}
			//renderer.camera.perspective->process_mouse_movement(x, -y);
		}
			
	}

	void mouseReleaseEvent(Renderer &renderer, SDL_Event &e)
	{
		
		mouse_motion = false;
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	
}

