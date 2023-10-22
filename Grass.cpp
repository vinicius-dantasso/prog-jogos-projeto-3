
#include "Grass.h"
#include "Random.h"

Grass::Grass(float posX, float posY)
{
	RandI type{ 1,3 };

	switch (type.Rand())
	{
	case 1: sprite = new Sprite("Resources/grass_1.png"); break;
	case 2: sprite = new Sprite("Resources/grass_2.png"); break;
	case 3: sprite = new Sprite("Resources/grass_3.png"); break;
	}

	MoveTo(posX, posY);
}

Grass::~Grass()
{
	delete sprite;
}

void Grass::Draw()
{
	sprite->Draw(x,y,z);
}