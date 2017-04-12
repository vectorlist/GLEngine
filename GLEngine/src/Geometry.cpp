#include "Geometry.h"
#include <SDL2/SDL_image.h>

#include <Texture.h>
Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

void Geometry::loadTerrain(const std::string & filename,
	float planeScale, float heightScale, unsigned int scalesize, float mapping_scale)
{
	SDL_Surface* map = IMG_Load(filename.c_str());
	if (!map) {
		std::string err = "failed to load height map : ";
		err.append(filename);
		LOG_ERROR(err);
	}

	scale_size = scalesize;
	total_x = map->w;
	total_z = map->h;

	for (int z_total = 0; z_total < map->h; z_total += scale_size) {
		for (int x_total = 0; x_total < map->w; x_total += scale_size) {
			//Mesh* m = new Mesh;
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;
			for (int z = z_total; z < z_total + scale_size + 1; z++) {
				for (int x = x_total; x < x_total + scale_size + 1; x++) {
					// uint8 / 255
					float y = getHeightPixel(x, z, map) * NORMALIZE_HEIGHT;

					Vertex vertex;
					vec3f vector;
					//pos
					vector.x = x;
					vector.y = y;
					vector.z = z;
					vertex.pos = vector;

					vec3f normal = getNormal(x, z, map, planeScale, heightScale);
					vertex.normal = normal;

					vertex.st = vec2f(x * mapping_scale, z * mapping_scale);
					vertex.tangent = vec3f(0.f);
					vertex.bitangent = vec3f(0.0f);

					vertices.push_back(vertex);
				}
			}

			for (int z = 0; z < scale_size - 1 + 1; ++z)
			{
				for (int x = 0; x < scale_size - 1 + 1; ++x)
				{
					int i[6];								//quad indices
															//tri1
					i[0] = x + z			 *	(scale_size + 1);
					i[1] = (x + 1) + (z + 1) *	(scale_size + 1);
					i[2] = (x + 1) + z *		(scale_size + 1);

					//tri 2
					i[3] = x + z *				(scale_size + 1);
					i[4] = x + (z + 1) *		(scale_size + 1);
					i[5] = (x + 1) + (z + 1) *	(scale_size + 1);

					indices.push_back(i[0]);
					indices.push_back(i[1]);
					indices.push_back(i[2]);

					indices.push_back(i[3]);
					indices.push_back(i[4]);
					indices.push_back(i[5]);
				}
			}
			//m->map.diffuse = Mesh::load(DIR_TEXTURE"terrain_test.jpg",false);
			
			//m->buildBuffer();
			meshes.push_back(Mesh(vertices, indices));
		}
	}

	//setting all matrix and translate widh scale and height
	//move to center
	float center_x = (map->w * planeScale / 2);
	float center_z = (map->h * planeScale / 2); 
	matrix_trans.translate(vec3f(-center_x, 0, -center_z));
	matrix_scale.scale(vec3f(planeScale, heightScale, planeScale));					
	matrix = matrix_trans * matrix_scale;
}


void Geometry::buildScaledMesh(int geoZ, int geoX, int perScale, Mesh * mesh, SDL_Surface * map)
{
	//int sumZ = geoZ + perScale + 1;
	//int sumX = geoX + perScale + 1;

	////Build Vertex Propertis
	//if (overScale) {
	//	sumZ = z_size;
	//	sumX = x_size;
	//}
	//for (int z = geoZ; z < sumZ; z++) {
	//	for (int x = geoX; x < sumX; x++){
	//		float y = getHeightPixel(x, z, map) * NORMALIZE_HEIGHT;
	//		LOG << z << ENDL;
	//		//Vertex
	//		mesh->vertices.push_back(x);
	//		mesh->vertices.push_back(y);
	//		mesh->vertices.push_back(z);

	//		//Normal
	//		vec3f normal = getNormal(x, z, map, geo_scale, 1.f);
	//		mesh->normals.push_back(normal.x);
	//		mesh->normals.push_back(normal.y);
	//		mesh->normals.push_back(normal.z);
	//		//LOG << "height : " << p << ENDL;

	//		//ST
	//		mesh->st.push_back(x);
	//		mesh->st.push_back(z);

	//		//TANGENT  later
	//	}
	//}
	//int scale = perScale;
	//if (overScale)
	//{
	//	scale = geoZ;
	//}

	////Build Indices
	//for (int z = 0; z < scale - 1 + 1; ++z)
	//{
	//	for (int x = 0; x < scale - 1 + 1; ++x)
	//	{
	//		int i[6];								//quad indices
	//												//tri1
	//		i[0] = x + z			 *	(scale + 1);
	//		i[1] = (x + 1) + (z + 1) *	(scale + 1);
	//		i[2] = (x + 1) + z *		(scale + 1);

	//		//tri 2
	//		i[3] = x + z *				(scale + 1);
	//		i[4] = x + (z + 1) *		(scale + 1);
	//		i[5] = (x + 1) + (z + 1) *	(scale + 1);

	//		mesh->indices.push_back(i[0]);
	//		mesh->indices.push_back(i[1]);
	//		mesh->indices.push_back(i[2]);

	//		mesh->indices.push_back(i[3]);
	//		mesh->indices.push_back(i[4]);
	//		mesh->indices.push_back(i[5]);
	//		//LOG << "indices : " << i0 << " " << i1 << ENDL;
	//	}
	//}

	//mesh->map.diffuse = Mesh::load(DIR_TEXTURE"terrain_test.jpg", false);



	LOG << "finish scaled mesh" << ENDL;
}

float Geometry::getHeightPixel(int x, int z, SDL_Surface * surface)
{
	uint32_t format = surface->format->BytesPerPixel;
	//LOG << "byte " << format << ENDL;
	Uint8 *point = (Uint8*)surface->pixels + z * surface->pitch + x * format;


	//https://ubuntuforums.org/archive/index.php/t-1088836.html
	switch (format)
	{
	case 1:
		return *point;
		break;
	case 2:
		return (point[0] + point[1]) / 2.f;
		break;
	case 3:
		if (SDL_BYTEORDER != SDL_BIG_ENDIAN)
			return (point[0] + point[1] + point[2]) / 3.f;			//GL_GRB
		else
			return (point[0] + point[1] + point[2]) / 3.f;			//GL_BGR fix later
		break;

	case 4:
		return (point[0] + point[1] + point[2] + point[3]) / 4.f;	//GL_RGBA
		break;
	default:
		LOG_ERROR("faile to get pixel byte");
		return 0.0f;
	}
}

vec3f Geometry::getNormal(int x, int z, SDL_Surface *map, float p, float h)
{
	vec3f normal;
	if (x < map->w - 1 && x > 0 &&
		z < map->h - 1 && z > 0)
	{
		
		vec3f p1(x * p,		getHeightPixel(x, z, map) *		h, z *p);
		vec3f p2((x -1) * p,getHeightPixel(x - 1, z, map) * h, z *p);
		vec3f p3(x * p,		getHeightPixel(x, z-1, map) *	h, (z-1) *p);

		vec3f p4((x+1) * p, getHeightPixel(x +1, z, map) *	h, z * p);
		vec3f p5(x * p,		getHeightPixel(x , z+1, map) *	h, (z+1) * p);

		vec3f edge1 = p1 - p2;
		vec3f edge2 = p1 - p3;
		
		//get normal from 2edge
		vec3f normal1 = vec3f::cross(edge1, edge2).normalized();
		//if negative flip , not sure
		if (normal1.y < 0) {
			normal1 *= -1.f;
		}

		//Next
		edge1 = p1 - p4;
		edge2 = p1 - p3;

		vec3f normal2 = vec3f::cross(edge1, edge2).normalized();
		if (normal2.y < 0) {
			normal2 *= -1.f;
		}

		//Next 
		edge1 = p1 - p5;
		edge2 = p1 - p4;

		vec3f normal3 = vec3f::cross(edge1, edge2).normalized();
		if (normal3.y < 0) {
			normal3 *= -1.f;
		}

		//Next
		edge1 = p1 - p2;
		edge2 = p1 - p5;

		vec3f normal4 = vec3f::cross(edge1, edge2).normalized();
		if (normal4.y < 0) {
			normal4 *= -1.f;
		}

		//normalize all normal
		normal = (normal1 + normal2 + normal3 + normal4).normalized();
	}
	else {
		return vec3f(0, 1, 0);		//return just upvector
	}
}


void Geometry::loadFlatTerrain(float x, float z, float mapping_scale)
{
	float width_x = x/2.f;
	float width_z = z/2.f;
	float st_x = width_x / mapping_scale;
	float st_z = width_z / mapping_scale;

	std::vector<float> v = {
		 width_x, 0,  width_z,
		-width_x, 0,  width_z,
		-width_x, 0, -width_z,
		 width_x, 0, -width_z
	};

	std::vector<float> n = {
		0, 1, 0.0f,
		0, 1, 0.0f,
		0,  1, 0.f,
		0,  1, 0
	};

	std::vector<float> st = {
		st_x, st_z,
		0.0, st_z,
		0.0, 0.0,
		st_x, 0.0
	};


	std::vector<uint32_t>index =
	{
		0,1,2,
		2,3,0
	};

	std::vector<Vertex> vertice;
	std::vector<GLuint> indices;

	for (int i = 0, j=0; i < 12; i+=3,j +=2)
	{
		Vertex vertex;
		vertex.pos =	vec3f(v[i], v[i + 1], v[i + 2]);
		vertex.normal = vec3f(n[i], v[i + 1], v[i + 2]);
		vertex.st = vec2f(st[j], st[j + 1]);
		vertex.tangent = vec3f(1, 0, 0);
		vertex.bitangent = vec3f(0, 0, 1);
		vertice.push_back(vertex);
	}

	for (int i = 0; i < index.size(); ++i)
	{
		indices.push_back(index[i]);
	}

	meshes.push_back(Mesh(vertice, indices));
}


