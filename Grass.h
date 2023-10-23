
#ifndef _GRASS_H_
#define _GRASS_H_

#include "Object.h"
#include "Sprite.h"

class Grass : public Object
{
private:
	Sprite* sprite;

public:
	Grass(float posX, float posY);
	~Grass();

	void Update();
	void Draw();
};

inline void Grass::Update(){}

#endif // !_GRASS_H_
