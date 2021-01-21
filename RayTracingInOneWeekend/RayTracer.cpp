#include "string"
#include <iostream>
#include "vec3.h"
#include "colour.h"
#include "ray.h"

colour ray_colour(const Ray& r)
{
	vec3 unit_direction = unit_vector(r.getDirection());
	auto t = 0.5 * (unit_direction.y() + 1.0);
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
	auto lower_left_corner = vec3(origin - horizontal / 2.0 - vertical / 2.0 - vec3(0, 0, focal_length));

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)
	{
		std::cerr << "Scanlines remaining: " << j << "\nPercent remaining: " << (double(j) / image_height) * 100 << "%\n" << std::flush;
		for (int i = 0; i < image_width - 1; i++)
		{

			auto u = double(i) / (image_width - 1.0);
			auto v = double(j) / (image_height - 1.0);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			colour final_colour = ray_colour(r);

			write_colour(std::cout, final_colour);

		}
	}

	std::cerr << "\nDone.\n";

}