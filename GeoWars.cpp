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
Hud    * GeoWars::hud     = nullptr;
bool     GeoWars::canPlay = false;

// ------------------------------------------------------------------------------

void GeoWars::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(THEME, "Resources/Goblin-Mischief.wav");
    audio->Add(FIRE, "Resources/Fire.wav");
    audio->Add(HITWALL, "Resources/Hitwall.wav");
    audio->Add(EXPLODE, "Resources/Explode.wav");
    audio->Add(START, "Resources/Start.wav");

    // ajusta volumes
    audio->Volume(FIRE, 0.2f);
    audio->Volume(START, 0.8f);
    audio->Volume(THEME, 0.5f);

    audio->Play(THEME, true);

    // carrega/incializa objetos
    backg = new Background("Resources/background_layer_1.png", "Resources/background_layer_2.png", "Resources/background_layer_3.png");
    logo = new Sprite("Resources/Logo.png");
    player  = new Player();
    scene   = new Scene();
    builder = new World("Resources/map.png");
    hud = new Hud();
    font = new Font("Resources/m5x7.png");
    font->Spacing(85);

    // adiciona objetos na cena
    scene->Add(player, MOVING);
    scene->Add(hud, STATIC);

    // ----------------------
    // inicializa a viewport
    // ----------------------

    // calcula posição para manter viewport centralizada
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

    // atualiza cena e calcula colisões
    scene->Update();
    scene->CollisionDetection();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_RETURN))
        canPlay = true;

    if (!canDraw)
    {
        frames++;
        if (frames >= maxFrames)
        {
            frames = 0;
            canDraw = true;
        }
    }

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

    // desenha logo
    if(!canPlay)
        logo->Draw(window->CenterX(), window->CenterY() - 60.0f, Layer::FRONT, 0.2f);

    Color white(1.0f, 1.0f, 1.0f, 1.0f);
    Color black(0.0f, 0.0f, 0.0f, 1.0f);

    if (canDraw && !canPlay)
    {
        font->Draw(window->CenterX() - 110.0f, window->CenterY() + 30.0f, "> PRESS ENTER <", black, Layer::LOWER, 0.2f);
        font->Draw(window->CenterX() - 111.0f, window->CenterY() + 30.0f, "> PRESS ENTER <", white, Layer::UPPER, 0.2f);

        frames++;
        if (frames >= maxFrames)
        {
            frames = 0;
            canDraw = false;
        }
    }

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
    delete logo;
    delete font;
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
    game->Size(12000, 648);
    
    // inicia execução
    engine->Start(game);

    // destrói motor e encerra jogo
    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------