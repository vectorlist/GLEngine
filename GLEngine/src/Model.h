#pragma once

#include <config.h>
#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>

struct ModelTexture
{
	Texture* diffuse;
	Texture* specular;
	Texture* normal;
};

class Model
{
public:
	Model();
	Model(const std::string &filepath,
		std::string diffuse = "", std::string specular = "", std::string normal = "");
	~Model();

	Mesh* mesh;
	ModelTexture textures;
	GLuint& vao() const { return mesh->vao; }
	uint32_t& indices_size() const { return mesh->indices_size; }
	void loadModel(const std::string &path);
private:
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

	std::string directory;
};

typedef std::shared_ptr<Model> model_ptr;







