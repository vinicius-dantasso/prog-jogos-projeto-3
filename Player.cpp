/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "GeoWars.h"

// -------------------------------------------------------------------------------

Player::Player()
{
    tile = new TileSet("Resources/player_sheet.png", 120, 80, 12, 192);
    anim = new Animation(tile, 0.12f, true);

    uint SeqIdleRight[10] = { 0,1,2,3,4,5,6,7,8,9 };

    anim->Add(PLAYERIDLER, SeqIdleRight, 10);

    BBox(new Rect(-12,-38,12,38));
    MoveTo(game->CenterX(), game->CenterY());
    type = PLAYER;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete tile;
    delete anim;
}

// -------------------------------------------------------------------------------

void Player::Update()
{
    anim->Select(PLAYERIDLER);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    anim->Draw(x, y, Layer::UPPER);
}


// -------------------------------------------------------------------------------
