
#include "Boss.h"
#include "GeoWars.h"
#include "Scripts.h"
#include "Summon.h"
#include "HitBox.h"

#include "Random"

RandI random = RandI(0,1);

Boss::Boss(float posX, float posY)
{

	sfx = new Audio();
	sfx->Add(BOSSSPWN, "Resources/BossSpawn.wav");
	sfx->Add(BOSSLGHT1, "Resources/BossLaught1.wav");
	sfx->Add(BOSSLGHT2, "Resources/BossLaught2.wav");
	sfx->Add(BOSSHT1, "Resources/BossHit1.wav");
	sfx->Add(BOSSHT2, "Resources/BossHit2.wav");
	sfxTimer = new Timer();
	sfxTimer->Start();

	tile = new TileSet("Resources/death_sheet3.png",300,300,10,60);
	anim = new Animation(tile, 0.1f, true);

	animTimer = new Timer();
	summonTimer = new Timer();
	tempo = 1.0f;

	uint SeqSpawn[18] = { 17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };
	uint SeqDespawn[18] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
	uint SeqIdle[9] = { 18,19,20,21,22,23,24,25,26 };
	uint SeqPreAtt[10] = { 27,28,29,30,31,32,33,34,35,36 };
	uint SeqAtt[15] = { 37,38,39,40,41,42,43,44,45,46,47,48,48,50,51 };
	uint SeqSummon[4] = { 52,53,54,55 };

	anim->Add(BOSSSPAWN, SeqSpawn, 18);
	anim->Add(BOSSDEATH, SeqDespawn, 18);
	anim->Add(BOSSIDLE, SeqIdle, 9);
	anim->Add(BOSSPRE, SeqPreAtt, 10);
	anim->Add(BOSSATTACK, SeqAtt, 15);
	anim->Add(BOSSSUMMON, SeqSummon, 4);

	state = APPEARANCE;

	frequency = 0.03f;
	amplitude = 50;
	time = 0;

	life = 800;

	BBox(new Rect(-16, -50, 50, 50));
	MoveTo(posX, posY - 48.0f);

}

Boss::~Boss()
{
	delete sfx;
	delete anim;
	delete tile;
	delete animTimer;
	delete summonTimer;
}

void Boss::OnCollision(Object* obj)
{
	if (state == BOSSSTOP && obj->Type() == HITBOX)
		life -= 1;
}

void Boss::Update()
{
	if(GeoWars::player->Triggered())
	{
		if (life <= 0)
		{
			state = BOSSDEAD;
			animState = BOSSDEATH;
		}

		switch (state)
		{
		case APPEARANCE:

			sfx->Play(BOSSSPWN);
			animState = BOSSSPAWN;
			state = BOSSSTOP;
			animTimer->Start();
			break;

		case BOSSSTOP:

			if(sfxTimer->Elapsed(0.5f)){
				int rand = random.Rand();
				sfx->Play(rand + 1);
				sfxTimer->Reset();
			}

			if (animTimer->Elapsed(1.0f))
				animState = BOSSIDLE;

			if (animTimer->Elapsed(4.0f))
			{
				state = BOSSPREATT;
				animState = BOSSPRE;
				animTimer->Stop();
			}

			break;

		case BOSSPREATT:

			frames++;
			if(frames >= maxFrames)
			{
				frames = 0;
				rng = rand.Rand();

				if (rng < 7)
				{
					animState = BOSSATTACK;
					state = BOSSATT;
					animTimer->Reset();
					canHit = true;
				}
				else
				{
					animState = BOSSSUMMON;
					state = BOSSSUMM;
					animTimer->Reset();
					summonTimer->Start();
				}
			}

			break;

		case BOSSATT:

			if (animTimer->Elapsed(5.5f))
			{
				animState = BOSSIDLE;
				state = BOSSSTOP;
				animTimer->Reset();
			}

			if (canHit)
			{
				int rand = random.Rand();
				sfx->Play(rand + 3);
				
				canHit = false;
				BossAttack();
			}

			break;

		case BOSSSUMM:

			if (animTimer->Elapsed(10.0f))
			{
				animState = BOSSIDLE;
				state = BOSSSTOP;
				animTimer->Reset();
				summonTimer->Stop();
			}

			if (summonTimer->Elapsed(2.0f))
			{
				summonTimer->Reset();
				Summon* summon = new Summon(x - 32.0f, y - 120.0f);
				GeoWars::scene->Add(summon, MOVING);
			}

			break;

		case BOSSDEAD:

			frames++;
			if (frames >= maxFrames)
				GeoWars::scene->Delete(this, MOVING);

			break;
		}

		vSpd = sin(time * frequency) * amplitude;
		time++;

		Translate(0.0f, vSpd * gameTime);

		anim->Select(animState);
		anim->NextFrame();
	}
}

void Boss::Draw()
{
	if (GeoWars::player->Triggered())
		anim->Draw(x, y, Layer::UPPER);
}

void Boss::BossAttack()
{
	HitBox* hitbox = new HitBox(x - 42.0f, y, ENEMYHITBOX);
	GeoWars::scene->Add(hitbox, STATIC);
}