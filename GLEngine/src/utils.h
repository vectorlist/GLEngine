
#pragma once

#include <random>
#include <time.h>
#include <vec3f.h>
#include <matrix4x4.h>

#define RAND_FLOAT() Random::rndFloat(Random::deviceEngine)

namespace Random
{
	
	extern std::random_device rndDevice;
	//engine
	extern std::mt19937 deviceEngine;
	extern std::default_random_engine timeEngine;
	//func
	extern std::uniform_real_distribution<float> rndFloat;
	extern std::uniform_int_distribution<int> rndInt;

}

namespace Utils
{
	//check terrain id
	uint32_t getTerrainID(float x, float z);
	Matrix4x4 translateModel(const vec3f &pos,
		float rx, float ry, float rz, float scale);
	//TODO : replace parameters arrays list size

	
}