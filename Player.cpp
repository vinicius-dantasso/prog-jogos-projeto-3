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
#include "Scripts.h"
#include "Camera.h"
#include <string>

// -------------------------------------------------------------------------------

Player::Player()
{
    tile = new TileSet("Resources/player2.png", 90, 70, 8, 48);
    anim = new Animation(tile, 0.12f, true);

    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    uint SeqIdleRight[6] = { 0,1,2,3,4,5 };
    uint SeqMoveRight[8] = { 16,17,18,19,20,21,22,23 };

    anim->Add(PLAYERIDLER, SeqIdleRight, 6);
    anim->Add(PLAYERMOVER, SeqMoveRight, 8);

    BBox(new Rect(-10,-16,10,35));
    MoveTo(window->CenterX() / 2.0f, window->CenterY());

    type = PLAYER;
    animState = PLAYERIDLER;
    state = PLAYERMOVE;

    grav = 300.0f;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete tile;
    delete anim;
    delete font;
}

// -------------------------------------------------------------------------------

void Player::Update()
{
    switch (state)
    {
        case PLAYERMOVE:
            PlayerMovement();
        break;
    }

    Translate(hSpd * gameTime, vSpd * gameTime);

    anim->Select(animState);
    anim->NextFrame();

    UpdateCamera();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    anim->Draw(x - Camera::x, y - Camera::y, Layer::UPPER);
}

// -------------------------------------------------------------------------------

void Player::PlayerMovement()
{
    int hDir = -window->KeyDown('A') + window->KeyDown('D');
    int vDir = -window->KeyDown('W') + window->KeyDown('S');
    int jump = window->KeyPress(VK_SPACE);

    float spdDir = Scripts::point_direction(x, y, x + hDir, y + vDir);

    if (hDir != 0 || vDir != 0)
        spd = 180.0f;
    else
        spd = 0.0f;

    switch (hDir)
    {
    case 1:
        lastDir = 1;
        animState = PLAYERMOVER;
        break;

    case -1:
        lastDir = -1;
        animState = PLAYERMOVER;
        break;

    default:
        if (lastDir == 1)
            animState = PLAYERIDLER;
        else if(lastDir == -1)
            animState = PLAYERIDLER;
    }

    hSpd = Scripts::lengthdir_x(spd, spdDir);
    vSpd = Scripts::lengthdir_y(spd, spdDir);
}

void Player::PlayerAttack()
{

}

void Player::PlayerHit()
{

}

void Player::UpdateCamera()
{
    Camera::x = Scripts::clamp(this->X() - window->Width() / 2.0f, 0, (2560 * 3) - window->Width());
}
