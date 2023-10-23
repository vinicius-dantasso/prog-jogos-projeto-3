#ifndef _WOLF_H_
#define _WOLF_H_

#include "Enemy.h"

enum WolfAnim { WOLFIDLEL, WOLFIDLER, WOLFHITL, WOLFHITR, WOLFRUNR, WOLFRUNL, WOLFDEATHR, WOLFDEATHL };

class Wolf : public Enemy
{
private:
	float		  time;
	int			  frames;
	int			  maxFrames;

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