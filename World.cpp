#include "World.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

World::World(const char* path)
{
	unsigned char* image = stbi_load(path, &width, &height, &channels, 3);

	for (int xx = 14; xx < width; xx++)
	{

		for (int yy = 0; yy < height; yy++)
		{

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				
			}

		}

	}

	stbi_image_free(image);
}