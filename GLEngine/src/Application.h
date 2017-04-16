#pragma once

#include <config.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <Renderer.h>
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point TimePoint;
typedef std::chrono::duration<float, std::chrono::seconds::period> Seconds;
typedef std::chrono::high_resolution_clock Clock;

#define APP_CURRENT_TIME Application::delta.count()

class Application
{
public:
	Application(const std::string &name, int w = 800, int h = 600);
	~Application();

	bool buildWindow();
	//main loop
	void run(Renderer *renderer);

	//get frame time
	static TimePoint last_frame_time;
	static Seconds delta;
	static Seconds get_current_time_seconds();

	void swap_update();

	std::string title;
	uint32_t width, height;

private:
	SDL_Window* window;
	SDL_GLContext context;

	//test
	float fps;

	void releaseWindow();
};

