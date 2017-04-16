
#include <config.h>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Application.h>
#include <Initilizer.h>

void setConsoleOutput(int x, int y, int w, int h)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	HWND console = GetConsoleWindow();
	MoveWindow(console, x, y, w, h, TRUE);
}

//test
#include <main.h>
#include <Camera.h>

int main(int args, char* argv[])
{
	setConsoleOutput(50, 50, 600, 720);

	Application app("OpenGL Engine",1280,720);
	Renderer renderer;

	Model model(DIR_MODEL"boxman/boxman.obj", DIR_MODEL"boxman/boxman.jpg");
	Player p(model,vec3f(0,100,0),0,0,0,1.f);
	PlayerCamera camera(p);

	renderer.setRenderMode(RENDER_FORWARD);
	Initializer::initCamera(renderer, camera);
	Initializer::initScene(renderer);
	Initializer::initTextures(renderer);

	app.run(&renderer);
	
	return 0;
}

