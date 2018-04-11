#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <random>
#include <string>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"





vec3 color(const ray& r, hitable* world, int depth)
{
	hit_record rec;

	if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec))
	{
		ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.ptr_mat->scatter(r, rec, attenuation, scattered))
		{
			return  attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
		
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		//Lerp color formula (1-t)*start_value + t * end_value
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}



int main()
{
	std::cout << "main on" << std::endl;

	int nx = 1024;
	int ny = 600;
	int ns = 100;

	std::string file_name = "firstImage.ppm";
	std::ofstream ostrm(file_name);
	ostrm << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 origin(0.0, 0.0, 0.0);
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 inc_hor(4.0, 0, 0);
	vec3 inc_ver(0, 2.0, 0);

	hitable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, std::unique_ptr<material>( new lambertian(vec3(0.8, 0.3, 0.3))));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, std::unique_ptr<material>( new lambertian(vec3(0.8,0.8,0.0))));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, std::unique_ptr<material>( new metal(vec3(0.8, 0.6, 0.2))));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, std::unique_ptr<material>( new metal(vec3(0.8, 0.8, 0.8))));
	hitable* world = new hitable_list(list, 4);

	camera cam;

	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<> random_range(0.f, 1.0f);


	for (int j = ny-1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + random_range(gen)) / float(nx);
				float v = float(j + random_range(gen)) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 point = r.point_at_parameter(2.0);
				col += color(r, world, 5);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			/*vec3 color(float(i) / float(nx), float(j) / float(ny), 0.2); */
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			ostrm << ir << " " << ig << " " << ib << "\n";
		}
	}

	std::cout << "Process finished" << std::endl;
	getchar();
	delete world;
	return 0;
}





//DIFFUSE

//vec3 random_in_unit_sphere()
//{
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::uniform_real_distribution<> random_range(0.f, 1.0f);
//
//	vec3 point;
//
//	do
//	{
//		point = 2.0* vec3(random_range(gen), random_range(gen), random_range(gen)) - vec3(1, 1, 1);
//	} while (dot(point, point) >= 1.0);
//
//	return point;
//}
//
//
//vec3 color(const ray& r, hitable* world)
//{
//	hit_record rec;
//
//	if (world->hit(r, 0.0, FLT_MAX, rec))
//	{
//		vec3 target = rec.point + rec.normal + random_in_unit_sphere();
//		return 0.5 * color(ray(rec.point, target - rec.point), world);
//	}
//	else
//	{
//		vec3 unit_direction = unit_vector(r.direction());
//		float t = 0.5 * (unit_direction.y() + 1.0);
//		//Lerp color formula (1-t)*start_value + t * end_value
//		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//	}
//}
//
//
//
//int main()
//{
//	std::cout << "main on" << std::endl;
//
//	int nx = 800;
//	int ny = 600;
//	int ns = 100;
//
//	std::string file_name = "firstImage.ppm";
//	std::ofstream ostrm(file_name);
//	ostrm << "P3\n" << nx << " " << ny << "\n255\n";
//
//	vec3 origin(0.0, 0.0, 0.0);
//	vec3 lower_left_corner(-2.0, -1.0, -1.0);
//	vec3 inc_hor(4.0, 0, 0);
//	vec3 inc_ver(0, 2.0, 0);
//
//	hitable *list[2];
//	list[0] = new sphere(vec3(0, 0, -1), 0.5);
//	list[1] = new sphere(vec3(0, -100.5, -1), 100);
//	hitable* world = new hitable_list(list, 2);
//	camera cam;
//
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::uniform_real_distribution<> random_range(0.f, 1.0f);
//
//
//	for (int j = ny - 1; j >= 0; j--)
//	{
//		for (int i = 0; i < nx; i++)
//		{
//			vec3 col(0, 0, 0);
//			for (int s = 0; s < ns; s++)
//			{
//				float u = float(i + random_range(gen)) / float(nx);
//				float v = float(j + random_range(gen)) / float(ny);
//				ray r = cam.get_ray(u, v);
//				vec3 point = r.point_at_parameter(2.0);
//				col += color(r, world);
//			}
//			col /= float(ns);
//			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
//			/*vec3 color(float(i) / float(nx), float(j) / float(ny), 0.2); */
//			int ir = int(255.99*col[0]);
//			int ig = int(255.99*col[1]);
//			int ib = int(255.99*col[2]);
//			ostrm << ir << " " << ig << " " << ib << "\n";
//		}
//	}
//
//	std::cout << "Process finished" << std::endl;
//	getchar();
//	delete list;
//	delete world;
//	return 0;
//}