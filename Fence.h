
#ifndef _FENCE_H_
#define _FENCE_H_

#include "Object.h"
#include "Sprite.h"

class Fence : public Object
{
private:
	Sprite* sprite;

public:
	Fence(float posX, float posY);
	~Fence();

	void Update();
	void Draw();
};

inline void Fence::Draw()
{
	sprite->Draw(x, y, z);
}

inline void Fence::Update(){}

#endif // !_FENCE_H_
