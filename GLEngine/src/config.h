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

//forwar declare
class Mesh;
class Model;

//TODO : replace unique ptr
typedef std::shared_ptr<Mesh> mesh_ptr;
typedef std::shared_ptr<Model> model_ptr;


//Shaders

enum Shader_Type
{
	SHADER_FORWARD = 0,
	SHADER_FLAT,
	SHADER_MAX_NUM
};



//log

#define LOG_ERROR(x) logError(x)

inline void logError(const std::string &msg)
{
	MessageBox(NULL, msg.c_str(), "Error", MB_OK);
	//if got error assert
	assert(0 && msg.c_str());
}


//TYPE DEFINES
enum Render_Mode
{
	MODE_FORWARD = 0,
	MODE_FLAT
};