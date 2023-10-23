
#include "Fence.h"
#include "Random.h"

Fence::Fence(float posX, float posY)
{
	RandI type{ 1,2 };

	switch (type.Rand())
	{
	case 1: sprite = new Sprite("Resources/fence_1.png"); break;
	case 2: sprite = new Sprite("Resources/fence_2.png"); break;
	}

	MoveTo(posX, posY);
}

Fence::~Fence()
{
	delete sprite;
}