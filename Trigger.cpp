
#include "Trigger.h"
#include "GeoWars.h"

Trigger::Trigger(float posX, float posY)
{
	type = TRIGGER;
	BBox(new Rect(-24, -24, 24, 24));
	MoveTo(posX, posY);
}