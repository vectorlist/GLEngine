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
	Model(const std::string &filename);
	~Model() {};

	std::vector<Mesh> meshes;

	void loadModel(const std::string &path);
private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::string directory;
};







