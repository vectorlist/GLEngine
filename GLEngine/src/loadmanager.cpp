#include <loadmanager.h>
#include <SDL2/SDL_image.h>
#include <log.h>

std::vector<texture_ptr> LoadManager::loadedTextures;
//std::vector<model_ptr> LoadManager::loadedModels;
//std::vector<mesh_ptr> LoadManager::loadedMeshes;

LoadManager::~LoadManager()
{

}

Texture* LoadManager::loadTexture(const std::string &path, bool clamp, Texture_Type type)
{
	for (int i = 0; i < loadedTextures.size(); ++i)
	{
		//0 is equal
		if (!path.compare(loadedTextures[i]->path))
		{
			return loadedTextures[i].get();
		}
	}
	SDL_Surface* image = IMG_Load(path.c_str());

	if (image == NULL) {
		std::string err = "failed to load image : ";
		err.append(path);
		LOG_ERROR(err);
	}
	auto texture = texture_ptr(new Texture);
	texture->type = type;
	texture->path = path;

	glGenTextures(1, &texture->id);				//id itself
	glBindTexture(GL_TEXTURE_2D, texture->id);

	if (clamp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (image->format->BytesPerPixel == 4)
	{
		GLenum format = (image->format->Rmask == 255) ? GL_RGBA : GL_BGRA;

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			image->w, image->h,
			0,
			format,
			GL_UNSIGNED_BYTE,
			(GLvoid*)image->pixels);
	}
	else {
		GLenum format = (image->format->Rmask == 255) ? GL_RGB : GL_BGR;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0,
			format,
			GL_UNSIGNED_BYTE,
			(GLvoid*)image->pixels);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);

	loadedTextures.push_back(texture);
	return texture.get();
}

Texture* LoadManager::loadCubeMap(std::vector<std::string> faces)
{
	texture_ptr texture;
	glGenTextures(1, &texture->id);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id);

	for (int i = 0; i < faces.size(); ++i)
	{
		SDL_Surface* image = IMG_Load(faces[i].c_str());

		if (image == NULL) {
			std::string err = "failed to load image : ";
			err.append(faces[i].c_str());
			LOG_ERROR(err);
		}
		texture->path.append(faces[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			image->w,
			image->h,
			0,
			GL_RGBA, GL_UNSIGNED_INT, image->pixels);
		SDL_FreeSurface(image);
	}

	glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	LoadManager::loadedTextures.push_back(texture);
	return texture.get();
}


//
//Mesh* LoadManager::loadModel(const std::string &path)
//{
//	LOG << "loading model... : " << path << ENDL;
//	Assimp::Importer importer;
//	const aiScene* scene = importer.ReadFile(path,
//		aiProcess_Triangulate | aiProcess_FlipUVs |
//		aiProcess_CalcTangentSpace);
//
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
//	{
//		LOG_ERROR(importer.GetErrorString());
//	}
//	//this->directory = path.substr(0, path.find_last_of('/'));
//	Mesh* mesh;
//	LoadManager::processNode(scene->mRootNode, scene, mesh);
//	return mesh;
//}
//
//
//void LoadManager::processNode(aiNode* node, const aiScene* scene, Mesh *mesh)
//{
//	for (GLuint i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
//
//		mesh = processMesh(aimesh, scene);
//		loadedMeshes.push_back(mesh_ptr(mesh));
//		
//	}
//	/*for (GLuint i = 0; i < node->mNumChildren; i++)
//	{
//		LoadManager::processNode(node->mChildren[i], scene);
//	}*/
//
//}
//
//Mesh* LoadManager::processMesh(aiMesh* mesh, const aiScene* scene)
//{
//	std::vector<Vertex> vertices;
//	std::vector<uint32_t> indices;
//
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		Vertex vertex;
//		vec3f vector;
//		// Pos
//		vector.x = mesh->mVertices[i].x;
//		vector.y = mesh->mVertices[i].y;
//		vector.z = mesh->mVertices[i].z;
//		vertex.pos = vector;
//		// Normals
//		vector.x = mesh->mNormals[i].x;
//		vector.y = mesh->mNormals[i].y;
//		vector.z = mesh->mNormals[i].z;
//		vertex.normal = vector;
//		// Texture Coordinates
//		if (mesh->mTextureCoords[0])
//		{
//			vec2f vec;
//			vec.x = mesh->mTextureCoords[0][i].x;
//			vec.y = mesh->mTextureCoords[0][i].y;
//			vertex.st = vec;
//		}
//		else
//			vertex.st = vec2f(0.0f, 0.0f);
//		// Tangent
//		vector.x = mesh->mTangents[i].x;
//		vector.y = mesh->mTangents[i].y;
//		vector.z = mesh->mTangents[i].z;
//		vertex.tangent = vector;
//		// Bitangent
//		vector.x = mesh->mBitangents[i].x;
//		vector.y = mesh->mBitangents[i].y;
//		vector.z = mesh->mBitangents[i].z;
//		vertex.bitangent = vector;
//		vertices.push_back(vertex);
//	}
//	for (GLuint i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//		for (GLuint j = 0; j < face.mNumIndices; j++)
//			indices.push_back(face.mIndices[j]);
//	}
//	// Process materials
//	if (mesh->mMaterialIndex >= 0)
//	{
//		LOG << "has texture " << ENDL;
//		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//
//	}
//	return new Mesh(vertices, indices);
//}