
#include "Summon.h"
#include "GeoWars.h"
#include "Scripts.h"

Summon::Summon(float posX, float posY)
{
	tile = new TileSet("Resources/summon_sheet2.png", 96, 96, 4, 16);
	anim = new Animation(tile, 0.1f, true);
	timer = new Timer();

	uint SeqSpawn[6] = { 0,1,2,3,4,5 };
	uint SeqDeath[5] = { 6,7,8,9,10 };
	uint SeqIdle[4] = { 12,13,14,15 };

	anim->Add(SUSPAWN, SeqSpawn, 6);
	anim->Add(SUDEATH, SeqDeath, 5);
	anim->Add(SUIDLE, SeqIdle, 4);
	anim->Add(SUCHASE, SeqIdle, 4);

	type = ENEMY;
	state = SUSPAWN;

	timer->Start();

	spd = 40.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	frequency = 0.03f;
	amplitude = 30;
	time = 0;

	BBox(new Rect(-16, -16, 16, 16));
	MoveTo(posX, posY);
}

Summon::~Summon()
{
	delete tile;
	delete anim;
	delete timer;
}

void Summon::OnCollision(Object* obj)
{
	if (obj->Type() == HITBOX)
	{
		timer->Start();
		state = SUDEATH;
	}
}

void Summon::Update()
{
	float dir = Scripts::point_direction(x, y, GeoWars::player->X(), GeoWars::player->Y());

	switch (state)
	{
	case SUSPAWN:
		if (timer->Elapsed(1.0f))
		{
			state = SUIDLE;
			timer->Reset();
		}
		break;

	case SUIDLE:

		if (timer->Elapsed(1.0f))
		{
			state = SUCHASE;
			timer->Stop();
		}

		vSpd = sin(time * frequency) * amplitude;
		time++;

		break;

	case SUCHASE:
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);
		break;

	case SUDEATH:

		if (timer->Elapsed(1.0f))
			GeoWars::scene->Delete(this, MOVING);

		break;
	}

	Translate(hSpd * gameTime, vSpd * gameTime);

	anim->Select(state);
	anim->NextFrame();
}

void Summon::Draw()
{
	anim->Draw(x, y, Layer::UPPER);
}