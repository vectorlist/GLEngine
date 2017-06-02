#pragma once

#include <GL/glew.h>
#include <texture.h>
#include <entity.h>
#include <terrain.h>
#include <vector>


class FrameBuffer
{
public:
	FrameBuffer(int frameBufferWidth, int frameBufferHeight,
		int windowWidth, int windowHeight);
	~FrameBuffer();

	
	void bind();
	void unbind();
	GLuint shadowMap;
private:
	void buildFrameBuffer();
	GLuint fbo;

	
	//frame buffer size
	int frameBufferWidth, frameBufferHeight;
	//window renderer size
	int windowWidth, windowHeight;
};

