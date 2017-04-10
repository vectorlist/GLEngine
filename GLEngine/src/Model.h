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
	~Model();

	std::vector<mesh_ptr> meshs;

	void addElement(mesh_ptr mesh);
	
	//Assimp
	void loadModel(const std::string &filename);
	//test without tangent
	void loadModel(const std::string &filename, bool usetiny);
	void extractNode(aiNode* node, const aiScene* scene);

	std::string dir;

	mesh_ptr convertMesh(aiMesh* aMesh,const aiScene* scene);
	float texswitch = -1.0f;
};

inline void Model::addElement(mesh_ptr mesh)
{
	meshs.push_back(mesh);
}






