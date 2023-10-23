
#include "Hud.h"
#include "GeoWars.h"

Hud::Hud()
{
	hearts = new Sprite("Resources/Heart.png");
}

Hud::~Hud()
{
	delete hearts;
}

void Hud::Draw()
{
	for (int i = 1; i <= GeoWars::player->Life(); i++)
		hearts->Draw((game->viewport.left + 30) + ((i - 1) * 48), game->viewport.top + 40, Layer::FRONT);
}