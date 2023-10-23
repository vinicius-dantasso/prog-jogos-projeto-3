
#ifndef _WOLF_H_
#define _WOLF_H_

#include "Enemy.h"

enum WolfAnim { WOLFIDLEL, WOLFIDLER, WOLFMOVEL, WOLFMOVER, WOLFHITL, WOLFHITR, WOLFDEADL, WOLFDEADR };

class Wolf : public Enemy
{
public:
	uint animState;

	Wolf(float posX, float posY);
	~Wolf();

	void Hit();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_WOLF_H_
