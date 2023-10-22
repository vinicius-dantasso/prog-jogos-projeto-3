#include "World.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GeoWars.h"
#include "Floor.h"
#include "Lamp.h"

World::World(const char* path)
{
	unsigned char* image = stbi_load(path, &width, &height, &channels, 3);

	for (int xx = 0; xx < width; xx++)
	{

		for (int yy = 0; yy < height; yy++)
		{

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// GRAMA
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, GRASS);
				GeoWars::scene->Add(floor, STATIC);
			}
			
			else if (image[3 * (xx + (yy * width))] == 230
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// PAREDE ESQUERDA
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, WALLESQ);
				GeoWars::scene->Add(floor, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 210
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// PAREDE DIREITA
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, WALLDIR);
				GeoWars::scene->Add(floor, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 190
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// SOLO
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, SOIL);
				GeoWars::scene->Add(floor, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 204
				&& image[3 * (xx + (yy * width)) + 1] == 81
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// LAMPARINA
				Lamp* lamp = new Lamp(xx * 48.0f, yy * 44.5f);
				GeoWars::scene->Add(lamp, STATIC);
			}

		}

	}

	stbi_image_free(image);
}