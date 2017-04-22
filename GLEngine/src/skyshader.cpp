#include "skyshader.h"


SkyShader::SkyShader(const char* vert, const char* frag)
	: Shader(vert, frag)
{
	buildUniformLocations();
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
	loc.cubemap1 = setUniformLocation("cubemap1");
	loc.cubemap2 = setUniformLocation("cubemap2");
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

