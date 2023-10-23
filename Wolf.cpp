
#include "Wolf.h"
#include "GeoWars.h"
#include "Random.h"

Wolf::Wolf(float posX, float posY)
{
	tile = new TileSet("Resources/wolf_sheet.png",64,64,7,56);
	anim = new Animation(tile, 0.12f, true);
	stateTimer = new Timer();

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
}

void Wolf::OnCollision(Object* obj)
{
	if (obj->Type() == FLOOR)
	{
		vSpd = 0.0f;
		MoveTo(x, obj->Y() - 50);
		onGround = true;
	}

	if (obj->Type() == RIGHTWALL)
	{
		if (x >= obj->X() + 24)
			MoveTo(obj->X() + 32, y);
		else
			MoveTo(x, obj->Y() - 58);
	}

	if (obj->Type() == LEFTWALL)
	{
		if (x <= obj->X() - 24)
			MoveTo(obj->X() - 32, y);
		else
			MoveTo(x, obj->Y() - 58);
	}
}

void Wolf::Update()
{
	if (stateTimer->Elapsed(stateTime))
	{
		RandF range{ 1.0f,3.0f };
		stateTime = range.Rand();
		stateTimer->Reset();
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}

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
		break;
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