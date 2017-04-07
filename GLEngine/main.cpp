
#include <GL/glew.h>
#include <SDL2/SDL.h>

bool initSDL(SDL_Window* &window, int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("GLEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		width, height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	if (!window) {
		return false;
	}
	return true;
}


int main(int argc, char* argv[])
{
	SDL_Window* window;

	initSDL(window, 800, 600);
	return 0;
}