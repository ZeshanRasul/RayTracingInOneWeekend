#include "string"
#include <iostream>
#include "vec3.h"
#include "colour.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.getOrigin() - center;
	auto a = r.getDirection().length_squared();
	auto half_b = dot(oc, r.getDirection());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;
	
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-half_b - sqrt(discriminant)) / a;
	};
}

colour ray_colour(ray& r)
{
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * colour(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = unit_vector(r.getDirection());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main()
{

	// Image

	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	
	// Camera

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	int focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "Scanlines remaining: " << j << "\nPercent remaining: " << (double(j) / image_height) * 100 << "%\n" << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			colour final_colour = ray_colour(r);	

			write_colour(std::cout, final_colour);

		}
	}

	std::cerr << "\nDone.\n";

}