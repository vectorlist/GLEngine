#include "terrainshader.h"



TerrainShader::TerrainShader(const char * vert, const char * frag)
	: Shader(vert, frag)
{
	buildUniformLocations();
}

void TerrainShader::buildUniformLocations()
{
	bind();
	loc.proj = setUniformLocation("proj");
	loc.view = setUniformLocation("view");
	loc.model = setUniformLocation("model");
	loc.lightPos = setUniformLocation("lightPos");
	loc.lightColor = setUniformLocation("lightColor");
	loc.textureBackground = setUniformLocation("textureBackground");
	loc.textureR = setUniformLocation("textureR");
	loc.textureG = setUniformLocation("textureG");
	loc.textureB = setUniformLocation("textureB");
	loc.textureBlend = setUniformLocation("textureBlend");
	unbind();
}

void TerrainShader::setProjectionMatrix(const Matrix4x4 & proj)
{
	setLocationMatrix4f(loc.proj, proj, true);
}

void TerrainShader::setViewMatrix(const Matrix4x4 & view)
{
	setLocationMatrix4f(loc.view, view, true);
}

void TerrainShader::setModelMatrix(const Matrix4x4 & model)
{
	setLocationMatrix4f(loc.model, model, true);
}

void TerrainShader::setLightpos(const vec3f & data)
{
	setLocation3f(loc.lightPos, data);
}

void TerrainShader::setLightColor(const vec3f & data)
{
	setLocation3f(loc.lightColor, data);
}

void TerrainShader::setSkyColor(const vec3f &skyColor)
{
	setLocation3f(loc.skyColor, skyColor);
}

void TerrainShader::bindTextureLocations()
{
	setLocation1i(loc.textureBackground, 0);
	setLocation1i(loc.textureR, 1);
	setLocation1i(loc.textureG, 2);
	setLocation1i(loc.textureB, 3);
	setLocation1i(loc.textureBlend, 4);
}


