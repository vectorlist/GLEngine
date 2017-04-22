#pragma once
#include <random>
#include <time.h>

#define RAND_FLOAT() Random::rndFloat(Random::deviceEngine)

namespace Random
{
	std::random_device rndDevice;
	//engine
	std::mt19937 deviceEngine(rndDevice());
	std::default_random_engine timeEngine(time(0));
	//func
	std::uniform_real_distribution<float> rndFloat(0.f, 1.0f);
	std::uniform_int_distribution<int> rndInt(0, 3);
}

namespace Utils
{
	//check terrain id
	uint32_t getTerrainID(float x, float z)
	{
		if (x < 0.f && z > 0)  return 0;
		else if (x >= 0.f && z >= 0) return 1;  //x 0-800 z 0-800
		else if (x >= 0.0f && z < 0) return 2;  //0 -- 800 0 --- -800
		else if (x < 0.0f && z < 0) return 3;  //0 -- -800 0 --- -800
		return -1;
	};

	//TODO : replace parameters arrays list size
	auto selectiveByRandom = [&]
	{
		float r = RAND_FLOAT();
		int result;
		if (r < 0.05)
			result = 0;
		if (r < 0.20)
			result = 1;
		if (r < 0.60)
			result = 2;
		else
			result = 3;						//most
		return result;
	};
}