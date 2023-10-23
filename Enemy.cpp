
#include "Enemy.h"
#include "Random.h"
#include "Scripts.h"
#include "GeoWars.h"

Enemy::Enemy()
{
	life = 3;

	grav = 30.0f;
	knockBackDir = 0.0f;
	knockBackSpd = 0.0f;

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
	destX = GeoWars::player->X();

	float dir = Scripts::point_direction(x, y, destX, y);
	hSpd = Scripts::lengthdir_x(spd, dir);

	if (Scripts::distance_to_object(this, GeoWars::player) >= 300.0f)
	{
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}
}

void Enemy::Hit()
{
	
}