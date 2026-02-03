#pragma once

struct Vec2
{
	float x, y;

	Vec2(float p_x, float p_y);

	void operator+=(const Vec2 rhs);
};