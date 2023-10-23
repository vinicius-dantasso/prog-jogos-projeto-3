
#ifndef _TRIGGER_H_
#define _TRIGGER_H_

#include "Object.h"
#include "Types.h"

class Trigger : public Object
{
public:
	Trigger(float posX, float posY);

	void Update();
	void Draw();
};

inline void Trigger::Update(){}

inline void Trigger::Draw(){}

#endif // !_TRIGGER_H_
