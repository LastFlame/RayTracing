#pragma once
#include "material.h"
#include <random>

class lambertian : public material
{
public :
	lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 target = rec.point + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.point, target - rec.point);
		attenuation = albedo;
		return true;
	}

	vec3 albedo;

private: 
	vec3 random_in_unit_sphere() const
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> random_range(0.f, 1.0f);

		vec3 point;

		do
		{
			point = 2.0* vec3(random_range(gen), random_range(gen), random_range(gen)) - vec3(1, 1, 1);
		} while (dot(point, point) >= 1.0);

		return point;
	};
};