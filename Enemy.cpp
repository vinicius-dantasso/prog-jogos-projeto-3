
#include "Enemy.h"
#include "Random.h"
#include "Scripts.h"

Enemy::Enemy()
{
	life = 3;
	grav = 30.0f;
	hit = false;
	onGround = false;
	onDestiny = false;
}

Enemy::~Enemy()
{

}

void Enemy::ChooseState()
{
	RandI choose{ 0,1 };
	RandF destination{ x - 50.0f, x + 50.0f };

	nextState = choose.Rand();

	if (nextState == WANDERING)
	{
		state = WANDERING;
		destX = destination.Rand();
	}
	else
		state = STOPPED;
}

void Enemy::Wandering()
{
	if (Scripts::distance_to_point(x, y, destX, y) > 10.0f)
	{
		onDestiny = false;
		float dir = Scripts::point_direction(x, y, destX, y);
		hSpd = Scripts::lengthdir_x(spd, dir);
	}
	else
	{
		onDestiny = false;
		float dir = Scripts::point_direction(x, y, destX, y);
		hSpd = Scripts::lengthdir_x(spd, dir);
	}

	if (Scripts::distance_to_point(x, y, destX, y) < 1.0f)
	{
		hSpd = 0.0f;
		onDestiny = true;
	}
}

void Enemy::Attacking()
{

}

void Enemy::Hit()
{

}