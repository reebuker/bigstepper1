#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "Vec2.h"

class Component
{
public:
	bool has = false;
};

class Tag : public Component
{
public:
	std::string tag = "";

	Tag() {}
	Tag(const std::string& p_tag)
		: tag(p_tag)
	{}
};

class Transform : public Component
{
public:
	Vec2 pos = { 0, 0 };
	Vec2 vel = { 0, 0 };

	Transform() {}
	Transform(float p_x, float p_y)
		: pos(p_x, p_y)
	{}
};

class Rect : public Component
{
public:
	SDL_FRect rect = { 0, 0, 0, 0 };

	Rect() {}
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
	SDL_Texture* texture = nullptr;

	Texture() {}
	Texture(SDL_Texture* p_texture)
		: texture(p_texture)
	{}
};

class UserInput : public Component
{
public:
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	UserInput() {}
};
