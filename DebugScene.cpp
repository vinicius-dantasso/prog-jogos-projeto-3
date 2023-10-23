#include "DebugScene.h"
#include "Resources.h"
#include "Engine.h"  

Scene * DebugScene::scene = nullptr;
Player * DebugScene::player = nullptr;

void DebugScene::Init()
{
    scene = new Scene();
    fonte = new Font("Resources/Tahoma14.png");
    player = new Player();
    player->MoveTo(window->CenterX(), window->CenterY());
	scene->Add(player, MOVING);
}

void DebugScene::Update()
{
    if (window->KeyDown(VK_ESCAPE))
        window->Close();
}

void DebugScene::Draw()
{
    //fonte->Draw(window->CenterX(), window->CenterY(), "testando 1 2 3");
    scene->Draw();
}

void DebugScene::Finalize()
{
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1280, 720);
    //engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Debug");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(false);
    //engine->graphics->VSync(true);

    // cria o jogo
    Game* game = new DebugScene();

    // configura o jogo
    game->Size(2560, 720);

    // inicia execução
    engine->Start(game);

    // destrói motor e encerra jogo
    delete engine;
    return 0;
}