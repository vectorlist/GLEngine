#include <Mesh.h>

//it must be Shader_Type Index
std::vector<Texture*> Mesh::global_textures;

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	releaseBuffer();
}

void Mesh::buildBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(4, vbos);
	//vertex
	glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_VERTEX]);					//index 0 for vertex
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() * 3) * sizeof(float),
		vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_NORAML]);					//index 1 for normal
	glBufferData(GL_ARRAY_BUFFER, (normals.size() * 3) * sizeof(float),
		normals.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);

	//st
	glBindBuffer(GL_ARRAY_BUFFER, vbos[VBO_ST]);					//index 1 for texture coords
	glBufferData(GL_ARRAY_BUFFER, (st.size() * 2) * sizeof(float),
		st.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);

	//indices
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]),
		indices.data(), GL_STATIC_DRAW);


	//finish vao bounding
	glBindVertexArray(0);

	//add vbo

}

void Mesh::releaseBuffer()
{
	glDeleteVertexArrays(1, &vao);
	/*if (vbos.size() == 0) return;
	glDeleteBuffers(vbos.size(), vbos.data());*/
	glDeleteBuffers(VBO_NUM, vbos);
	glDeleteBuffers(1, &ibo);
}


Texture* Mesh::load(const std::string & filename, bool clamp)
{
	SDL_Surface* image = IMG_Load(filename.c_str());
	SDL_Texture* t = IMG_LoadTexture(NULL, filename.c_str());
	if (image == NULL) {
		std::string err = "failed to load image : ";
		err.append(filename);
		LOG_ERROR(err);
	}

	LOG << "loaded texture" << ENDL;
	Texture* texture = new Texture();
	texture->type = DIFFUSE;
	texture->path = filename;

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
		LOG << "RGBA" << ENDL;
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
		LOG << "RGB : " << image->format->Rmask << ENDL;
		GLenum format = (image->format->Rmask == 255) ? GL_RGB : GL_BGR;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0,
			format,
			GL_UNSIGNED_BYTE,
			(GLvoid*)image->pixels);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);

	global_textures.push_back(texture);
	return texture;
}
