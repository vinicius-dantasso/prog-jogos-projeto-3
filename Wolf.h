
#ifndef _WOLF_H_
#define _WOLF_H_

#include "Enemy.h"
#include "Audio.h"
#include "Timer.h"

enum WolfAnim { WOLFIDLEL, WOLFIDLER, WOLFMOVEL, WOLFMOVER, WOLFHITL, WOLFHITR, WOLFDEADL, WOLFDEADR };

enum WolfSfx { WOLFMOV1, WOLFMOV2, WOLFATT1, WOLFATT2, WOLFDIE};

class Wolf : public Enemy
{
private:
	Audio * sfx;
	Timer * sfxTimer;

	int frames = 0;
	int maxFrames = 120;

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
