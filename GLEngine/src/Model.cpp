#include <Model.h>
#include <loadmanager.h>

Model::Model()
{

}

Model::Model(const std::string & filename,
	std::string diffuse, std::string specular, std::string normal)
	: mesh(NULL)
{
	loadModel(filename);

	if (!diffuse.empty())
		textures.diffuse = LOAD_TEXTURE(diffuse);
	else
		textures.diffuse = LOAD_TEXTURE(FILE_DEFAULT_DIFFUSE);

	if (!specular.empty())
		textures.specular = LOAD_TEXTURE(specular);
	else
		textures.specular = NULL;

	if (!normal.empty())
		textures.normal = LOAD_TEXTURE(diffuse);
	else
		textures.normal = NULL;
}

Model::~Model()
{
	delete mesh;
}



void Model::loadModel(const std::string &path)
{
	LOG << "loading model... : " << path << ENDL;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_Triangulate | aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		LOG_ERROR(importer.GetErrorString());
	}
	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}


void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		//this->meshes.push_back(processMesh(mesh, scene));
		mesh = processMesh(aimesh, scene);
	}	
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}

}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vec3f vector; 
		// Pos
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.pos = vector;
		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;
		// Texture Coordinates
		if (mesh->mTextureCoords[0]) 
		{
			vec2f vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.st = vec;
		}
		else
			vertex.st = vec2f(0.0f, 0.0f);
		// Tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.tangent = vector;
		// Bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.bitangent = vector;
		vertices.push_back(vertex);
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		LOG << "has texture " << ENDL;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
	}

	return new Mesh(vertices, indices);
}