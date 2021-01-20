#include "FreeImage.h"
#include "string"
#include <iostream>
#include "vec3.h"
#include "colour.h"

int main()
{
	std::string outputFilename = "Raytracer.png";
	int width = 256;
	int height = 256;
	unsigned char* pixels = new unsigned char[size_t(width) * height * 3];


	for (int j = height - 1; j >= 0; j--)
	{
		std::cout << "Scanlines remaining: " << j << "\nPercent remaining: " << (float(j) / height) * 100 << "%\n";
		for (int i = 0; i < width - 1; i++)
		{

			unsigned char col[3];

			float r = float(i) / (width - 1);
			float g = float(j) / (height - 1);
			float b = 0.25;

			colour final_colour(r, g, b);
			
			write_colour(col, final_colour);

			memcpy(&pixels[((j * width) + i) * 3], &col, 3);
		}
	}

	std::cout << "\nDone.\n";

	FreeImage_Initialise();
	FIBITMAP* img = FreeImage_ConvertFromRawBits((BYTE*)pixels, width, height, 3 * width, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, img, outputFilename.c_str(), 0);
	FreeImage_DeInitialise();
}