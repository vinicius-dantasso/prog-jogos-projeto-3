#include "World.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GeoWars.h"
#include "Floor.h"
#include "Lamp.h"
#include "Grass.h"
#include "Fence.h"
#include "Wolf.h"
#include "Boss.h"
#include "Trigger.h"

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
				// CHÃO
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, GRASS);
				GeoWars::scene->Add(floor, STATIC);
			}
			
			if (image[3 * (xx + (yy * width))] == 230
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// PAREDE ESQUERDA
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, WALLESQ);
				GeoWars::scene->Add(floor, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 210
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// PAREDE DIREITA
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, WALLDIR);
				GeoWars::scene->Add(floor, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 190
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// SOLO
				Floor* floor = new Floor(xx * 48.0f, yy * 48.0f, SOIL);
				GeoWars::scene->Add(floor, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 204
				&& image[3 * (xx + (yy * width)) + 1] == 81
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// LAMPARINA
				Lamp* lamp = new Lamp(xx * 48.0f, yy * 44.5f);
				GeoWars::scene->Add(lamp, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 178
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// GRAMA
				Grass* grass = new Grass(xx * 48.0f, yy * 50.2f);
				GeoWars::scene->Add(grass, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 135
				&& image[3 * (xx + (yy * width)) + 2] == 71
				)
			{
				// CERCA
				Fence* fence = new Fence(xx * 48.0f, yy * 48.5f);
				GeoWars::scene->Add(fence, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 0
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// LOBO
				Wolf* wolf = new Wolf(xx * 48.0f, yy * 47.0f);
				GeoWars::scene->Add(wolf, MOVING);
			}

			if (image[3 * (xx + (yy * width))] == 0
				&& image[3 * (xx + (yy * width)) + 1] == 38
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// BOSS
				Boss* boss = new Boss(xx * 48.0f, yy * 47.0f);
				GeoWars::scene->Add(boss, MOVING);
			}

			if (image[3 * (xx + (yy * width))] == 163
				&& image[3 * (xx + (yy * width)) + 1] == 38
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// TRIGGER
				Trigger* trigger = new Trigger(xx * 48.0f, yy * 48.0f);
				GeoWars::scene->Add(trigger, STATIC);
			}

		}

	}

	stbi_image_free(image);
}