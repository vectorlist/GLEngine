#pragma once

#include <chrono>
#include <vector>
#include <map>
#include <config.h>

typedef std::chrono::high_resolution_clock Clock;


enum class Counter_Type : unsigned int
{
	FPS,
	SECONT
};

struct Counter
{
	bool started = false;
	Clock::time_point begin_time;
	std::chrono::duration<double> total_time;
	std::chrono::duration<double> elapse_time;
	unsigned int num_run = 0;
};

class Performance
{
public:
	Performance() {};
	~Performance() {};

	static void begin(Counter_Type type);
	static void end(Counter_Type type);
	static void show();
	static float get_fps(Counter_Type type);

	/*bool started = false;
	Clock::time_point begin_time;
	std::chrono::duration<double> total_time;*/

	static std::map<Counter_Type, Counter> counters;
};

