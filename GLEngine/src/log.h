#pragma once

#include <iostream>
#include <Windows.h>
#include <assert.h>

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
		MessageBox(NULL, err.c_str(), "Error", MB_OK);
		assert(0 && msg.c_str());
	}
}
