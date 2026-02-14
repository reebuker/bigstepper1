#include "Vec2.h"

/******************** Vec2 INT ********************/

Vec2i::Vec2i() {}

Vec2i::Vec2i(int p_x, int p_y) 
	: x(p_x), y(p_y) {}

Vec2i Vec2i::operator + (const Vec2i rhs)
{
	return Vec2i(x + rhs.x, y + rhs.y);
}

Vec2i Vec2i::operator - (const Vec2i rhs)
{
	return Vec2i(x - rhs.x, y - rhs.y);
}

Vec2i Vec2i::operator * (int value)
{
	return Vec2i(x * value, y * value);
}

Vec2i Vec2i::operator / (int value)
{
	return Vec2i(x / value, y / value);
}

void Vec2i::operator += (const Vec2i rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2i::operator -= (const Vec2i rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2i::operator *= (int value)
{
	x *= value;
	y *= value;
}

void Vec2i::operator /= (int value)
{
	x /= value;
	y /= value;
}

void Vec2i::limit(int max_value)
{
	if (x > max_value)
		x = max_value;

	if (x < -max_value)
		x = -max_value;

	if (y > max_value)
		y = max_value;

	if (y < -max_value)
		y = -max_value;
}

float Vec2i::length()
{
	return sqrt(x * x + y * y);
}

bool Vec2i::isPositive()
{
	return (x > 0 && y > 0);
}

bool Vec2i::isZero()
{
	return (x == 0 && y == 0);
}

std::ostream& operator << (std::ostream& os, Vec2i v)
{
	return os << v.x << ", " << v.y;
} 

/******************** Vec2 FLOAT ********************/

Vec2f::Vec2f() {}

Vec2f::Vec2f(float p_x, float p_y) 
	: x(p_x), y(p_y) {}

Vec2f Vec2f::operator + (const Vec2f rhs)
{
	return Vec2f(x + rhs.x, y + rhs.y);
}

Vec2f Vec2f::operator - (const Vec2f rhs)
{
	return Vec2f(x - rhs.x, y - rhs.y);
}

Vec2f Vec2f::operator * (float value)
{
	return Vec2f(x * value, y * value);
}

Vec2f Vec2f::operator / (float value)
{
	return Vec2f(x / value, y / value);
}

void Vec2f::operator += (const Vec2f rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2f::operator -= (const Vec2f rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2f::operator *= (float value)
{
	x *= value;
	y *= value;
}

void Vec2f::operator /= (float value)
{
	x /= value;
	y /= value;
}

void Vec2f::limit(float max_value)
{
	if (x > max_value)
		x = max_value;

	if (x < -max_value)
		x = -max_value;

	if (y > max_value)
		y = max_value;

	if (y < -max_value)
		y = -max_value;
}

float Vec2f::length()
{
	return sqrt(x * x + y * y);
}

bool Vec2f::isPositive()
{
	return (x > 0 && y > 0);
}

bool Vec2f::isZero()
{
	return (x == 0 && y == 0);
}

std::ostream& operator << (std::ostream& os, Vec2f v)
{
	return os << v.x << ", " << v.y;
} 