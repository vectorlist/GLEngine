#include <forwardshader.h>


ForwardShader::ForwardShader(const char * vert, const char * frag)
	: Shader(vert, frag)
{
	buildUniformLocations();
}

void ForwardShader::buildUniformLocations()
{
	bind();
	loc.proj = setUniformLocation("proj");
	loc.view = setUniformLocation("view");
	loc.model = setUniformLocation("model");
	loc.lightPos = setUniformLocation("lightPos");
	loc.lightColor = setUniformLocation("lightColor");
	loc.shiness = setUniformLocation("shiness");
	loc.skyColor = setUniformLocation("skyColor;");
	loc.textureDiffuse = setUniformLocation("textureDiffuse");
	unbind();
}

void ForwardShader::setProjectionMatrix(const Matrix4x4 & proj)
{
	setLocationMatrix4f(loc.proj, proj, true);
}

void ForwardShader::setViewMatrix(const Matrix4x4 & view)
{
	setLocationMatrix4f(loc.view, view, true);
}

void ForwardShader::setModelMatrix(const Matrix4x4 & model)
{
	setLocationMatrix4f(loc.model, model, true);
}

void ForwardShader::setLightpos(const vec3f & data)
{
	setLocation3f(loc.lightPos, data);
}

void ForwardShader::setLightColor(const vec3f & data)
{
	setLocation3f(loc.lightColor, data);
}

void ForwardShader::setShiness(float data)
{
	setLocation1f(loc.shiness, data);
}

void ForwardShader::setSkyColor(const vec3f &skyColor)
{
	setLocation3f(loc.skyColor, skyColor);
}

void ForwardShader::bindTextureLocations()
{
	setLocation1i(loc.textureDiffuse, 0);
}



