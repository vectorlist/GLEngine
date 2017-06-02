#pragma once

#include <Camera.h>
#include <framebuffer.h>
#include <vector>
#include <entity.h>
#include <shadowbbox.h>
#define SHADOW_MAP_SIZE			8100

class ShadowRenderer
{
public:
	ShadowRenderer(int windowWidth, int windowHeight,Camera &camera);
	~ShadowRenderer();


	void render(std::vector<entity_ptr> &entities, const vec3f &sun,
		const vec3f &at);
	void renderFrambuffer(std::vector<entity_ptr> &entities);

	ShadowBBox shadow_bbox;
	FrameBuffer frameBuffer;
	Camera &camera;
	GLuint depthShader;
	

	GLuint getShadowMap();
	Matrix4x4 getShadowMatrix();
	Matrix4x4 getShadowRelativeMatrix() { return projectionView; }
private:
	//Matrix for frambuffers (light projection view matrix)
	Matrix4x4 projection;
	Matrix4x4 view;
	Matrix4x4 projectionView;
	//offset
	static const Matrix4x4 bias;

	void updateProjection(float width, float height, float length);
	void updateView(const vec3f &direction, const vec3f &center);

};

