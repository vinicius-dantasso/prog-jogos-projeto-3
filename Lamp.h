
#ifndef _LAMP_H_
#define _LAMP_H_

#include "Object.h"
#include "Sprite.h"
#include "Particles.h"

class Lamp : public Object
{
private:
	Sprite* sprite;
	Particles* fire;

public:
	Lamp(float posX, float posY);
	~Lamp();

	void Update();
	void Draw();
};

#endif // !_LAMP_H_
