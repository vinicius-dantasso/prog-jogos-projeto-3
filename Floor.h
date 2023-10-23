
#ifndef _FLOOR_H_

#include "Object.h"
#include "Sprite.h"
#include "Types.h"

enum FloorType {GRASS, WALLDIR, WALLESQ, SOIL};

class Floor : public Object
{
private:
	Sprite* sprite;

public:
	Floor(float posX, float posY, uint imageType);
	~Floor();

	void Update();
	void Draw();
};

inline void Floor::Draw()
{
	sprite->Draw(x, y, Layer::BACK);
}

inline void Floor::Update(){}

#endif // !_FLOOR_H_
