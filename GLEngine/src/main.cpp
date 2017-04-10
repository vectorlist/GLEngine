
#include <config.h>
#include <SDL2/SDL.h>
#include <Renderer.h>
#include <Input.h>
#include <Application.h>
#include <Model.h>
#include <Shader.h>
#include <Texture.h>
#include <SDL2/SDL_image.h>
#include <Geometry.h>

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
//---------- ground --------------
const std::vector<float> v2 = {
	50, 0.0, 50,
	-50,0, 50,
	-50,0,-50,
	50,0,-50
};

const std::vector<float> n2 = {
	0, 1, 0.0f,
	0, 1, 0.0f,
	0,  1, 0.f,
	0,  1, 0
};

const std::vector<float> st2 = {
	50.0, 50.0,
	0.0, 50.0,
	0.0, 0.0,
	50.0, 0.0
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
	model_ptr model2 = model_ptr(new Model);

	model2->loadModel(DIR_MODEL"plane.obj");
	model2->meshs[0]->map.normal = Mesh::load(DIR_TEXTURE"ground_normal.jpg", false, TEXTURE_NORMAL);
	renderer.addElement(model2);
	//Model
	/*model_ptr model1 = model_ptr(new Model);
	mesh_ptr mesh1 = mesh_ptr(new Mesh);
	mesh1->vertices = v1;
	mesh1->normals = n1;
	mesh1->st = st1;
	mesh1->indices = i1;
	mesh1->buildBuffer();
	mesh1->map.diffuse = Mesh::load(DIR_TEXTURE"checker.jpg");

	mesh_ptr mesh2 = mesh_ptr(new Mesh);
	mesh2->vertices = v2;
	mesh2->normals = n2;
	mesh2->st = st2;
	mesh2->indices = i2;
	mesh2->buildBuffer();
	mesh2->map.diffuse = Mesh::load(DIR_TEXTURE"ground_normal.jpg", false);
	model1->meshs.push_back(mesh1);
	model1->meshs.push_back(mesh2);
	
	renderer.addElement(model1);*/

	////---------- ASSIMP -------------
	//model_ptr model2 = model_ptr(new Model);
	//model2->loadModel(DIR_MODEL"sphinx.obj");

	//Geometry (Terrain)
	//geometry_ptr geo1 = geometry_ptr(new Geometry());
	//geo1->loadTerrain(DIR_HEIGHTMAP"height_map_ss.jpg",2,10,64);     //scaling size
	////geo1->loadFlatTerrain();
	//renderer.addElement(geo1);
	

	//---------- ASSIMP -------------
	/*model_ptr model2 = model_ptr(new Model);
	
	model2->loadModel(DIR_MODEL"sphinx.obj");*/
	
	//Shader
	renderer.shaders[SHADER_FORWARD] = Shader::load(DIR_SHADER"forward.vert",DIR_SHADER"forward.frag");
	renderer.shaders[SHADER_TERRAIN] = Shader::load(DIR_SHADER"terrain.vert", DIR_SHADER"terrain.frag");
	renderer.shaders[SHADER_FLAT] = Shader::load(DIR_SHADER"flat.vert", DIR_SHADER"flat.frag");

}

void initTextures(Renderer &renderer)
{
	uint32_t mesh_num = 0;
	for (auto m : renderer.models)
	{
		for (auto mesh : m->meshs)
		{
			//LOG << "add diffuse texture to " << mesh_num << " mesh" << ENDL;
			if(mesh->map.diffuse->id == TEXTURE_NONE)
				mesh->map.diffuse = Mesh::global_textures[SHADER_FORWARD];
			mesh_num++;
		}
	}
	
}

int main(int args, char* argv[])
{
	setConsoleOutput(50, 50, 600, 720);

	Application app("OpenGL Engine",1280,720);
	Renderer renderer;

	renderer.setRenderMode(RENDER_FORWARD);
	setRenderSetting(renderer);
	initTextures(renderer);

	app.run(&renderer);

	return 0;
}

