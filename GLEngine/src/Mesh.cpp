#include <Mesh.h>

//it must be Shader_Type Index
std::vector<Texture*> Mesh::global_textures;

Mesh::Mesh(std::vector<Vertex> vertice, std::vector<uint32_t> indices)
{
	this->vertices = vertice;
	this->indices = indices;
	build_buffers();
}

Mesh::~Mesh()
{
	/*glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);*/
}

void Mesh::build_buffers()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ibo);

	glBindVertexArray(this->vao);

	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::st));
	// Vertex Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::tangent));
	// Vertex Bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Vertex::bitangent));

	glBindVertexArray(0);
}


void Mesh::setTexture(const std::string & filename, bool clamp, Texture_Type type)
{
	//initialize when local
	Texture* texture = NULL;
	bool found = false;
	for (int i = 0; i < global_textures.size(); ++i)
	{
		//if path is not in already loaded textures
		if (!filename.compare(Mesh::global_textures[i]->path))
		{
			texture = Mesh::global_textures[i];
			found = true;
		}
	}
	//path is not in global texture
	if (!found) {
		texture = Mesh::loadTexture(filename, clamp, type);
	}
	
	//set texture to this mesh
	switch (type)
	{
	case TEXTURE_DIFFUSE:
		maps.diffuse = texture;
		break;
	case TEXTURE_SPECULAR:
		maps.specular = texture;
		break;
	case TEXTURE_NORMAL:
		maps.normal = texture;
		break;
	}
}

Texture* Mesh::loadTexture(const std::string & filename, bool clamp, Texture_Type type)
{
	SDL_Surface* image = IMG_Load(filename.c_str());
	SDL_Texture* t = IMG_LoadTexture(NULL, filename.c_str());
	if (image == NULL) {
		std::string err = "failed to load image : ";
		err.append(filename);
		LOG_ERROR(err);
	}
	Texture* texture = new Texture();
	texture->type = type;
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
	SDL_DestroyTexture(t);

	global_textures.push_back(texture);
	return texture;
}

void Mesh::render()
{
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
