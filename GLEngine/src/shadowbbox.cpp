#include "shadowbbox.h"
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

const float ShadowBBox::OFFSET			= 10;
const vec3f ShadowBBox::UP				= vec3f(0, 1,  0);
const vec3f ShadowBBox::FRONT			= vec3f(0, 0, -1);
const float ShadowBBox::SHADOW_DISTANCE	= 150;


ShadowBBox::ShadowBBox(Matrix4x4 &lightView, Camera &camera)
	: camera(camera), lightView(lightView)
{
	buildBoundingBox();
}


ShadowBBox::~ShadowBBox()
{

}

void ShadowBBox::buildBoundingBox()
{
	farWidth = SHADOW_DISTANCE * tan(radians(camera.fov()));
	farHeight = farWidth / camera.aspect();

	nearWidth = camera.nearPlane() * tan(radians(camera.fov()));
	nearHeight = nearWidth / camera.aspect();
}

Matrix4x4 ShadowBBox::getCameraRotation()
{
	Matrix4x4 rotation;
	rotation.rotate(AXIS::Y, -camera.yaw());
	rotation.rotate(AXIS::X, -camera.pitch());
	return rotation;
}

std::vector<vec3f> ShadowBBox::buildFrustum(
	const Matrix4x4 &rotation,
	const vec3f &front,
	const vec3f &centerNear,
	const vec3f &centerFar)
{
	//get rotation direction
	vec3f up = (rotation * UP);
	vec3f right = vec3f::cross(front, up);
	vec3f down = up.negative();
	vec3f left = right.negative();
	vec3f farTop = centerFar + (up * farHeight);
	vec3f farButtom = centerFar + (down * farHeight);
	vec3f nearTop = centerNear + (up * nearHeight);
	vec3f nearButtom = centerNear + (down * nearHeight);

	std::vector<vec3f> points(8);
	//far vertices
	points[0] = getFrustumCorner(farTop, right, farWidth);
	points[1] = getFrustumCorner(farTop, left, farWidth);
	points[2] = getFrustumCorner(farButtom, right, farWidth);
	points[3] = getFrustumCorner(farButtom, left, farWidth);
	//near vertices
	points[4] = getFrustumCorner(nearTop, right, nearWidth);
	points[5] = getFrustumCorner(nearTop, left, nearWidth);
	points[6] = getFrustumCorner(nearButtom, right, nearWidth);
	points[7] = getFrustumCorner(nearButtom, left, nearWidth);

	return points;
}

vec3f ShadowBBox::getFrustumCorner(const vec3f &startPoint, const vec3f &direction, float width)
{
	vec3f point = startPoint + (direction * width);
	vec3f point3 = lightView * point;
	return point3;
}

void ShadowBBox::update()
{
	//get rotation
	Matrix4x4 rotation = getCameraRotation();
	//get forward
	vec3f forward = rotation * FRONT;

	vec3f toFar = forward;
	toFar *= SHADOW_DISTANCE;
	vec3f toNear = forward;
	toNear *= camera.nearPlane();

	//all fine so far
	vec3f centerNear = toNear + camera.position();
	vec3f centerFar = toFar + camera.position();

	auto points = buildFrustum(rotation,forward, centerNear, centerFar);

	bool first = true;

	for (auto& point : points)
	{
		if (first) {
			minX = point.x;
			maxX = point.x;
			minY = point.y;
			maxY = point.y;
			minZ = point.z;
			maxZ = point.z;
			first = false;
			continue;
		}
		if (point.x > maxX) {
			maxX = point.x;
		}
		else if (point.x < minX) {
			minX = point.x;
		}

		if (point.y > maxY) {
			maxY = point.y;
		}
		else if (point.y < minY) {
			minY = point.y;
		}

		if (point.z > maxZ) {
			maxZ = point.z;
		}
		else if (point.z < minZ) {
			minZ = point.z;
		}
		maxZ += OFFSET;
	}
	//LOG << camera.position() << ENDL;
	//LOG << "max x " << maxX<< " max y " << maxY << " max z "<< maxZ << ENDL;

}

vec3f ShadowBBox::getCenter()
{
	float x = (minX + maxX) /2.f;
	float y = (minY + maxY) /2.f;
	float z = (minZ + maxZ) /2.f;
	//vec4f center = vec4f(x, y, z, 1.f);
	vec3f center(x, y, z);
	
	Matrix4x4 invertedLight = lightView.inverted();
	auto outCenter = (invertedLight * center);
	//LOG << "center : " << center <<  " viewCenter : " << outCenter  <<ENDL;

	return outCenter;
}
