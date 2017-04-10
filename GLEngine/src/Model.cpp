#include "Model.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

Model::Model()
{
}


Model::~Model()
{
}

void Model::loadModel(const std::string & filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_Triangulate | 
		aiProcess_FlipUVs | 
		/*aiProcess_GenNormals | */
		aiProcess_CalcTangentSpace);

	//enable post normals and tagent
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LOG_ERROR("failed to load model");
	}
	
	//get path dir
	dir = filename.substr(0, filename.find_last_of('/'));
	LOG << dir << ENDL;
	extractNode(scene->mRootNode, scene);
}

void Model::extractNode(aiNode * node, const aiScene * scene)
{

	for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* m = scene->mMeshes[node->mMeshes[i]];
		//aiMesh* m = node->mMeshes[i];
		//convert to aimesh to mesh
		mesh_ptr converted = convertMesh(m, scene);

		converted->buildBuffer();

		meshs.push_back(converted);

		int g = 100;
	}

	for (uint32_t i = 0; i < node->mNumChildren; ++i) {
		extractNode(node->mChildren[i], scene);
	}

}

mesh_ptr Model::convertMesh(aiMesh * ai_mesh,const aiScene* scene)
{
	//Mesh* m = new Mesh();
	mesh_ptr m = mesh_ptr(new Mesh);

	m->indice_size = ai_mesh->mNumFaces * 3;
	m->vertices_size = ai_mesh->mNumVertices;

	for (uint32_t i = 0; i < ai_mesh->mNumVertices; ++i)
	{
		/*vec3f v = vec3f(ai_mesh->mVertices[0].x, ai_mesh->mVertices[0].y,
			ai_mesh->mVertices[0].z) * 0.3f;

		m->vertices.push_back(v.x);
		m->vertices.push_back(v.y);
		m->vertices.push_back(v.z);*/
		
		m->vertices.push_back(ai_mesh->mVertices[i].x);
		m->vertices.push_back(ai_mesh->mVertices[i].y);
		m->vertices.push_back(ai_mesh->mVertices[i].z);

		m->normals.push_back(ai_mesh->mNormals[i].x);
		m->normals.push_back(ai_mesh->mNormals[i].y);
		m->normals.push_back(ai_mesh->mNormals[i].z);

		//ST
		if (ai_mesh->HasTextureCoords(0))
		{
			//LOG << "model has texture " << ENDL;
			m->st.push_back(ai_mesh->mTextureCoords[0][i].x);
			m->st.push_back(ai_mesh->mTextureCoords[0][i].y);
		}
		else {
			//LOG << "no coords " << ENDL;
			m->st.push_back(0.0f);
			m->st.push_back(0.0f);
		}
		//TANGENT
		if (ai_mesh->HasTangentsAndBitangents()) {
			//LOG << "has TBN " << ENDL;
			m->tangent.push_back(ai_mesh->mTangents[i].x);
			m->tangent.push_back(ai_mesh->mTangents[i].y);
			m->tangent.push_back(ai_mesh->mTangents[i].z);
		}
		else {
			//LOG << "no tangent " << ENDL;
			m->tangent.push_back(0.0f);
			m->tangent.push_back(0.0f);
			m->tangent.push_back(0.0f);
		}
	}
	//Indices
	for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i) {
		aiFace face = ai_mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; ++j) {
			m->indices.push_back(face.mIndices[j]);
		}
	}

	//Materials
	aiMaterial* mat = scene->mMaterials[ai_mesh->mMaterialIndex];

	/*LOG << "diffuse texture found" << ENDL;*/
	if (mat->GetTextureCount(aiTextureType_DIFFUSE))
	{
		LOG << "diffuse texture found" << ENDL;
		aiString tpath;
		//get texture path
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &tpath);
		m->setTexture(dir + "/" + tpath.C_Str(),false, TEXTURE_DIFFUSE);
	}
	else {
		LOG << "set defualt texture " << ENDL;
		m->setTexture(FILE_DEFAULT_DIFFUSE, false, TEXTURE_DIFFUSE);
		//m->map.diffuse = m->global_textures[];
	}

	//create buffer

	//m->buildBuffer();


	//log
	LOG << "vertice : " <<  m->vertices.size() <<ENDL;
	LOG << "indices : " << m->indices.size() << ENDL;
	LOG << "st : " << m->st.size() << ENDL;
	LOG << "has bit tangents : " << ai_mesh->HasTangentsAndBitangents() << ENDL;

	return m;
}

void Model::loadModel(const std::string &filename, bool usetiny)
{
	/*tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str()))
		LOG_ASSERT(err);

	std::unordered_map<Vertex, int> uniqueVertices = {};

	for (const auto &shape : shapes)
	{
		for (const auto &index : shape.mesh.indices)
		{
			Vertex vertex;
			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.normal = {
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};

			vertex.st = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.color = { 1.0f,1.0f, 0.0f };

			if (uniqueVertices.count(vertex) == 0)
			{
				uniqueVertices[vertex] = vertices.size();
				vertices.push_back(vertex);
			}
			indices.push_back(uniqueVertices[vertex]);
		}
	}
	LOG << "vertices num : " << vertices.size() << ENDL;
	LOG << "indices num : " << indices.size() << ENDL;*/
}