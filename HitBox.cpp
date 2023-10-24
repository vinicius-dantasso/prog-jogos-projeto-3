
#include "HitBox.h"
#include "GeoWars.h"

HitBox::HitBox(float posX, float posY, uint types)
{
	timer = new Timer();
	timer->Start();

	switch (types)
	{
	case HITBOX:
		type = types;
		BBox(new Circle(26));
		break;

	case ENEMYHITBOX:
		type = types;
		BBox(new Circle(48));
		break;
	}
	
	MoveTo(posX, posY);
}

HitBox::~HitBox(){}

void HitBox::Update()
{
	if (timer->Elapsed(0.1f) && type == HITBOX)
		GeoWars::scene->Delete(this, STATIC);
	else if(timer->Elapsed(3.0f))
		GeoWars::scene->Delete(this, STATIC);
}