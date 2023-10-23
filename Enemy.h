
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Types.h"
#include "Object.h"
#include "Scripts.h"
#include "Animation.h"
#include "Font.h"
#include "Timer.h"

enum EnemyState { WANDERING, STOPPED, ATTACKING, CHOOSESTATE, ENEMYHIT };

class Enemy : public Object
{
public:
	TileSet* tile;
	Animation* anim;
	Timer* timer;
	Font* font;

	uint	state;
	uint	nextState;
	float	spd;
	float	hSpd;
	float	vSpd;
	float	destX;
	float	destY;
	float	knockBackDir;
	float	knockBackSpd;
	int		life;
	bool	hit;

	Enemy();
	virtual ~Enemy();

	virtual void ChooseState();
	virtual void Wandering();
	virtual void Attacking();
	virtual void Hit();

	int DistX();
	int DistY();
	int TimerRange();

	void Update();
	void Draw();
	void WallCollision(Object* obj);
};

#endif // !_ENEMY_H_