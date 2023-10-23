
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"
#include "Timer.h"

enum EnemyState {WANDERING, STOPPED, ATTACKING, CHOOSESTATE, ENEMYHIT};

class Enemy : public Object
{
public:
	TileSet* tile;
	Animation* anim;
	Timer* stateTimer;

	uint state;
	uint nextState;

	float spd;
	float hSpd;
	float vSpd;
	float destX;
	float destY;
	float grav;
	float stateTime;

	int life;

	bool hit;
	bool onGround;
	bool onDestiny;

	Enemy();
	virtual ~Enemy();

	virtual void ChooseState();
	virtual void Wandering();
	virtual void Attacking();
	virtual void Hit();

	void Update();
	void Draw();
};

inline void Enemy::Update(){}

inline void Enemy::Draw(){}

#endif // !_ENEMY_H_
