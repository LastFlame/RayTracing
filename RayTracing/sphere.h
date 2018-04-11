#pragma once
#include "hitable.h"
#include <memory>


class sphere : public hitable
{
public:
	sphere() {}

	sphere(vec3 cen, float r,  std::unique_ptr<material> mat ) : center(cen), radius(r), current_material (std::move(mat)) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const;
	vec3 center;
	float radius;

private:
	std::unique_ptr<material> current_material;
};


bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b -  a*c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - center) / radius;
			rec.ptr_mat = current_material.get();
			return true;
		}

		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - center) / radius;
			rec.ptr_mat = current_material.get();
			return true;
		}
	}
	return false;
}


