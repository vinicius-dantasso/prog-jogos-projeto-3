
#include "Wolf.h"
#include "GeoWars.h"
#include "Random.h"
#include "Scripts.h"

Wolf::Wolf(float posX, float posY)
{
	tile = new TileSet("Resources/wolf_sheet.png",64,64,7,56);
	anim = new Animation(tile, 0.12f, true);

	stateTimer = new Timer();
	attackTimer = new Timer();

	uint SeqIdleL[6] = { 0,1,2,3,4,5 };
	uint SeqMoveL[5] = { 7,8,9,10,11 };
	uint SeqHitL[4] = { 14,15,16,17 };
	uint SeqDieL[7] = { 21,22,23,24,25,26,27 };

	uint SeqIdleR[6] = { 34,33,32,31,30,29 };
	uint SeqMoveR[5] = { 41,40,39,38,37 };
	uint SeqHitR[4] = { 48,47,46,45 };
	uint SeqDieR[7] = { 55,54,53,52,51,50,49 };

	anim->Add(WOLFIDLEL, SeqIdleL, 6);
	anim->Add(WOLFMOVEL, SeqMoveL, 5);
	anim->Add(WOLFHITL, SeqHitL, 4);
	anim->Add(WOLFDEADL, SeqDieL, 7);

	anim->Add(WOLFIDLER, SeqIdleR, 6);
	anim->Add(WOLFMOVER, SeqMoveR, 5);
	anim->Add(WOLFHITR, SeqHitR, 4);
	anim->Add(WOLFDEADR, SeqDieR, 7);

	spd = 80.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	type = ENEMY;
	state = CHOOSESTATE;
	animState = WOLFIDLEL;

	attackTimer->Start();
	stateTimer->Start();
	stateTime = 1.0f;

	BBox(new Rect(-16,-8,16,32));
	MoveTo(posX, posY);
}

Wolf::~Wolf()
{
	delete tile;
	delete anim;
	delete stateTimer;
	delete attackTimer;
}

void Wolf::OnCollision(Object* obj)
{
	if (obj->Type() == FLOOR)
	{
		vSpd = 0.0f;
		MoveTo(x, obj->Y() - 52);
		onGround = true;
	}

	if (obj->Type() == RIGHTWALL)
	{
		if (x >= obj->X() + 24)
			MoveTo(obj->X() + 64, y);
		else
			MoveTo(x, obj->Y() - 58);
	}

	if (obj->Type() == LEFTWALL)
	{
		if (x <= obj->X() - 24)
			MoveTo(obj->X() - 64, y);
		else
			MoveTo(x, obj->Y() - 58);
	}

	if (obj->Type() == HITBOX && !hit)
	{
		hit = true;
		life -= 1;
		float dir = Scripts::point_direction(GeoWars::player->X(), GeoWars::player->Y(), obj->X(), obj->Y());
		knockBackDir = dir;
		knockBackSpd = 200.0f;
		state = ENEMYHIT;

		if (GeoWars::player->X() < x)
			animState = WOLFHITL;
		else
			animState = WOLFHITR;
	}

	if (obj->Type() == PLAYER)
	{
		hitPlayer = true;
		attackTimer->Reset();
	}
}

void Wolf::Update()
{
	if (!hit && life > 0 && stateTimer->Elapsed(stateTime))
	{
		RandF range{ 1.0f,3.0f };
		stateTime = range.Rand();
		stateTimer->Reset();
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}

	if (!hit && !hitPlayer && life > 0 && Scripts::distance_to_object(this, GeoWars::player) <= 350.0f)
		state = ATTACKING;

	if (hitPlayer && attackTimer->Elapsed(1.5f))
		hitPlayer = false;

	switch (state)
	{
	case CHOOSESTATE:
		ChooseState();
		break;

	case WANDERING:
		Wandering();

		if (destX > x)
			animState = WOLFMOVER;
		else
			animState = WOLFMOVEL;

		if (onDestiny && destX > x)
			animState = WOLFIDLER;
		else if (onDestiny && destX < x)
			animState = WOLFIDLEL;

		break;
		
	case STOPPED:
		hSpd = 0.0f;
		vSpd = 0.0f;

		if (destX > x)
			animState = WOLFIDLER;
		else
			animState = WOLFIDLEL;

		break;

	case ATTACKING:
		Attacking();

		if (destX > x)
			animState = WOLFMOVER;
		else
			animState = WOLFMOVEL;

		break;

	case ENEMYHIT:
		Hit();
		break;
	}

	if (life <= 0)
	{
		if (x > GeoWars::player->X())
			animState = WOLFDEADL;
		else
			animState = WOLFDEADR;

		if (stateTimer->Elapsed(0.2f))
			GeoWars::scene->Delete(this, MOVING);
	}

	vSpd += grav;

	Translate(hSpd * gameTime, vSpd * gameTime);

	anim->Select(animState);
	anim->NextFrame();
}

void Wolf::Draw()
{
	anim->Draw(x, y, Layer::UPPER);
}

void Wolf::Hit()
{
	knockBackSpd = Scripts::lerp(knockBackSpd, 0.0f, 0.3f);
	hSpd = Scripts::lengthdir_x(knockBackSpd, knockBackDir);

	if (stateTimer->Elapsed(0.3f))
	{
		state = STOPPED;
		stateTimer->Reset();
		stateTime = 1.0f;
		hit = false;
	}
}