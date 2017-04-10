#pragma once
//VML
#define VML_USE_OPENGL
#include <vml.h>
#include <matrix4x4.h>
#include <vec2f.h>
#include <vec3f.h>


#include <GL/glew.h>
#include <Windows.h>
#include <iostream>
#include <memory>
#include <vector>
#include <assert.h>

#define LOG						std::cout
#define ENDL					std::endl

#define DIR_DATA				"../data/"
#define DIR_SHADER				"../data/shader/"
#define DIR_TEXTURE				"../data/texture/"
#define DIR_HEIGHTMAP			"../data/texture/"
#define DIR_MODEL				"../data/model/"

#define FILE_DEFAULT_DIFFUSE	DIR_TEXTURE"desert_diffuse.jpg"

//math
#define NORMALIZE_HEIGHT		1.f/255.f;

//forwar declare
class Mesh;
class Model;
class Geometry;
class Texture;
//TODO : replace unique ptr
typedef std::shared_ptr<Mesh> mesh_ptr;
typedef std::shared_ptr<Model> model_ptr;
typedef std::shared_ptr<Geometry> geometry_ptr;



//log

#define LOG_ERROR(x) logError(x)
#define LOG_SHADER_ERROR(x,xx)
inline void logError(const std::string &msg)
{
	MessageBox(NULL, msg.c_str(), "Error", MB_OK);
	//if got error assert
	assert(0 && msg.c_str());
}

inline void shaderLogError(const std::string &path,const std::string &msg)
{
	std::string err = path;
	err.append(" : ").append(msg);
	MessageBox(NULL, err.c_str(), "Error", MB_OK);
	//if got error assert
	assert(0 && msg.c_str());
}


//TYPE DEFINES
enum Render_Mode
{
	RENDER_FORWARD = 0,
	RENDER_TERRIAN,
	RENDER_FLAT
};

//Shaders
enum Shader_Type
{
	SHADER_FORWARD = 0,
	SHADER_TERRAIN,
	SHADER_FLAT,
	SHADER_MAX_NUM
};

//Texture type
//enum Texture_Type
//{
//	TEXTURE_DIFFUSE = 0,
//	TEXTURE_SPECULAR,
//	TEXTURE_NORMAL
//};