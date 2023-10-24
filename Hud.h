
#ifndef _HUD_H_
#define _HUD_H_

#include "Object.h"
#include "Sprite.h"

class Hud : public Object
{
private:
	Sprite* hearts;

public:
	Hud();
	~Hud();

	void Update();
	void Draw();
};

inline void Hud::Update(){}

#endif // !_HUD_H_
