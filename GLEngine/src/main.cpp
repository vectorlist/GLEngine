
#include <config.h>
#include <SDL2/SDL.h>
#include <Windows.h>
#include <Renderer.h>
#include <Input.h>
#include <Application.h>
#include <Model.h>
#include <Shader.h>

//const std::vector<float> v1 = {
//	-0.5,-0.5,
//	0.5,-0.5,
//	0.5,0.5
//};

const std::vector<float> v1 = {
	-1.f,-1.f,
	1.f,-1.0f,
	0.0,1.f
};


void setConsoleOutput(int x, int y, int w, int h)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	HWND console = GetConsoleWindow();
	MoveWindow(console, x, y, w, h, TRUE);
}

void setRenderSetting(Renderer &renderer)
{
	//Model
	model_ptr model1 = model_ptr(new Model);
	mesh_ptr mesh1 = mesh_ptr(new Mesh(v1));
	model1->addElement(mesh1);
	//renderer.models.push_back(std::move(m1));
	renderer.addElement(model1);

	//Shader
	renderer.shader[SHADER_DEFUALT] = Shader::load(DIR_SHADER"main.vert",DIR_SHADER"main.frag");
	//renderer.shader[SHADER_SKY] = Shader::load("", "");
}

int main(int args, char* argv[])
{
	setConsoleOutput(50, 50, 700, 800);

	Application app("OpenGL Engine");
	Renderer renderer;

	setRenderSetting(renderer);

	app.run(&renderer);

	return 0;
}