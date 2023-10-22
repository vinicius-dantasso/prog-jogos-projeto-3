#include "Floor.h"
#include "GeoWars.h"

Floor::Floor(float posX, float posY)
{
	sprite = new Sprite("Resources/floor2.png");

	type = FLOOR;
	BBox(new Rect(-24, -24, 24, 24));
	MoveTo(posX, posY);
}

Floor::~Floor()
{
	delete sprite;
}