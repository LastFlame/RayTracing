#pragma once
#include "ray.h"

class material;

struct hit_record
{
	float t;
	vec3 point;
	vec3 normal;
	material* ptr_mat;
};

class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record ) const = 0;

};

