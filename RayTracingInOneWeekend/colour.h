#pragma once

#include "vec3.h"
#include <minmax.h>

unsigned char* write_colour(unsigned char* col, colour pixel_colour)
{
	col[0] = unsigned char(min(255.99 * pixel_colour.z(), 255.0f));
	col[1] = unsigned char(min(255.99 * pixel_colour.y(), 255.0f));
	col[2] = unsigned char(min(255.99 * pixel_colour.x(), 255.0f));

	return col;
}


