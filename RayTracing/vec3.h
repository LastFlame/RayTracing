#pragma once
#include <stdlib.h>
#include <math.h>

class vec3
{
public:
	vec3() {};
	vec3(float p0, float p1, float p2) { p[0] = p0; p[1] = p1; p[2] = p2; }
	inline float x() const { return p[0]; }
	inline float y() const { return p[1]; }
	inline float z() const { return p[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-p[0], -p[1], p[2]); }
	inline float operator[](int i) const { return p[i]; }
	inline float& operator[] (int i) { return p[i]; }

	inline vec3& operator+= (const vec3& v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*= (const vec3& v2);
	inline vec3& operator/= (const vec3& v2);

	inline vec3& operator*= ( float t);
	inline vec3& operator/= (float t);

	inline float lenght() const { return sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]); }
	inline float sqrt_lenght() const { return p[0] * p[0] + p[1] * p[1] + p[2] * p[2]; }
	inline void make_unit_vector();

	float p[3]{0,0,0};

};

inline vec3 & vec3::operator+=(const vec3 & v2)
{
	p[0] += v2.p[0];
	p[1] += v2.p[1];
	p[2] += v2.p[2];

	return *this;
}

inline vec3 & vec3::operator/=(const vec3 & v2)
{
	p[0] /= v2.p[0];
	p[1] /= v2.p[1];
	p[2] /= v2.p[2];

	return *this;
}



inline vec3& vec3::operator*= (float t)
{
	p[0] *= t;
	p[1] *= t;
	p[2] *= t;
}

inline vec3 & vec3::operator/=(float t)
{
	p[0] /= t;
	p[1] /= t;
	p[2] /= t;
	
	return *this;
}

inline void vec3::make_unit_vector()
{
	int i = 1 / lenght();
	p[0] *= i;
	p[1] *= i;
	p[2] *= i;
}

inline vec3 operator/ (vec3 v, float t)
{
	return vec3(v.p[0] / t, v.p[1] / t, v.p[2] / t);
}

inline vec3 operator* (const vec3& v, const vec3& v2)
{
	return vec3(v.p[0] * v2.p[0], v.p[1] * v2.p[1], v.p[2] * v2.p[2]);
}
inline vec3 operator* (const vec3& v, float t)
{
	return vec3(v.p[0] * t, v.p[1] * t, v.p[2] * t);
}

inline vec3 operator* (float t, const vec3& v)
{
	return vec3(v.p[0] * t, v.p[1] * t, v.p[2] * t);
}

inline vec3 operator+ (const vec3& v, const vec3& v2)
{
	return vec3(v.p[0] + v2.p[0], v.p[1] + v2.p[1], v.p[2] + v2.p[2]);
}

inline vec3 operator- (const vec3& v, const vec3& v2)
{
	return vec3(v.p[0] - v2.p[0], v.p[1] - v2.p[1], v.p[2] - v2.p[2]);
}

inline float dot(const vec3& v, const vec3& v2)
{
	return v.p[0] * v2.p[0] + v.p[1] * v2.p[1] + v.p[2] * v2.p[2];
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.lenght();
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) *n;
}

