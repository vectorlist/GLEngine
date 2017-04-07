#pragma once

#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <vector>

#define LOG			std::cout
#define ENDL		std::endl

#define DIR_DATA	"../data/"
#define DIR_SHADER	"../data/shader/"
#define DIR_TEXTURE	"../data/texture/"

//forwar declare
class Mesh;
class Model;

//TODO : replace unique ptr
typedef std::shared_ptr<Mesh> mesh_ptr;
typedef std::shared_ptr<Model> model_ptr;


//Shaders

enum Shader_Type
{
	SHADER_DEFUALT = 0,
	SHADER_SKY 
};

#define SHADER_MAX_NUM	2
