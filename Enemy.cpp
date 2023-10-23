
#include "Enemy.h"
#include "GeoWars.h"
#include <random>
using namespace std;

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> difference(1, 10);
uniform_int_distribution<int> choose(0, 1);
uniform_int_distribution<int> timerRange(1, 5);
uniform_int_distribution<int> coinsToDrop(0, 3);

Enemy::Enemy()
{
	// vida inicial
	life = 3;

	// inicia hit
	hit = false;

	// inicia variáveis de hit
	knockBackDir = 0.0f;
	knockBackSpd = 0.0f;
}

Enemy::~Enemy()
{}

void Enemy::ChooseState()
{
	nextState = choose(mt);

	if (nextState == WANDERING)
	{
		state = WANDERING;
		destX = DistX();
		destY = DistY();
	}
	else
		state = STOPPED;
}

void Enemy::Wandering()
{
	if (Scripts::distance_to_point(x, y, destX, destY) > 10.0f)
	{
		float dir = Scripts::point_direction(x, y, destX, destY);
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);
	}
	else
	{
		float dir = Scripts::point_direction(x, y, destX, destY);
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);
	}

	if (Scripts::distance_to_point(x, y, destX, destY) < 1.0f)
	{
		hSpd = 0.0f;
		vSpd = 0.0f;
	}
}

void Enemy::Attacking()
{
	destX = GeoWars::player->X();
	destY = GeoWars::player->Y();

	float dir = Scripts::point_direction(x, y, destX, destY);
	hSpd = Scripts::lengthdir_x(spd, dir);
	vSpd = Scripts::lengthdir_y(spd, dir);

	if (Scripts::distance_to_object(this, GeoWars::player) >= 500.0f)
	{
		hSpd = 0.0f;
		vSpd = 0.0f;
		state = CHOOSESTATE;
	}
}

int Enemy::DistX()
{
	uniform_int_distribution<int> distX(-50, 50);
	return x + distX(mt);
}

int Enemy::DistY()
{
	uniform_int_distribution<int> distY(-50, 50);
	return y + distY(mt);
}

int Enemy::TimerRange()
{
	return timerRange(mt);
}

void Enemy::Hit()
{

}

void Enemy::WallCollision(Object* obj)
{
	float deltaX = obj->X() - x;
	float deltaY = obj->Y() - y;

	// Verifica se a colisão é mais horizontal ou vertical
	if (abs(deltaX) > abs(deltaY))
	{
		// Colisão mais horizontal, ajusta horizontalmente
		if (x + tile->TileWidth() / 2.0f >= obj->X() - 16 && x - tile->TileWidth() / 2.0f <= obj->X() - 16)
			MoveTo(obj->X() - 32, y);
		else if (x - tile->TileWidth() / 2.0f <= obj->X() + 16 && x + tile->TileWidth() / 2.0f >= obj->X() - 16)
			MoveTo(obj->X() + 32, y);
	}
	else
	{
		// Colisão mais vertical, ajusta verticalmente
		if (y - tile->TileHeight() / 2.0f <= obj->Y() + 16 && y + tile->TileHeight() / 2.0f >= obj->Y() + 16)
			MoveTo(x, obj->Y() - 32);
		else if (y + tile->TileHeight() / 2.0f >= obj->Y() - 16 && y - tile->TileHeight() / 2.0f <= obj->Y() - 16)
			MoveTo(x, obj->Y() + 32);
	}
}

void Enemy::Update()
{}

void Enemy::Draw()
{}