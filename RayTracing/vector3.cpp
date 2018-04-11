#pragma once
#include <math.h>

class vector3
{
public:
	vector3() {};
	vector3(float p1, float p2, float p3) { p[0] = p1; p[1] = p2; p[2] = p3; }
	inline float x() const { return p[0]; }
	inline float y() const { return p[1]; }
	inline float z() const { return p[2]; }

	inline const vector3& operator+() const { return *this; }
	inline vector3 operator-() const { return vector3(-p[0], -p[1], p[2]); }
	inline float operator[](int i) const { return p[i]; }
	inline float& operator[] (int i) { return p[i]; }

	inline vector3& operator+= (const vector3& v2);
	inline vector3& operator-=(const vector3& v2);
	inline vector3& operator*= (const vector3& v2);
	inline vector3& operator/= (const vector3& v2);
	inline vector3& operator*= (float t);
	inline vector3& operator/= (float t);

	inline float length() const { return sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]); }
	inline float sqrt_lenght() const { return p[0] * p[0] + p[1] * p[1] + p[2] * p[2]; }
	inline void make_unit_vector();

private:
	float p[3];
};







