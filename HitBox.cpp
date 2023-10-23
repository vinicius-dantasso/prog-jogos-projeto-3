
#include "HitBox.h"
#include "GeoWars.h"

HitBox::HitBox(float posX, float posY)
{
	timer = new Timer();
	timer->Start();

	type = HITBOX;
	BBox(new Circle(26));
	MoveTo(posX, posY);
}

HitBox::~HitBox(){}

void HitBox::Update()
{
	if (timer->Elapsed(0.2f))
		GeoWars::scene->Delete(this, STATIC);
}