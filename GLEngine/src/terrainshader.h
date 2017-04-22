#pragma once

#include <shader.h>

class TerrainShader : public Shader
{
public:
	TerrainShader(const char* vert, const char* frag);

	virtual void buildUniformLocations() override;

	void setProjectionMatrix(const Matrix4x4& proj);
	void setViewMatrix(const Matrix4x4& view);
	void setModelMatrix(const Matrix4x4& model);
	void setLightpos(const vec3f &data);
	void setLightColor(const vec3f &data);
	void setSkyColor(const vec3f &skyColor);

	void bindTextureLocations();

	//locations
	struct
	{
		int proj;
		int view;
		int model;
		int lightPos;
		int lightColor;
		int skyColor;
		//texture
		int textureBackground;
		int textureR;
		int textureG;
		int textureB;
		int textureBlend;
	}loc;
};

