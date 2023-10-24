
#ifndef _SUMMON_H_
#define _SUMMON_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"
#include "Timer.h"

enum SummonState {SUSPAWN, SUIDLE, SUDEATH, SUCHASE};

class Summon : public Object
{
private:
	TileSet* tile;
	Animation* anim;
	Timer* timer;

	float spd;
	float hSpd;
	float vSpd;
	float frequency;

	int amplitude;
	int time;

	bool hit = false;

public:
	uint state;

	Summon(float posX, float posY);
	~Summon();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_SUMMON_H_
