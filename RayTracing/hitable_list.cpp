#include "hitable_list.h"



hitable_list::hitable_list()
{



hitable_list::~hitable_list()
{
}

bool hitable_list::hit(const ray & r, float t_min, float t_max, hit_record & rec) const
{
	return false;
}
