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
    
    void Update();                      // atualização
    void Draw();                        // desenho
}; 
// ---------------------------------------------------------------------------------

#endif