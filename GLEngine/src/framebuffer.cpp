#include "framebuffer.h"
#include <shadertool.h>
#include <utils.h>

//@param framebuffer size, window size
FrameBuffer::FrameBuffer(
	int frameBufferWidth, int frameBufferHeight,
	int windowWidth, int windowHeight)
	: 
	frameBufferWidth(frameBufferWidth), frameBufferHeight(frameBufferHeight),
	windowWidth(windowWidth), windowHeight(windowHeight)
{
	buildFrameBuffer();
}


FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST);
	//refresh to DEPTH BUFFER BIT
	glClear(GL_DEPTH_BUFFER_BIT);
	//fit frame buffe size to whole screen rect
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//we are finished frame buffer
	//back to window viewport size

	glViewport(0, 0, windowWidth, windowHeight);
}

void FrameBuffer::buildFrameBuffer()
{
	//gen frame buffer
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//no read and draw
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//gen texture for framebuffer
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_DEPTH_COMPONENT16,
		frameBufferWidth, frameBufferHeight,
		0,
		GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//bounding texture to frame buffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);
	//finish bounding framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

