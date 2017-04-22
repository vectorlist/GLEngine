
#include <config.h>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Application.h>
#include <Initilizer.h>
#include <terrainshader.h>

void setConsoleOutput(int x, int y, int w, int h)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	HWND console = GetConsoleWindow();
	MoveWindow(console, x, y, w, h, TRUE);
}

struct SomeData
{
	float data=0;
};

void lambda_func(SomeData& aa)
{
	aa.data += 1;
	//LOG << aa.data << LOG;
	if (aa.data > 10) return;
	lambda_func(aa);
	
}

int main(int args, char* argv[])
{
	setConsoleOutput(50, 50, 600, 720);

	Application app("OpenGL Engine",1280,720);
	Renderer renderer;
	

	renderer.setRenderMode(RENDER_FORWARD);
	Initializer::initCamera(renderer);
	Initializer::initScene(renderer);
	Initializer::initTextures(renderer);

	TerrainRenderer terrainRenderer;// (/**renderer.terrainShader*/);
	

	app.run(renderer, terrainRenderer);

	return 0;
}

