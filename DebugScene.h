#pragma once

#include "Game.h"
#include "Player.h"
#include "Scene.h"
#include "Font.h"

class DebugScene : public Game
{

private:
	
	static Player * player;

	Font * fonte;

public:
	static Scene * scene;

	// Herdado por meio de Game
	void Init() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};