
#include "Scripts.h"
#define _USE_MATH_DEFINES
#include <cmath>

const double M_PI = 3.1415926535;

float Scripts::lengthdir_x(float len, float dir)
{
	float angle = dir * (M_PI / 180.0f);
	return len * cos(angle);
}

float Scripts::lengthdir_y(float len, float dir)
{
	float angle = dir * (M_PI / 180.0f);
	return len * sin(angle);
}

float Scripts::point_direction(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	float angle = atan2(dy, dx);
	angle = angle * (180.0f / M_PI);

	if (angle < 0)
		angle += 360.0f;

	return angle;
}

float Scripts::distance_to_object(Object* instance, Object* destiny)
{
	float dx = destiny->X() - instance->X();
	float dy = destiny->Y() - instance->Y();

	return std::sqrt(dx * dx + dy * dy);
}

float Scripts::distance_to_point(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	return std::sqrt(dx * dx + dy * dy);
}

float Scripts::lerp(float start, float end, float t)
{
	if (start < end)
	{
		start += t;
		if (start > end)
			return end;
	}
	else
	{
		start -= t;
		if (start < end)
			return end;
	}

	return start;
}

float Scripts::clamp(float val, float minVal, float maxVal)
{
	if (val < minVal)
		val = minVal;

	if (val > maxVal)
		val = maxVal;

	return val;
}

int Scripts::sign(float value)
{
	if (value < 0)
		return -1;
	else if (value > 0)
		return 1;
	else
		return 0;
}