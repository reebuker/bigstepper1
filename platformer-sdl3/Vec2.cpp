#include "Vec2.h"

Vec2::Vec2(float p_x, float p_y) 
	: x(p_x), y(p_y) {}

void Vec2::operator+=(const Vec2 rhs)
{
	x += rhs.x;
	y += rhs.y;
}