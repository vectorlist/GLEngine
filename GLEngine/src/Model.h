#pragma once

#include <config.h>
#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model();
	Model(const std::string &filename, std::string texture = "");
	~Model() {};

	std::vector<Mesh> meshes;
	std::string diffuse_texture_path;
	void loadModel(const std::string &path);
private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::string directory;
};







