#pragma once

#include "vec3.h"
#include <minmax.h>

void write_colour(std::ostream &out, colour pixel_colour)
{
	out << static_cast<int>(255.99 * pixel_colour.x()) << ' '
		<< static_cast<int>(255.99 * pixel_colour.y()) << ' '
		<< static_cast<int>(255.99 * pixel_colour.z()) << '\n';
}


