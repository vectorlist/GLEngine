#include "Performance.h"

std::map<Counter_Type, Counter> Performance::counters;

void Performance::begin(Counter_Type type)
{
	Counter* current_counter;
	//check counter allocated already
	if (counters.count(type)) {
		current_counter = &counters.at(type);
	}
	else {
		Counter new_counter;
		current_counter = &new_counter;
	}
	 
	current_counter->started = true;
	current_counter->begin_time = Clock::now();
	
	counters[type] = *current_counter;
}

void Performance::end(Counter_Type type)
{
	Counter* current_counter;
	if (!counters.count(type))
		LOG_ERROR("Performance : forgot start?");

	current_counter = &counters.at(type);
	current_counter->started = false;
	current_counter->num_run++;

	
	/*std::chrono::duration<double> current_time =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			Clock::now() - current_counter->begin_time);*/

	auto end_time(Clock::now());

	current_counter->elapse_time = (end_time - current_counter->begin_time);

}

void Performance::show()
{
	for (std::map<Counter_Type, Counter>::iterator it = counters.begin();
		it != counters.end(); ++it)
	{
		
		Counter &counter = it->second;
		if (counter.num_run != 0)
		{
			//TODO : need per frame
			double average =
				std::chrono::duration_cast<std::chrono::milliseconds>
				(counter.elapse_time).count() ;

			auto fsecond(average / 1000.f);
			auto fps(1.f / fsecond);
			LOG << "Performance : " << fsecond  
				<< " " << fps << ".ms" << ENDL;
		}
	}
}

float Performance::get_fps(Counter_Type type)
{
	auto &counter = counters[type];
	double average =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(counter.elapse_time).count();

	auto fsecond(average / 1000.f);
	auto fps(1.f / fsecond);
	return fps;
}

