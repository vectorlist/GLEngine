#pragma once

#include <Mesh.h>

class Model
{
public:
	Model();
	~Model();

	std::vector<mesh_ptr> meshs;

	void addElement(mesh_ptr mesh);
	
};

inline void Model::addElement(mesh_ptr mesh)
{
	meshs.push_back(mesh);
}




