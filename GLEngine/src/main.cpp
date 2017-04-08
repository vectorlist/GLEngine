
#include <config.h>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Input.h>
#include <Application.h>
#include <Model.h>
#include <Shader.h>
#include <Texture.h>
#include <SDL2/SDL_image.h>

//const std::vector<float> v1 = {
//	-0.5f, -0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	0.0f,  0.5f, 0.0f
//};
//
//const std::vector<float> n1 = {
//	1, 0, 0.0f,
//	0, 1, 0.0f,
//	0,  0, 1.f
//};

const std::vector<float> v1 = {
	0.5, 0.5, 0,
	-0.5,0.5, 0,
	-0.5,-0.5,0,
	0.5,-0.5,0
};

const std::vector<float> n1 = {
	1, 0, 0.0f,
	0, 1, 0.0f,
	0,  0, 1.f,
	1,  1, 0
};

const std::vector<float> st1 = {
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0
};


const std::vector<uint32_t>i1 = 
{
	0,1,2,
	2,3,0
};
//------------------------
const std::vector<float> v2 = {
	5, 0.0, 5,
	-5,0, 5,
	-5,0,-5,
	5,0,-5
};

const std::vector<float> n2 = {
	1, 0, 0.0f,
	0, 1, 0.0f,
	0,  0, 1.f,
	1,  1, 0
};

const std::vector<float> st2 = {
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0
};


const std::vector<uint32_t>i2 =
{
	0,1,2,
	2,3,0
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
	mesh_ptr mesh1 = mesh_ptr(new Mesh);
	mesh1->vertices = v1;
	mesh1->normals = n1;
	mesh1->st = st1;
	mesh1->indices = i1;
	mesh1->buildBuffer();

	mesh_ptr mesh2 = mesh_ptr(new Mesh);
	mesh2->vertices = v2;
	mesh2->normals = n2;
	mesh2->st = st2;
	mesh2->indices = i2;
	mesh2->buildBuffer();

	model1->meshs.push_back(mesh1);
	model1->meshs.push_back(mesh2);
	
	Mesh::load("E:/github/GLEngine/data/texture/checker.jpg");
	
	//renderer.models.push_back(std::move(m1));
	renderer.addElement(model1);
	
	//Shader
	renderer.shaders[SHADER_FORWARD] = Shader::load(DIR_SHADER"forward.vert",DIR_SHADER"forward.frag");
	//TODO : need fix program conversations
	//renderer.shaders[SHADER_FLAT] = Shader::load(DIR_SHADER"flat.vert", DIR_SHADER"flat.frag");
	//renderer.shader[SHADER_FLAT] = Shader::load("", "");
}

void initTextures(Renderer &renderer)
{
	uint32_t mesh_num = 0;
	for (auto m : renderer.models)
	{
		for (auto mesh : m->meshs)
		{
			LOG << "add diffuse texture to " << mesh_num << " mesh" << ENDL;
			mesh->map.diffuse = Mesh::global_textures[SHADER_FORWARD];
			mesh_num++;
		}
	}
}

int main(int args, char* argv[])
{
	setConsoleOutput(50, 50, 600, 720);

	Application app("OpenGL Engine",1024,720);
	Renderer renderer;

	setRenderSetting(renderer);
	initTextures(renderer);

	app.run(&renderer);

	return 0;
}

