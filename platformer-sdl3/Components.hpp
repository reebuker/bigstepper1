#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "Vec2.h"

class Component
{
public:
};


class BlockTag : public Component
{
public:
	BlockTag() {}
};

class GravityTag : public Component
{
public:
	GravityTag() {}
};

class Transform : public Component
{
public:
	Vec2f pos		= { 0, 0 };
	Vec2f prevPos	= { 0, 0 };
	Vec2f vel		= { 0, 0 };

	Transform() {}
	Transform(float p_x, float p_y)
		: pos(p_x, p_y), prevPos(p_x, p_y)
	{}
};

class Rect : public Component
{
public:
	SDL_FRect rect = { 0, 0, 0, 0 };

	Rect() {}
	Rect(float p_w, float p_h) 
	{
		rect.w = p_w;
		rect.h = p_h;
	}
	Rect(float p_x, float p_y, float p_w, float p_h)
	{
		rect.x = p_x;
		rect.y = p_y;
		rect.w = p_w;
		rect.h = p_h;
	}
};

class Texture : public Component
{
public:
	size_t x = 0;
	size_t y = 0;

	Texture() {}

	Texture(Vec2i vec)
		: x(vec.x), y(vec.y) {}

	Texture(size_t p_x, size_t p_y)
		: x(p_x), y(p_y) {}
};

class UserInput : public Component
{
public:
	bool jump = false;
	bool dash = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool respawn = false;

	UserInput() {}
};

class BoundingBox : public Component
{
public:
	Vec2f size = { 0,0 };
	Vec2f halfSize = { 0,0 };

	BoundingBox() {}
	BoundingBox(float x, float y) 
		: size(x, y), halfSize(x / 2, y / 2) {}
};

class State : public Component
{
public:
	// jump related
	bool	grounded	= false;
	bool	hitCeiling	= false;
	bool	canJump		= false;
	float	timeSinceAirborne = 0;

	// dash related (grounded too)
	bool	anDash	= false;
	bool	inDash	= false;

	int		dashDir				= 0;
	float	timeSinceLanding	= 0;
	float	timeInDash			= 0;

	State() {}
};

class Movement : public Component
{
public:
	float max_vel = 0.f;
	float accel = 0.f;
	float jump = 0.f;

	Movement() {}
	Movement(float p_max_vel, float p_accel, float p_jump)
		: max_vel(p_max_vel), accel(p_accel), jump(p_jump) {}
};

class Camera : public Component
{
public:
	Vec2f offset = { 0, 0 };

	Camera() {}
};