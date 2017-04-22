#include "skyshader.h"


SkyShader::SkyShader(const char* vert, const char* frag)
	: Shader(vert, frag)
{
	buildUniformLocations();
	//dynamically
	setAttribute(0, "position");
}

SkyShader::~SkyShader()
{
}

void SkyShader::buildUniformLocations()
{
	bind();
	loc.proj = setUniformLocation("proj");
	loc.view = setUniformLocation("view");
	loc.fogColor = setUniformLocation("fogColor");
	loc.cubemap = setUniformLocation("cubemap");
	loc.blendFactor = setUniformLocation("blendFactor");
	unbind();
}

void SkyShader::setProjectionMatrix(const Matrix4x4 &data)
{
	setLocationMatrix4f(loc.proj, data, true);
}

void SkyShader::setViewMatrix(const Matrix4x4 &data)
{
	setLocationMatrix4f(loc.view, data, true);
}

void SkyShader::setFogColor(const vec3f &data)
{
	setLocation3f(loc.fogColor, data);
}

void SkyShader::setBlendFactor(const float &data)
{
	setLocation1f(loc.blendFactor, data);
}

