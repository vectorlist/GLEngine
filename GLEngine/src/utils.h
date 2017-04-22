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