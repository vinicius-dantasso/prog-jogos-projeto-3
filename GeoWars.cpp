/**********************************************************************************
// GeoWars (C�digo Fonte)
// 
// Cria��o:     23 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Demonstra��o da vers�o final do motor
//
**********************************************************************************/

#include "Resources.h"
#include "GeoWars.h"
#include "Engine.h"

// ------------------------------------------------------------------------------

Player * GeoWars::player  = nullptr;
Audio  * GeoWars::audio   = nullptr;
Scene  * GeoWars::scene   = nullptr;
World  * GeoWars::builder = nullptr;
Hud    * GeoWars::hud     = nullptr;

// ------------------------------------------------------------------------------

void GeoWars::Init() 
{
    // cria sistema de �udio
    audio = new Audio();
    audio->Add(THEME, "Resources/Theme.wav");
    audio->Add(FIRE, "Resources/Fire.wav");
    audio->Add(HITWALL, "Resources/Hitwall.wav");
    audio->Add(EXPLODE, "Resources/Explode.wav");
    audio->Add(START, "Resources/Start.wav");

    // ajusta volumes
    audio->Volume(FIRE, 0.2f);
    audio->Volume(START, 0.8f);

    // carrega/incializa objetos
    backg = new Background("Resources/background_layer_1.png", "Resources/background_layer_2.png", "Resources/background_layer_3.png");
    player  = new Player();
    scene   = new Scene();
    builder = new World("Resources/debugMap.png");
    hud = new Hud();

    // adiciona objetos na cena
    scene->Add(player, MOVING);
    scene->Add(hud, STATIC);

    // ----------------------
    // inicializa a viewport
    // ----------------------

    // calcula posi��o para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    // inicializa viewport para o centro do mundo
    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();
}

// ------------------------------------------------------------------------------

void GeoWars::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena e calcula colis�es
    scene->Update();
    scene->CollisionDetection();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // --------------------
    // atualiza a viewport
    // --------------------

    viewport.left = player->X() - window->CenterX();
    viewport.right = player->X() + window->CenterX();
    viewport.top = player->Y() - window->CenterY();
    viewport.bottom = player->Y() + window->CenterY();

    if (viewport.left < 0)
    {
        viewport.left = 0;
        viewport.right = window->Width();
    }
    else if (viewport.right > game->Width())
    {
        viewport.left = game->Width() - window->Width();
        viewport.right = game->Width();
    }

    if (viewport.top < 0)
    {
        viewport.top = 0;
        viewport.bottom = window->Height();
    }
    else if (viewport.bottom > game->Height())
    {
        viewport.top = game->Height() - window->Height();
        viewport.bottom = game->Height();
    }
} 

// ------------------------------------------------------------------------------

void GeoWars::Draw()
{
    // desenha pano de fundo
    backg->Draw(viewport);

    // desenha a cena
    scene->Draw();

    // desenha bounding box
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void GeoWars::Finalize()
{
    delete audio;
    delete scene;
    delete backg;
    delete builder;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine * engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1152, 648);
    //engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("GeoWars");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(false);
    engine->graphics->VSync(true);

    // cria o jogo
    Game * game = new GeoWars();

    // configura o jogo
    game->Size(5750, 648);
    
    // inicia execu��o
    engine->Start(game);

    // destr�i motor e encerra jogo
    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------