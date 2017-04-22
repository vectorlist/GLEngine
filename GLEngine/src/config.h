#pragma once
//VML
#define VML_USE_OPENGL
#include <vml.h>
#include <matrix4x4.h>
#include <vec2f.h>
#include <vec3f.h>

#include <GL/glew.h>
#include <memory>
#include <vector>
#include <log.h>
#include <map>

//DIRS
#define DIR_DATA				"../data/"
#define DIR_SHADER				"../data/shader/"
#define DIR_TEXTURE				"../data/texture/"
#define DIR_TEXTURE_TERRAIN		"../data/texture/terrain/"
#define DIR_HEIGHT				"../data/texture/height/"
#define DIR_MODEL				"../data/model/"
#define DIR_TEXT				"../data/text/"
#define DIR_CUBEMAP				"../data/texture/cubemap/"

//FILES
#define FILE_DEFAULT_DIFFUSE	DIR_TEXTURE"default_diffuse.jpg"
#define FILE_TEXT_CONSOLAS		DIR_TEXT"consola.ttf"
#define FILE_TEXT_SEGOEUI		DIR_TEXT"segoeui.ttf"

//math
#define NORMALIZE_HEIGHT		1.f/255.f;

//forwar declare

class Model;
class Texture;
class PerspectiveCamera;
class Text;
class Terrain;
class Player;
class Camera;
class Entity;
//TODO : replace unique ptr

typedef std::shared_ptr<Model> model_ptr;
typedef std::shared_ptr<Camera> camera_ptr;
typedef std::shared_ptr<Text> text_ptr;
typedef std::shared_ptr<Terrain> terrain_ptr;
typedef std::shared_ptr<Player> player_ptr;
typedef std::shared_ptr<Entity> entity_ptr;
//TYPE DEFINES
enum Render_Mode
{
	RENDER_FORWARD = 0,
	RENDER_TERRIAN,
	RENDER_FLAT
};

inline std::string modeToString(Render_Mode mode)
{
	const std::map<Render_Mode, char*> modes{
		{ RENDER_FORWARD, "forward mode" },
		{ RENDER_TERRIAN, "terrain mode" },
		{ RENDER_FLAT, "flat mode" }
	};
	auto result = modes.find(mode);
	return result == modes.end() ? "no mode" : result->second;
}

//Shaders 4
enum Shader_Type
{
	SHADER_FORWARD = 0,
	SHADER_TERRAIN,
	SHADER_FLAT,
	SHADER_TEXT,
	SHADER_PLAYER,
	SHADER_MAX_NUM
};

