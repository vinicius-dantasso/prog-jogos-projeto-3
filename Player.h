/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define a classe jogador
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
#include "Audio.h"

// ---------------------------------------------------------------------------------

enum PlayerAnim {
    PLAYERIDLEL,
    PLAYERIDLER,
    PLAYERMOVEL,
    PLAYERMOVER,
    PLAYERJUMPR,
    PLAYERJUMPL,
    PLAYERATTACKL,
    PLAYERATTACKR
};
enum PlayerState {PLAYERMOVE, PLAYERHIT, PLAYERATTACK};

enum PlayerSFC {
    ATT1,
    ATT2,
    ATT3,
    ATT4,
    JMP1,
    JMP2,
    HRT1,
    HRT2,
    MOV1,
    MOV2
};

class Player : public Object
{
private:

    Audio * playerSfx;
    Timer* sfxTimer;
    bool soundOn;

    TileSet* tile;
    Animation* anim;
    Timer* attackTimer;
    Font* font;
    HitBox* hitbox;

    float spd;
    float hSpd;
    float vSpd;
    float grav;
    
    int lastDir;
    int life;

    bool onGround;

public:
    uint state;
    uint animState;

    Player();                           // construtor
    ~Player();                          // destrutor

    void PlayerMovement();
    void PlayerAttack();
    void PlayerHit();
    void UpdateCamera();
    
    void OnCollision(Object* obj);
    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif