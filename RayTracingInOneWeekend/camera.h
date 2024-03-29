#pragma once
#include "vec3.h"
#include "ray.h"

class camera
{
public:
	camera(
		point3 lookfrom,
		point3 lookat,
		vec3 vup,
		double vfov,
		double aspect_ratio,
		double aperture,
		double focus_distance,
		double defocus_disk_R
		)
		: 
		defocus_disk_radius(defocus_disk_R)
	{
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		origin = lookfrom;
		horizontal = focus_distance * viewport_width * u;
		vertical = focus_distance * viewport_height * v;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_distance * w;

		lens_radius = aperture / 2;
	}

	ray get_ray(double s, double t) const
	{
		vec3 rd = lens_radius * random_in_disk(defocus_disk_radius);
		vec3 offset = u * rd.x() + v * rd.y();

		return ray(
			origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset);
	};

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
	double defocus_disk_radius;
};