#pragma once
#include "vec3.h"

class ray
{
public:
	ray() {}
	ray(const vec3& a, const vec3& b) { this->a = a; this->b = b; }
	vec3 origin() const { return a; }
	vec3 direction() const { return b; }
	vec3 point_at_parameter(float t) const { return a + t*b; }

private:
	vec3 a;
	vec3 b;
};