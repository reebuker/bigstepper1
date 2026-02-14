#pragma once

#include <iostream>


struct Vec2i
{
	int x, y;

	Vec2i();
	Vec2i(int p_x, int p_y);

	Vec2i operator + (const Vec2i rhs);
	Vec2i operator - (const Vec2i rhs);
	Vec2i operator * (int value);
	Vec2i operator / (int value);

	void operator += (const Vec2i rhs);
	void operator -= (const Vec2i rhs);
	void operator *= (int value);
	void operator /= (int value);

	void limit(int max_value);

	float length();
	bool isPositive();
	bool isZero();

	friend std::ostream& operator << (std::ostream& os, Vec2i v);
};

struct Vec2f
{
	float x, y;

	Vec2f();
	Vec2f(float p_x, float p_y);

	Vec2f operator + (const Vec2f rhs);
	Vec2f operator - (const Vec2f rhs);
	Vec2f operator * (float value);
	Vec2f operator / (float value);

	void operator += (const Vec2f rhs);
	void operator -= (const Vec2f rhs);
	void operator *= (float value);
	void operator /= (float value);

	void limit(float max_value);

	float length();
	bool isPositive();
	bool isZero();

	friend std::ostream& operator << (std::ostream& os, Vec2f v);
};