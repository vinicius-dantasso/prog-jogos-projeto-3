
#ifndef _BOSS_H_
#define _BOSS_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"
#include "Timer.h"
#include "Random.h"

enum BossAnim {BOSSIDLE,BOSSSPAWN,BOSSDEATH,BOSSPRE,BOSSATTACK,BOSSSUMMON};
enum BossState {APPEARANCE,BOSSSTOP,BOSSATT,BOSSPREATT,BOSSSUMM};

class Boss : public Object
{
private:
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

public:
	uint state;
	uint nextState;
	uint animState;

	Boss(float posX, float posY);
	~Boss();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_BOSS_H_
