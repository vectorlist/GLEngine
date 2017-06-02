
#include <config.h>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Application.h>
#include <Initilizer.h>
#include <terrainshader.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

void setConsoleOutput(int x, int y, int w, int h)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	HWND console = GetConsoleWindow();
	MoveWindow(console, x, y, w, h, TRUE);
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
	renderer.resize(app.width, app.height);
	TerrainRenderer terrainRenderer;// (/**renderer.terrainShader*/);
	EnvironmentRenderer environmentRenderer;

	ShadowRenderer shadowRenderer(1280, 720,*renderer.camera.get());

	app.run(renderer, terrainRenderer, environmentRenderer, shadowRenderer);


	/*Matrix4x4 rot;
	rot = vml::lookAt(vec3f(3, 3, 3), vec3f(1,0,0), vec3f(0, 1, 0));

	LOG << rot * vec3f(1) << ENDL;
	LOG << rot.inverted() << ENDL;

	glm::mat4 p = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 pp = glm::transpose(glm::inverse(p));
	LOG << glm::to_string(p * glm::vec4(1)) << ENDL;
	LOG << glm::to_string(pp[0]) << ENDL;
	LOG << glm::to_string(pp[1]) << ENDL;
	LOG << glm::to_string(pp[2]) << ENDL;
	LOG << glm::to_string(pp[3]) << ENDL;
	
	system("pause");*/
	return 0;
}

