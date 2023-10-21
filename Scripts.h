
#ifndef _SCRIPTS_H_
#define _SCRIPTS_H_

#include "Object.h"

class Scripts
{
public:
	static float lengthdir_x(float len, float dir);
	static float lengthdir_y(float len, float dir);
	static float point_direction(float x1, float y1, float x2, float y2);
	static float distance_to_object(Object* instance, Object* destiny);
	static float distance_to_point(float x1, float y1, float x2, float y2);
	static float lerp(float start, float end, float t);
	static int sign(float value);
};

#endif // !_SCRIPTS_H_
