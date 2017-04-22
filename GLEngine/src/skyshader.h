#pragma once

#include <shader.h>

class SkyShader : public Shader
{
public:
	SkyShader(const char* vert, const char* frag);
	~SkyShader();


	void buildUniformLocations() override;

	void setProjectionMatrix(const Matrix4x4 &data);
	void setViewMatrix(const Matrix4x4 &data);
	void setFogColor(const vec3f &data);
	void setBlendFactor(const float &data);

private:
	struct 
	{
		int proj;
		int view;
		int fogColor;
		int cubemap1;
		int cubemap2;
		int blendFactor;
	}loc;
};

