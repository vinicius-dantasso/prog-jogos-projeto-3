/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#ifndef _GEOWARS_PLAYER_H_
#define _GEOWARS_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Animation.h"
#include "Timer.h"
#include "Font.h"
#include "HitBox.h"

// ---------------------------------------------------------------------------------

enum PlayerAnim {
    PLAYERIDLEL,
    PLAYERIDLER,
    PLAYERMOVEL,
    PLAYERMOVER,
    PLAYERJUMPR,
    PLAYERJUMPL,
    PLAYERATTACKL,
    PLAYERATTACKR,
    PLAYERHITL,
    PLAYERHITR
};
enum PlayerState {PLAYERMOVE, PLAYERHIT, PLAYERATTACK};

class Player : public Object
{
private:
    TileSet* tile;
    Animation* anim;
    Timer* attackTimer;
    Font* font;
    HitBox* hitbox;

    float spd;
    float hSpd;
    float vSpd;
    float grav;
    float knockBackDir;
    float knockBackSpd;
    
    int lastDir;
    int life;
    int frames = 0;
    int maxFrames = 15;

    bool onGround;
    bool hit;

public:
    uint state;
    uint animState;

    Player();                           // construtor
    ~Player();                          // destrutor

    void PlayerMovement();
    void PlayerAttack();
    void PlayerHit();

    bool isHit();
    
    void OnCollision(Object* obj);
    void Update();                      // atualização
    void Draw();                        // desenho
};

inline bool Player::isHit()
{ return hit; }

// ---------------------------------------------------------------------------------

#endif