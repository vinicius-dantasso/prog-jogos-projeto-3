/**********************************************************************************
// GeoWars (Arquivo de Cabe�alho)
// 
// Cria��o:     23 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Demonstra��o da vers�o final do motor
//
**********************************************************************************/

#ifndef _GEOWARS_H_
#define _GEOWARS_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "World.h"
#include "Hud.h"
#include "Sprite.h"
#include "Font.h"

// ------------------------------------------------------------------------------

enum ObjectIds { PLAYER, FLOOR, RIGHTWALL, LEFTWALL, HITBOX, ENEMYHITBOX, ENEMY, TRIGGER };

// ------------------------------------------------------------------------------

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

// ------------------------------------------------------------------------------

class GeoWars : public Game
{
private:
    Background* backg = nullptr;   // pano de fundo
    Sprite* logo = nullptr;
    Font* font = nullptr;
    bool viewBBox = false;          // visualiza��o das bouding boxes

public:
    static Player * player;         // nave controlada pela jogador
    static Audio * audio;           // sitema de �udio
    static Scene * scene;           // cena do jogo
    static World * builder;         // construtor de mapa
    static Hud * hud;
    static bool canPlay;

    int frames = 0;
    int maxFrames = 25;

    bool canDraw;

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif