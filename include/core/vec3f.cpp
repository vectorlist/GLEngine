#include <vec3f.h>

const vec3f vec3f::AxisX = vec3f(1.f, 0, 0);
const vec3f vec3f::AxisY = vec3f(0, 1.f, 0);
const vec3f vec3f::AxisZ = vec3f(0, 0, 1.f);

float vec3f::dot(const vec3f &v1, const vec3f &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float vec3f::fabsdot(const vec3f &v1, const vec3f &v2)
{
	return fabs(vec3f::dot(v1, v2));
}

vec3f vec3f::cross(const vec3f& v1, const vec3f& v2)
{
	return vec3f(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

vec3f vec3f::reflect(const vec3f &dir, const vec3f &n)
{
	/*Vnew = b * (-2 * (V dot N)*N + V)*/
	//vec3f reflected = (dir * 2 * vec3f::dot(n, dir)) - n;
	return dir - n * 2 * vec3f::dot(n, dir);
}

vec3f vec3f::min(const vec3f &v1, const vec3f &v2)
{
	return vec3f(	std::min(v1.x, v2.x),
					std::min(v1.y, v2.y),
					std::min(v1.z, v2.z));
}

vec3f vec3f::max(const vec3f &v1, const vec3f &v2)
{
	return vec3f(	std::max(v1.x, v2.x),
					std::max(v1.y, v2.y),
					std::max(v1.z, v2.z));
}