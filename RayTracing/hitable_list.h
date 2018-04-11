#pragma once

#include "hitable.h"

class hitable_list: public hitable
{
public:
	hitable_list() {}
	hitable_list(hitable ** l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record&rec) const;
	int list_size;
	hitable **list;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool has_hit_anything = false;
	double temp_closest = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, temp_closest, temp_rec))
		{
			has_hit_anything = true;
			temp_closest = temp_rec.t;
			rec = temp_rec;
		}
	}

	return has_hit_anything;
}

