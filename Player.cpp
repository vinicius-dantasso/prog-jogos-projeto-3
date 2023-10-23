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
#include <random>

// -------------------------------------------------------------------------------

std::random_device rd;
std::mt19937 mt(rd());

// -------------------------------------------------------------------------------

Player::Player()
{

    playerSfx = new Audio();
    playerSfx->Add(ATT1, "Resources/attack1.wav");
    playerSfx->Add(ATT2, "Resources/attack2.wav");
    playerSfx->Add(ATT3, "Resources/attack3.wav");
    playerSfx->Add(ATT4, "Resources/attack4.wav");
    playerSfx->Add(JMP1, "Resources/jump1.wav");
    playerSfx->Add(JMP2, "Resources/jump2.wav");
    playerSfx->Add(HRT1, "Resources/hurt1.wav");
    playerSfx->Add(HRT2, "Resources/hurt2.wav");
    playerSfx->Add(MOV1, "Resources/footstep01.wav");
    playerSfx->Add(MOV2, "Resources/footstep03.wav");

    playerSfx->Volume(MOV1, 0.1f);
    playerSfx->Volume(MOV2, 0.1f);

    tile = new TileSet("Resources/player_sheet.png", 90, 70, 8, 96);
    anim = new Animation(tile, 0.12f, true);

    attackTimer = new Timer();
    sfxTimer = new Timer();

    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    uint SeqIdleRight[6] = { 0,1,2,3,4,5 };
    uint SeqIdleLeft[6] = { 55,54,53,52,51,50 };
    uint SeqMoveLeft[8] = { 71,70,69,68,67,66,65,64 };
    uint SeqMoveRight[8] = { 16,17,18,19,20,21,22,23 };
    uint SeqJumpRight[6] = { 24,25,26,27,28,29 };
    uint SeqJumpLeft[6] = { 79,78,77,76,75,74 };
    uint SeqAttackRight[6] = { 8,9,10,11,12,13 };
    uint SeqAttackLeft[6] = { 63,62,61,60,59,58 };

    anim->Add(PLAYERIDLER, SeqIdleRight, 6);
    anim->Add(PLAYERMOVER, SeqMoveRight, 8);
    anim->Add(PLAYERMOVEL, SeqMoveLeft, 8);
    anim->Add(PLAYERIDLEL, SeqIdleLeft, 6);
    anim->Add(PLAYERJUMPR, SeqJumpRight, 6);
    anim->Add(PLAYERJUMPL, SeqJumpLeft, 6);
    anim->Add(PLAYERATTACKR, SeqAttackRight, 6);
    anim->Add(PLAYERATTACKL, SeqAttackLeft, 6);

    BBox(new Rect(-10,-16,10,35));
    MoveTo((window->CenterX() / 2.0f) - 50.0f, window->CenterY());

    type = PLAYER;
    animState = PLAYERIDLER;
    state = PLAYERMOVE;

    lastDir = 0;
    life = 3;

    grav = 30.0f;
    onGround = false;
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete tile;
    delete anim;
    delete font;
    delete attackTimer;
    delete playerSfx;
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

    if (obj->Type() == RIGHTWALL)
    {
        if (x >= obj->X() + 24)
            MoveTo(obj->X() + 32, y);
        else
            MoveTo(x, obj->Y() - 58);
    }

    if (obj->Type() == LEFTWALL)
    {
        if (x <= obj->X() - 24)
            MoveTo(obj->X() - 32, y);
        else
            MoveTo(x, obj->Y() - 58);
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
    {
        
        //efeito sonoro de movimentação
        if(sfxTimer->Elapsed(0.25f)){
            sfxTimer->Reset();
            int rand = mt() % 2;
            playerSfx->Play(rand + 8);
        }

        spd = 280.0f;
    }else
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

        int rand = mt() % 2;
        playerSfx->Play(rand + 4);

        onGround = false;
        jump = 0;
    }

    hSpd = Scripts::lengthdir_x(spd, spdDir);
}

// -------------------------------------------------------------------------------

void Player::PlayerAttack()
{
    //toca som apenas uma vez
    if(!soundOn){
        soundOn = true;
        int rand = mt() % 4;
        playerSfx->Play(rand);
    }


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


    if (attackTimer->Elapsed(0.5f)){
        state = PLAYERMOVE;
        soundOn = false;
    }
}

// -------------------------------------------------------------------------------

void Player::PlayerHit()
{
    //flag soundOn usada como placeholder
    if (!soundOn) {
        int rand = mt() % 2;
        playerSfx->Play(rand + 6);
    }
}

// -------------------------------------------------------------------------------

void Player::UpdateCamera()
{
    Camera::x = Scripts::clamp(this->X() - window->Width() / 2.0f, 0, (2560 * 3) - window->Width());
}

// -------------------------------------------------------------------------------
