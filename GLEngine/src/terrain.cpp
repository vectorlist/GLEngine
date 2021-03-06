#include <terrain.h>
#include <cstdio>
#include <cmath>
#include <vector>

#define		TERRAIN_SIZE  800.f
#define		TERRAIN_FLAT_VERTEX_SIZE		128
#define		MAX_HEIGHT  40.0f
#define		MAX_PIXEL_COLOR  16777216.0f
#define		MAX_PIXEL_COLOR_RGB 256 * 256 * 256

Terrain::Terrain(const TerrainCreateInfo &info)
	: relative_x(info.x * TERRAIN_SIZE), relative_z(info.z * TERRAIN_SIZE),
	textures(info.textures)
{
	if (info.heightFilePath.length())
		mesh = generateTerrain(info.heightFilePath);
	else
		mesh = generateFlatTerrain();


	matrix.translate(get_relative_pos());
}

Terrain::~Terrain()
{
	if (mesh)
		delete mesh;
}

Mesh* Terrain::generateTerrain(const std::string& height_map_path)
{
	SDL_Surface* map = IMG_Load(height_map_path.c_str());
	if (!map) {
		std::string err = "failed to load height map : ";
		err.append(height_map_path);
		LOG_ERROR(err);
	}

	int vertex_size = map->h;

	//heights_ = std::vector<std::vector<float>>(vertex_size, std::vector<float>(vertex_size));
	heights.resize(vertex_size);
	for (auto &h : heights)
		h.resize(vertex_size);

	int count = vertex_size * vertex_size;
	std::vector<Vertex> vertices(count);
	std::vector<uint32_t>  indices(6 * (vertex_size - 1) * (vertex_size - 1));
	int vertexPointer = 0;
	for (int i = 0; i < vertex_size; i++) {
		for (int j = 0; j < vertex_size; j++) {
			Vertex vertex;
			vec3f pos;
			pos.x = (float)j / ((float)vertex_size - 1) * TERRAIN_SIZE;
			//height
			float height = get_height(j, i, map);
			heights[j][i] = height;
			pos.y = height;

			pos.z = (float)i / ((float)vertex_size - 1) * TERRAIN_SIZE;
			vec2f st;
			st.x = (float)j / ((float)vertex_size - 1);
			st.y = (float)i / ((float)vertex_size - 1);
			vec3f normal = get_normal(j, i, map);

			vertex.pos = pos;
			vertex.normal = normal;
			vertex.st = st;
			vertex.tangent = vec3f(1, 0, 0);
			vertex.bitangent = vec3f(0, 0, 1);
			vertices[vertexPointer] = vertex;
			++vertexPointer;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < vertex_size - 1; gz++) {
		for (int gx = 0; gx < vertex_size - 1; gx++) {
			uint32_t topLeft = (gz*vertex_size) + gx;
			uint32_t topRight = topLeft + 1;
			uint32_t bottomLeft = ((gz + 1)*vertex_size) + gx;
			uint32_t bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return new Mesh(vertices, indices);
}

Mesh* Terrain::generateFlatTerrain()
{

	int count = TERRAIN_FLAT_VERTEX_SIZE * TERRAIN_FLAT_VERTEX_SIZE;
	int vertex_size = TERRAIN_FLAT_VERTEX_SIZE;
	std::vector<Vertex> vertices(count);
	std::vector<uint32_t>  indices(6 * (vertex_size - 1) * (vertex_size - 1));

	heights = std::vector<std::vector<float>>(vertex_size, std::vector<float>(vertex_size));
	int vertexPointer = 0;
	for (int i = 0; i < vertex_size; i++) {
		for (int j = 0; j < vertex_size; j++) {
			Vertex vertex;
			vec3f pos;
			pos.x = (float)j / ((float)vertex_size - 1) * TERRAIN_SIZE;
			heights[j][i] = 0.f;
			pos.y = 0.0f;
			pos.z = (float)i / ((float)vertex_size - 1) * TERRAIN_SIZE;
			vec2f st;
			st.x = (float)j / ((float)vertex_size - 1);
			st.y = (float)i / ((float)vertex_size - 1);

			vertex.pos = pos;
			vertex.normal = vec3f(0,1,0);
			vertex.st = st;
			
			vertex.tangent = vec3f(1, 0, 0);
			vertex.bitangent = vec3f(0, 0, 1);
			vertices[vertexPointer] = vertex;
			++vertexPointer;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < vertex_size - 1; gz++) {
		for (int gx = 0; gx < vertex_size - 1; gx++) {
			uint32_t topLeft = (gz*vertex_size) + gx;
			uint32_t topRight = topLeft + 1;
			uint32_t bottomLeft = ((gz + 1)*vertex_size) + gx;
			uint32_t bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return new Mesh(vertices, indices);
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ) const
{
	float terrainX = worldX - relative_x;
	float terrainZ = worldZ - relative_z;
	float gridSquareSize = TERRAIN_SIZE / (float)(heights.size() - 1);
	int gridX = std::floor(terrainX / gridSquareSize);
	int gridZ = std::floor(terrainZ / gridSquareSize);
	if(gridX < 0 || gridX + 1 >= (int)heights.size() || gridZ < 0 ||
		gridZ + 1 >= (int)heights.size())
	{
		return 0.0f;
	}
	float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
	float height = 0.f;

	if (xCoord <= (1 - zCoord)) {
		height = barryCentric(
			vec3f(0, heights[gridX][gridZ], 0),
			vec3f(1, heights[gridX + 1][gridZ], 0),
			vec3f(0, heights[gridX][gridZ + 1], 1),
			vec2f(xCoord, zCoord));
	}
	else {
		height = barryCentric(
			vec3f(1, heights[gridX + 1][gridZ], 0),
			vec3f(1, heights[gridX + 1][gridZ + 1], 1),
			vec3f(0, heights[gridX][gridZ + 1], 1),
			vec2f(xCoord, zCoord));
	}

	return height;
}

vec3f Terrain::get_normal(unsigned int x, unsigned int z, SDL_Surface* map)
{
	float HL = get_height(x - 1, z, map);
	float HR = get_height(x + 1, z, map);
	float HD = get_height(x, z - 1, map);
	float HU = get_height(x, z + 1, map);

	vec3f normal = vec3f(HL - HR, 2.f, HD - HD).normalized();
	return normal;
}

float Terrain::get_height(unsigned int x, unsigned int z, SDL_Surface* map)
{
	if (x < 0 || x >= map->h | z < 0 || z >= map->h) {
		return 0.f;
	}
	uint32_t format = map->format->BytesPerPixel;
	Uint8 *point = (Uint8*)map->pixels + z * map->pitch + x * format;

	uint32_t r = point[0];
	uint32_t g = point[1];
	uint32_t b = point[2];
	uint32_t rgb = (r << 16) + (g << 8) + b;
	
	double value = rgb;
	value /= (MAX_PIXEL_COLOR_RGB / 2);
	value -= 1.0;
	value *= MAX_HEIGHT;

	return value;

	////https://ubuntuforums.org/archive/index.php/t-1088836.html
	//switch (format)
	//{
	//case 1:
	//	return *point;
	//	break;
	//case 2:
	//	return (point[0] + point[1]) / 2.f;
	//	break;
	//case 3:
	//	if (SDL_BYTEORDER != SDL_BIG_ENDIAN)
	//		return (point[0] + point[1] + point[2]) / 3.f;			//GL_GRB
	//	else
	//		return (point[0] + point[1] + point[2]) / 3.f;			//GL_BGR fix later
	//	break;

	//case 4:
	//	return (point[0] + point[1] + point[2] + point[3]) / 4.f;	//GL_RGBA
	//	break;
	//default:
	//	LOG_ERROR("faile to get pixel byte");
	//	return 0.0f;
	//}
}

float Terrain::barryCentric(vec3f p1, vec3f p2,
	vec3f p3, vec2f pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float L1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float L2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float L3 = 1.0f - L1 - L2;
	return L1 * p1.y + L2 * p2.y + L3 * p3.y;
}
