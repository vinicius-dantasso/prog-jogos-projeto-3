#include "Wolf.h"
#include "GeoWars.h"
#include "Scripts.h"

/*enum WolfAnim { WOLFIDLEL, WOLFIDLER, WOLFHITL, WOLFHITR, WOLFRUNR, WOLFRUNL, WOLFDEATHR, WOLFDEATHL };
*/
Wolf::Wolf(float posX, float posY) {

	//tile = new TileSet("Resources/wolf_sheet.png", 90, 70, 7, 28);
	tile = new TileSet("Resources/wolf_sheet.png", 4, 7);
	anim = new Animation(tile, 0.25f, true);
	timer = new Timer();

	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	uint idleright[6] = {0, 1, 2, 3, 4 ,5};
	uint runright[5] = {7, 8, 9, 10, 11};
	uint hitright[4] = {14, 15, 16, 17};
	uint deathr[7] = {21, 22, 23,24, 25, 26, 27};

	anim->Add(WOLFIDLER, idleright, 6);
	anim->Add(WOLFRUNR, runright, 5);
	anim->Add(WOLFHITR, hitright, 4);
	anim->Add(WOLFDEATHR, deathr, 7);

	spd = 80.0f;
	hSpd = 0.0f;
	vSpd = 0.0f;

	type = ENEMY;
	state = CHOOSESTATE;
	animState = WOLFIDLER;

	timer->Start();
	time = 1.0f;

	frames = 0;
	maxFrames = 10;

	BBox(new Rect(-24, -16, 24, 16));
	MoveTo(posX, posY);
}

Wolf::~Wolf() {
	delete tile;
	delete anim;
	delete timer;
	delete font;
}

void Wolf::Update() {

	if (timer->Elapsed(time))
	{
		time = TimerRange();
		timer->Reset();
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}

	if (!hit && Scripts::distance_to_object(this, GeoWars::player) <= 350.0f)
		state = ATTACKING;

	if (!hit && GeoWars::player->X() > x) {
		animState = WOLFIDLEL;
	}
	else if (!hit && GeoWars::player->X() < x) {
		animState = WOLFIDLER;
	}

	switch (state)
	{
	case CHOOSESTATE:
		ChooseState();
		break;

	case WANDERING:
		Wandering();
		break;

	case STOPPED:
		hSpd = 0.0f;
		vSpd = 0.0f;
		break;

	case ATTACKING:
		Attacking();
		break;

	case ENEMYHIT:
		Hit();
		break;
	}

	Translate(hSpd * gameTime, vSpd * gameTime);

	anim->Select(animState);
	anim->NextFrame();
}

void Wolf::Draw() {
	anim->Draw(x, y, Layer::UPPER);
}

void Wolf::OnCollision(Object * obj) {
	
}

void Wolf::Hit() {

}