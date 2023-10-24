
#ifndef _HIT_BOX_H_
#define _HIT_BOX_H_

#include "Object.h"
#include "Types.h"
#include "Timer.h"

class HitBox : public Object
{
private:
	Timer* timer;

public:
	HitBox(float posX, float posY, uint types);
	~HitBox();

	void Update();
	void Draw();
};

inline void HitBox::Draw(){}

#endif // !_HIT_BOX_H_
