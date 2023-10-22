#include "Floor.h"
#include "GeoWars.h"

Floor::Floor(float posX, float posY, uint imageType)
{
	switch (imageType)
	{
	case GRASS:
		sprite = new Sprite("Resources/floor.png");
		type = FLOOR;
		BBox(new Rect(-24, -24, 24, 24));
		break;

	case WALLDIR:
		sprite = new Sprite("Resources/floor_corner_right.png");
		type = RIGHTWALL;
		BBox(new Rect(-24, -24, 24, 24));
		break;

	case WALLESQ:
		sprite = new Sprite("Resources/floor_corner_left.png");
		type = LEFTWALL;
		BBox(new Rect(-24, -24, 24, 24));
		break;

	case SOIL:
		sprite = new Sprite("Resources/floor_down.png");
		break;
	}

	MoveTo(posX, posY);
}

Floor::~Floor()
{
	delete sprite;
}