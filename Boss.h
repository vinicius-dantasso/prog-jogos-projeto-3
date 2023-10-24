
#ifndef _BOSS_H_
#define _BOSS_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"
#include "Timer.h"
#include "Random.h"
#include "Audio.h"

enum BossAnim {BOSSIDLE,BOSSSPAWN,BOSSDEATH,BOSSPRE,BOSSATTACK,BOSSSUMMON};
enum BossState {APPEARANCE,BOSSSTOP,BOSSATT,BOSSPREATT,BOSSSUMM, BOSSDEAD};
enum Bosssf { BOSSSPWN, BOSSLGHT1, BOSSLGHT2, BOSSHT1, BOSSHT2};

class Boss : public Object
{
private:

	Audio* sfx;
	Timer* sfxTimer;

	TileSet* tile;
	Animation* anim;
	Timer* animTimer;
	Timer* summonTimer;
	
	float vSpd;
	float frequency;
	float tempo;

	RandI rand{ 1,10 };
	RandF posX{ x - 10,x + 10 };

	int rng;
	int amplitude;
	int time;
	int life;
	int frames = 0;
	int maxFrames = 90;

	bool canHit;

public:
	uint state;
	uint nextState;
	uint animState;

	Boss(float posX, float posY);
	~Boss();

	void BossAttack();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_BOSS_H_
