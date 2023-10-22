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
    tile = new TileSet("Resources/player_sheet.png", 90, 70, 8, 96);
    anim = new Animation(tile, 0.12f, true);

    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    uint SeqIdleRight[6] = { 0,1,2,3,4,5 };
    uint SeqIdleLeft[6] = { 55,54,53,52,51,50 };
    uint SeqMoveLeft[8] = { 71,70,69,68,67,66,65,64 };
    uint SeqMoveRight[8] = { 16,17,18,19,20,21,22,23 };

    anim->Add(PLAYERIDLER, SeqIdleRight, 6);
    anim->Add(PLAYERMOVER, SeqMoveRight, 8);
    anim->Add(PLAYERMOVEL, SeqMoveLeft, 8);
    anim->Add(PLAYERIDLEL, SeqIdleLeft, 6);

    BBox(new Rect(-10,-16,10,35));
    MoveTo(window->CenterX() / 2.0f, window->CenterY());

    type = PLAYER;
    animState = PLAYERIDLER;
    state = PLAYERMOVE;

    grav = 20.0f;
    onGround = false;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete tile;
    delete anim;
    delete font;
}

// -------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    if (obj->Type() == FLOOR)
    {
        vSpd = 0.0f;
        MoveTo(x, obj->Y() - 58);
        if (state != PLAYERATTACK)
            state = PLAYERMOVE;
        onGround = true;
    }
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
    anim->Draw(x, y, Layer::UPPER);
}

// -------------------------------------------------------------------------------

void Player::PlayerMovement()
{
    int hDir = -window->KeyDown(VK_LEFT) + window->KeyDown(VK_RIGHT);
    int jump = window->KeyPress(VK_UP);

    float spdDir = Scripts::point_direction(x, y, x + hDir, y);

    if (hDir != 0)
        spd = 280.0f;
    else
        spd = 0.0f;

    if(onGround)
    {
        switch (hDir)
        {
        case 1:
            lastDir = 1;
            animState = PLAYERMOVER;
            break;

        case -1:
            lastDir = -1;
            animState = PLAYERMOVEL;
            break;

        default:
            if (lastDir == 1)
                animState = PLAYERIDLER;
            else if (lastDir == -1)
                animState = PLAYERIDLEL;
        }
    }

    if(!onGround)
        vSpd += grav;

    if (jump && onGround)
    {
        vSpd -= 350.0f;
        onGround = false;
        animState = PLAYERJUMP;
        jump = 0;
    }

    hSpd = Scripts::lengthdir_x(spd, spdDir);
}

// -------------------------------------------------------------------------------

void Player::PlayerAttack()
{

}

// -------------------------------------------------------------------------------

void Player::PlayerHit()
{

}

// -------------------------------------------------------------------------------

void Player::UpdateCamera()
{
    Camera::x = Scripts::clamp(this->X() - window->Width() / 2.0f, 0, (2560 * 3) - window->Width());
}

// -------------------------------------------------------------------------------
