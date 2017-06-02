#pragma once

#include <Camera.h>
#include <vec4f.h>

class ShadowBBox
{
public:
	ShadowBBox(Matrix4x4 &lightView,Camera &camera);
	~ShadowBBox();


	const static float OFFSET;
	const static vec3f UP;
	const static vec3f FRONT;
	const static float SHADOW_DISTANCE;


	float getWidth() { return maxX - minX; }
	float getHeight() { return maxY - minY; }
	float getLength() { return maxZ - minZ; }
	void update();

	vec3f getCenter();
private:
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;

	Matrix4x4& lightView;
	Camera &camera;

	void buildBoundingBox();
	Matrix4x4 getCameraRotation();
	//vec4f buildLightFrustum();

	//build frustum 8point
	std::vector<vec3f> buildFrustum(
		const Matrix4x4 &rotation,
		const vec3f &front,
		const vec3f &centerNear,
		const vec3f &centerFar);

	vec3f getFrustumCorner(
		const vec3f &startPoint,
		const vec3f &direction, float width);


	//struct
	//{
	//	float farwidth;
	//}box;
	float nearWidth;
	float nearHeight;
	float farWidth;
	float farHeight;
};

