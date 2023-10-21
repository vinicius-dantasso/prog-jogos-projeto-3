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

// ---------------------------------------------------------------------------------

enum PlayerAnim {PLAYERIDLEL, PLAYERIDLER};

class Player : public Object
{
private:
    TileSet* tile;
    Animation* anim;

    float spd;
    float hSpd;
    float vSpd;

public:
    Player();                           // construtor
    ~Player();                          // destrutor
    
    void Update();                      // atualiza��o
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif