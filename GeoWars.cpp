/**********************************************************************************
// GeoWars (Código Fonte)
// 
// Criação:     23 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Demonstração da versão final do motor
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

// ------------------------------------------------------------------------------

void GeoWars::Init() 
{
    // cria sistema de áudio
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
    player  = new Player();
    scene   = new Scene();
    builder = new World("Resources/debugMap.png");

    // adiciona objetos na cena (sem colisão)
    scene->Add(player, STATIC);
}

// ------------------------------------------------------------------------------

void GeoWars::Update()
{
    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena e calcula colisões
    scene->Update();
    scene->CollisionDetection();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;
} 

// ------------------------------------------------------------------------------

void GeoWars::Draw()
{
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
    
    // inicia execução
    engine->Start(game);

    // destrói motor e encerra jogo
    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------