#include "Geometry.h"
#include <SDL2/SDL_image.h>
#include <Mesh.h>
#include <Texture.h>
Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


//void Geometry::loadHeightMap(const std::string &filename, int scale)
//{
//	SDL_Surface* map = IMG_Load(filename.c_str());
//	if (!map) {
//		std::string err = "failed to load height map : ";
//		err.append(filename);
//		LOG_ERROR(err);
//	}
//
//	/*auto p = getHeightPixelPointer(, 0, map);*/
//	//float n = NORMALIZE_HEIGHT;
//	//calculateNormal(10, 10, map, n, 0.3);
//
//	uint32_t scale_size = scale;
//	x_size = map->w;
//	z_size = map->h;
//	LOG << "height map size : " << x_size << " : " << z_size << ENDL;
//	int totalScaled = 0;
//	//per scaled size
//	if (scale >= x_size) {
//		overScale = true;
//		LOG << "over scale" << ENDL;
//	}
//
//	for (int geo_z = 0; geo_z < map->h; geo_z += scale_size){
//		for (int geo_x = 0; geo_x < map->w; geo_x += scale_size){
//
//			//if (geo_z >= x_size - (scale) || geo_x >= z_size -(scale)) continue;
//			/*mesh_ptr m = mesh_ptr(new Mesh());*/
//			Mesh* mesh = new Mesh;
//			mesh->indice_size = 3 * 2 * ((scale_size - 1 + 1) * (scale_size - 1 + 1));
//			mesh->vertices_size = (scale_size + 1) * (scale_size + 1);
//
//			
//			LOG << " z : " << geo_z << ENDL;
//			LOG <<  " x : " << geo_x << ENDL;
//
//			buildScaledMesh(geo_z, geo_x, scale_size, mesh, map);
//
//			mesh->buildBuffer();
//
//			totalScaled++;
//		}
//	}
//
//	/*LOG << "total scale tailed : " <<  totalScaled << ENDL;*/
//}

void Geometry::loadTerrain(const std::string & filename,
	float planeScale, float heightScale, unsigned int scalesize)
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
			Mesh* m = new Mesh;

			m->indice_size = 3 * 2 * ((scale_size - 1 + 1) * (scale_size - 1 + 1));
			m->vertices_size = (scale_size + 1) * (scale_size + 1);

			for (int z = z_total; z < z_total + scale_size + 1; z++) {
				for (int x = x_total; x < x_total + scale_size + 1; x++) {
					// uint8 / 255
					float y = getHeightPixel(x, z, map) * (heightScale / 255.f);

					//TODO : scale per vertex issue
					/*float f_x = x * planeScale / (float)x_total;
					float f_z = z * planeScale / (float)z_total;*/

					m->vertices.push_back(x);
					m->vertices.push_back(y);
					m->vertices.push_back(z);

					vec3f normal = calculateNormal(x, z, map, planeScale, heightScale);
					m->normals.push_back(normal.x);
					m->normals.push_back(normal.y);
					m->normals.push_back(normal.z);

					m->st.push_back(x);
					m->st.push_back(z);


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

					m->indices.push_back(i[0]);
					m->indices.push_back(i[1]);
					m->indices.push_back(i[2]);

					m->indices.push_back(i[3]);
					m->indices.push_back(i[4]);
					m->indices.push_back(i[5]);
					//LOG << "indices : " << i0 << " " << i1 << ENDL;
				}
			}
			m->map.diffuse = Mesh::load(DIR_TEXTURE"terrain_test.jpg", false);
			
			m->buildBuffer();
			meshs.push_back(m);
		}
	}
}


void Geometry::buildScaledMesh(int geoZ, int geoX, int perScale, Mesh * mesh, SDL_Surface * map)
{
	int sumZ = geoZ + perScale + 1;
	int sumX = geoX + perScale + 1;

	//Build Vertex Propertis
	if (overScale) {
		sumZ = z_size;
		sumX = x_size;
	}
	for (int z = geoZ; z < sumZ; z++) {
		for (int x = geoX; x < sumX; x++){
			float y = getHeightPixel(x, z, map) * NORMALIZE_HEIGHT;
			LOG << z << ENDL;
			//Vertex
			mesh->vertices.push_back(x);
			mesh->vertices.push_back(y);
			mesh->vertices.push_back(z);

			//Normal
			vec3f normal = calculateNormal(x, z, map, geo_scale, 1.f);
			mesh->normals.push_back(normal.x);
			mesh->normals.push_back(normal.y);
			mesh->normals.push_back(normal.z);
			//LOG << "height : " << p << ENDL;

			//ST
			mesh->st.push_back(x);
			mesh->st.push_back(z);

			//TANGENT  later
		}
	}
	int scale = perScale;
	if (overScale)
	{
		scale = geoZ;
	}

	//Build Indices
	for (int z = 0; z < scale - 1 + 1; ++z)
	{
		for (int x = 0; x < scale - 1 + 1; ++x)
		{
			int i[5];								//quad indices
													//tri1
			i[0] = x + z			 *	(scale + 1);
			i[1] = (x + 1) + (z + 1) *	(scale + 1);
			i[2] = (x + 1) + z *		(scale + 1);

			//tri 2
			i[3] = x + z *				(scale + 1);
			i[4] = x + (z + 1) *		(scale + 1);
			i[5] = (x + 1) + (z + 1) *	(scale + 1);

			mesh->indices.push_back(i[0]);
			mesh->indices.push_back(i[1]);
			mesh->indices.push_back(i[2]);

			mesh->indices.push_back(i[3]);
			mesh->indices.push_back(i[4]);
			mesh->indices.push_back(i[5]);
			//LOG << "indices : " << i0 << " " << i1 << ENDL;
		}
	}

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

	vec3f Geometry::calculateNormal(int x, int z, SDL_Surface *map, float p, float h)
{
	vec3f normal;
	if ((x < map->w - 1 && x > 0) &&
		(z < map->h - 1 && z > 0))
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
			normal1.y *= -1.f;
		}

		//Next
		edge1 = p1 - p4;
		edge2 = p1 - p3;

		vec3f normal2 = vec3f::cross(edge1, edge2).normalized();
		if (normal2.y < 0) {
			normal2.y *= -1.f;
		}

		//Next 
		edge1 = p1 - p5;
		edge2 = p1 - p4;

		vec3f normal3 = vec3f::cross(edge1, edge2).normalized();
		if (normal3.y < 0) {
			normal3.y *= -1.f;
		}

		//Next
		edge1 = p1 - p2;
		edge2 = p1 - p5;

		vec3f normal4 = vec3f::cross(edge1, edge2).normalized();
		if (normal4.y < 0) {
			normal4.y *= -1.f;
		}

		//normalize all normal
		normal = (normal1 + normal2 + normal3 + normal4).normalized();


		/*LOG << " 0 : " << p1 << ENDL;
		LOG << " 1 : " << p2 << ENDL;
		LOG << " 2 : " << p3 << ENDL;

		LOG << "normal : " << normal << ENDL;*/
	}
	else {
		return vec3f(0, 1, 0);		//return just upvector
	}
}


void Geometry::buildFlatTerrain()
{
	//mesh->
	std::vector<float> v2 = {
		50, 0.0, 50,
		-50,0, 50,
		-50,0,-50,
		50,0,-50
	};

	std::vector<float> n2 = {
		0, 1, 0.0f,
		0, 1, 0.0f,
		0,  1, 0.f,
		0,  1, 0
	};

	std::vector<float> st2 = {
		50.0, 50.0,
		0.0, 50.0,
		0.0, 0.0,
		50.0, 0.0
	};


	std::vector<uint32_t>i2 =
	{
		0,1,2,
		2,3,0
	};
	Mesh* mesh = new Mesh;
	for (int i = 0; i < v2.size(); ++i)
	{
		mesh->vertices.push_back(v2[i]);
		mesh->normals.push_back(n2[i]);
	}

	for (int i = 0; i < st2.size(); ++i)
	{
		mesh->st.push_back(st2[i]);
	}

	for (int i = 0; i < i2.size(); ++i)
	{
		mesh->indices.push_back(i2[i]);
	}

	mesh->map.diffuse = Mesh::load(DIR_TEXTURE"terrain_test.jpg", false);
	mesh->buildBuffer();
	meshs.push_back(mesh);
}


