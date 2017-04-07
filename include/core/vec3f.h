
#ifndef VEC3F_H
#define VEC3F_H

#include <algorithm>
#include <assert.h>
#include <ostream>
#undef min
#undef max
class vec3f
{
public:
	float x, y, z;
	vec3f() : x(0.0), y(0.0), z(0.0){}
	vec3f(const vec3f &v) : x(v.x), y(v.y), z(v.z){}
	vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
	explicit vec3f(float f) : x(f), y(f), z(f){}

	float& operator[](unsigned int i)
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}
	float operator[](unsigned int i) const
	{
		assert(i >= 0 && i <= 2);
		return (&x)[i];
	}

	float length2() const { return x * x + y * y + z * z; }
	float length() const { return std::sqrt(length2()); }

	//normailze itself and return length
	float normalize() { float len = length(); *this /= len; return len; }
	//return normalize vector without calculate itself
	vec3f normalized() const
	{
		vec3f nor(*this);
		nor.normalize();
		return nor;
	}

	vec3f negative() const {
		return vec3f(-x, -y, -z);
	}
	vec3f& operator = (const vec3f &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	vec3f operator-() const
	{
		return vec3f(-x, -y, -z);
	}

	vec3f& operator+=(const vec3f &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3f& operator-=(const vec3f &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3f& operator*=(const vec3f &v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3f& operator/=(const vec3f &v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	vec3f& operator*=(const float &f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	vec3f& operator/= (const float &f)
	{
		float inv = 1.f / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
	/*----------------- LOCAL -------------------------*/
	inline float dot(const vec3f &v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	inline vec3f cross(const vec3f &v)
	{
		return vec3f(y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}

	/*----------------- STATICS -----------------------*/
	static float dot(const vec3f &v1, const vec3f &v2);
	static float fabsdot(const vec3f &v1, const vec3f &v2);
	static vec3f cross(const vec3f &v1, const vec3f &v2);
	static vec3f reflect(const vec3f &dir, const vec3f &n);
	static vec3f min(const vec3f &v1, const vec3f &v2);
	static vec3f max(const vec3f &v1, const vec3f &v2);
	/*-------------------------------------------------*/

	static const vec3f AxisX;
	static const vec3f AxisY;
	static const vec3f AxisZ;

	float maxComponent() const { return std::max(std::max(x, y), z); }
	float minComponent() const { return std::min(std::min(x, y), z); }

	friend std::ostream& operator<<(std::ostream &o, const vec3f &v)
	{
		o << "vec3( " << v.x << ", " << v.y << " ," << v.z << ')';
		return o;
	}

};

inline vec3f operator+(const vec3f &v1, const vec3f &v2)
{
	return vec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3f operator-(const vec3f &v1, const vec3f &v2)
{
	return vec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3f operator*(const vec3f &v1, const vec3f &v2)
{
	return vec3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline vec3f operator*(const vec3f &v, float f)
{
	return vec3f(f * v.x, f * v.y, f * v.z);
}

inline vec3f operator*(float f, const vec3f &v)
{
	return vec3f(f * v.x, f * v.y, f * v.z);
}

inline vec3f operator/(const vec3f &v, float f)
{
	float inv = 1.f / f;
	return vec3f(v.x * inv, v.y * inv, v.z * inv);
}

inline vec3f operator/(float f, const vec3f &v)
{
	return vec3f(f / v.x, f / v.y, f / v.z);
}

inline vec3f operator/(const vec3f &v1, const vec3f &v2)
{
	return vec3f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline bool operator==(const vec3f &r, const vec3f &l)
{ 
	return (r.x == l.x && r.y == l.y && r.z == l.z);
}

inline bool operator!=(const vec3f &r, const vec3f &l)
{
	return (r.x != l.x && r.y != l.y && r.z != l.z);
}

inline bool operator>(const vec3f &r, const vec3f &l)
{
	return (r.length2() > l.length2());
}

inline bool operator<(const vec3f &r, const vec3f &l)
{
	return (r.length2() < l.length2());
}

#endif //VEC3F_H