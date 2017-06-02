#pragma once

#include <config.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <Renderer.h>
#include <terrainrenderer.h>
#include <EnvironmentRenderer.h>
#include <shadowrenderer.h>
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
	void contextInfo();
	//main loop
	void run(
		Renderer &renderer, 
		TerrainRenderer &terrainRenderer,
		EnvironmentRenderer &environRenderer,
		ShadowRenderer &shadowRenderer);

	//get frame time
	static TimePoint last_frame_time;
	static Seconds delta;
	static Seconds get_current_time_seconds();

	void swap_update();

	std::string title;
	uint32_t width, height;

	void debug(
		GLuint shader,
		Camera &camera,
		GLuint texture,
		const vec3f &sun,
		const Matrix4x4 shadowProjectionView,
		const Matrix4x4 shadowView,
		std::vector<entity_ptr> &es,
		std::vector<terrain_ptr> &ts,
		float isShadowView);
private:
	SDL_Window* window;
	SDL_GLContext context;

	//test
	float fps;

	void releaseWindow();
};

