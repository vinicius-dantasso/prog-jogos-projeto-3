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
#include <string>

// -------------------------------------------------------------------------------

Player::Player()
{
    tile = new TileSet("Resources/player_sheet.png", 90, 70, 8, 96);
    anim = new Animation(tile, 0.12f, true);

    attackTimer = new Timer();

    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    uint SeqIdleRight[6] = { 0,1,2,3,4,5 };
    uint SeqMoveRight[8] = { 16,17,18,19,20,21,22,23 };
    uint SeqJumpRight[6] = { 24,25,26,27,28,29 };
    uint SeqAttackRight[6] = { 8,9,10,11,12,13 };
    uint SeqHitRight[3] = { 40,41,42 };

    uint SeqIdleLeft[6] = { 55,54,53,52,51,50 };
    uint SeqMoveLeft[8] = { 71,70,69,68,67,66,65,64 };
    uint SeqJumpLeft[6] = { 79,78,77,76,75,74 };
    uint SeqAttackLeft[6] = { 63,62,61,60,59,58 };
    uint SeqHitLeft[3] = { 95,94,93 };

    anim->Add(PLAYERIDLER, SeqIdleRight, 6);
    anim->Add(PLAYERMOVER, SeqMoveRight, 8); 
    anim->Add(PLAYERJUMPR, SeqJumpRight, 6);  
    anim->Add(PLAYERATTACKR, SeqAttackRight, 6);   
    anim->Add(PLAYERHITR, SeqHitRight, 3);

    anim->Add(PLAYERMOVEL, SeqMoveLeft, 8);
    anim->Add(PLAYERIDLEL, SeqIdleLeft, 6);
    anim->Add(PLAYERJUMPL, SeqJumpLeft, 6);
    anim->Add(PLAYERATTACKL, SeqAttackLeft, 6);
    anim->Add(PLAYERHITL, SeqAttackLeft, 3);

    BBox(new Rect(-10,-16,10,35));
    MoveTo((window->CenterX() / 2.0f) - 50.0f, window->CenterY());

    type = PLAYER;
    animState = PLAYERIDLER;
    state = PLAYERMOVE;

    lastDir = 0;
    life = 5;

    grav = 30.0f;
    onGround = false;
    hit = false;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete tile;
    delete anim;
    delete font;
    delete attackTimer;
}

// -------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    if (obj->Type() == FLOOR)
    {
        vSpd = 0.0f;
        MoveTo(x, obj->Y() - 60);
        if (state != PLAYERATTACK)
            state = PLAYERMOVE;
        onGround = true;
    }

    if (obj->Type() == RIGHTWALL)
    {
        vSpd = 0.0f;
        if (x >= obj->X() + 24)
            MoveTo(obj->X() + 32, y);
        else
            MoveTo(x, obj->Y() - 58);
        onGround = true;
    }

    if (obj->Type() == LEFTWALL)
    {
        vSpd = 0.0f;
        if (x <= obj->X() - 24)
            MoveTo(obj->X() - 32, y);
        else
            MoveTo(x, obj->Y() - 58);
        onGround = true;
    }

    if (obj->Type() == ENEMY)
    {
        hit = true;
        life -= 1;
        float dir = Scripts::point_direction(obj->X(), obj->Y(), x, y - 10.0f);
        knockBackDir = dir;
        knockBackSpd = 200.0f;
        state = PLAYERHIT;

        switch (lastDir)
        {
        case 1:
            animState = PLAYERHITR;
            break;

        case -1:
            animState = PLAYERHITL;
        }
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

    case PLAYERATTACK:
        PlayerAttack();
        break;

    case PLAYERHIT:
        PlayerHit();
        break;
    }

    Translate(hSpd * gameTime, vSpd * gameTime);

    anim->Select(animState);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    Color white(1.0f, 1.0f, 1.0f, 1.0f);
    std::string str = std::to_string(anim->Frame());

    //font->Draw(x,y-30,str,white,Layer::FRONT,0.3f);
    anim->Draw(x, y, Layer::UPPER);
}

// -------------------------------------------------------------------------------

void Player::PlayerMovement()
{
    int hDir = -window->KeyDown(VK_LEFT) + window->KeyDown(VK_RIGHT);
    int jump = window->KeyPress(VK_UP);
    int attack = window->KeyPress(VK_SPACE);

    float spdDir = Scripts::point_direction(x, y, x + hDir, y);

    if (hDir != 0)
        spd = 280.0f;
    else
        spd = 0.0f;

    if(onGround)
    {
        // Caso aperte ataque, mude de estado
        if (attack)
        {
            attack = 0;
            spd = 0.0f;
            attackTimer->Start();
            state = PLAYERATTACK;
        }

        // Controla as animações quando estiver em solo
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
    else
    {
        // Controla as animações quando estiver no ar
        switch (lastDir)
        {
        case 1:
            animState = PLAYERJUMPR;
            break;

        case -1:
            animState = PLAYERJUMPL;
            break;
        }
    }

    // Efeito da gravidade
    vSpd += grav;

    // Pulo
    if (jump && onGround)
    {
        vSpd -= 550.0f;
        onGround = false;
        jump = 0;
    }

    hSpd = Scripts::lengthdir_x(spd, spdDir);
}

// -------------------------------------------------------------------------------

void Player::PlayerAttack()
{
    switch (lastDir)
    {
    case 1:
        animState = PLAYERATTACKR;
        hitbox = new HitBox(x + 32, y);
        GeoWars::scene->Add(hitbox, STATIC);
        break;

    case -1:
        animState = PLAYERATTACKL;
        hitbox = new HitBox(x - 32, y);
        GeoWars::scene->Add(hitbox, STATIC);
        break;
    }

    if (attackTimer->Elapsed(0.5f))
        state = PLAYERMOVE;
}

// -------------------------------------------------------------------------------

void Player::PlayerHit()
{
    knockBackSpd = Scripts::lerp(knockBackSpd, 0.0f, 0.3f);
    hSpd = Scripts::lengthdir_x(knockBackSpd, knockBackDir);
    vSpd = Scripts::lengthdir_y(knockBackSpd, knockBackDir);

    vSpd += grav;

    frames++;
    if (frames >= maxFrames)
    {
        state = PLAYERMOVE;
        hit = false;
        frames = 0;
    }
}

// -------------------------------------------------------------------------------
