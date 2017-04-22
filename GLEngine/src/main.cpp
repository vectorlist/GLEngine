
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

class SomeData
{
public:
	SomeData(const char* d) : data(d){}
	bool operator==(char* otherData)
	{
		return (this->data == otherData);
	}

	//this friend dose not meaning just for declare u can use it without this
	//but u need it if we can find this func in cpp or somewhere
	//it can't be const func it's already const func
	friend bool operator==(const char* firstinput,const SomeData &secondinput)
	{
		return (firstinput == secondinput.data);
	}
	
	const char* data;
};


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
	EnvironmentRenderer environmentRenderer;

	app.run(renderer, terrainRenderer, environmentRenderer);
	
	
	/*for(int i =0; i < 10; ++i)
		LOG << selectiveBuRandom() << ENDL;;


	system("pause");*/

	return 0;
}

