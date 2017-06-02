#pragma once

#include <iostream>
#include <Windows.h>
#include <assert.h>

#define LOG						std::cout
#define ENDL					std::endl

#define LOG_ERROR(x)				Log::log_error(x)
#define LOG_SHADER_ERROR(x,xx)		Log::log_shader_error(x,xx)

namespace Log
{
	inline void log_error(const std::string &msg)
	{
		MessageBox(NULL, msg.c_str(), "Error", MB_OK);
		assert(0 && msg.c_str());
	}

	inline void log_shader_error(const std::string &path, const std::string &msg)
	{
		std::string err = path;
		err.append(" : ").append(msg);
		LOG << err.c_str() << ENDL;
		MessageBox(NULL, err.c_str(), "Error", MB_OK);
		//assert(0 && msg.c_str());
	}
}

class LogWriter
{
public:
	LogWriter(const std::string& filename){}

	inline void write(){}

	std::string data;
	//std::ostream log_file;
	LogWriter& operator<<(const std::string &s) {
		data.append(s);
		return *this;
	}

};