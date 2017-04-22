#pragma once

#include <texture.h>
#include <Model.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define LOAD_TEXTURE(x) LoadManager::loadTexture(x)
#define LOAD_TEXTURE_CLAMP(x) LoadManager::loadTexture(x,true)
#define LOAF_CUBE_MAP(x) LoadManager::loadCubeMap(x)

class LoadManager
{
public:
	~LoadManager();

	static Texture* loadTexture(const std::string &path, bool clamp = false,
		Texture_Type type = TEXTURE_DIFFUSE);

	//test 
	static Texture* loadCubeMap(std::vector<std::string> faces);


	static std::vector<texture_ptr> loadedTextures;

	/*static Mesh* loadModel(const std::string &path);
private:
	static void processNode(aiNode* node, const aiScene* scene, Mesh *mesh);
	static Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::string driectory;

	static std::vector<model_ptr> loadedModels;
	static std::vector<mesh_ptr> loadedMeshes;*/
};