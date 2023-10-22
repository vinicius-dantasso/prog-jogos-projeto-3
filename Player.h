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
#include "Font.h"

// ---------------------------------------------------------------------------------

enum PlayerAnim {PLAYERIDLEL, PLAYERIDLER, PLAYERMOVEL, PLAYERMOVER};
enum PlayerState {PLAYERMOVE, PLAYERHIT, PLAYERATTACK};

class Player : public Object
{
private:
    TileSet* tile;
    Animation* anim;
    Font* font;

    float spd;
    float hSpd;
    float vSpd;
    float grav;
    
    int lastDir;

public:
    uint state;
    uint animState;

    Player();                           // construtor
    ~Player();                          // destrutor

    void PlayerMovement();
    void PlayerAttack();
    void PlayerHit();
    void UpdateCamera();
    
    void Update();                      // atualização
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif