#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Registry.hpp"

class RenderSystem
{
private:
	SDL_Renderer*	renderer = NULL;
	Registry*		registry = NULL;

public:
	RenderSystem() {}
	RenderSystem(SDL_Renderer* p_renderer, Registry* p_registry)
		: renderer(p_renderer), registry(p_registry) 
	{}

	void Render()
	{
		clear();
		for (Entity e : registry->getEntities())
		{
			renderEntity(e);
		}
		SDL_RenderPresent(renderer);
	}

	void Update(Registry* p_registry)
	{
		registry = p_registry;
	}

	void renderEntity(Entity p_entity) 
	{
		SDL_FRect src;	// actual size of texture
		if (registry->hasComponent<Rect>(p_entity))
		{
			src = registry->getComponent<Rect>(p_entity)->rect;
		}

		SDL_FRect dst;
		if (registry->hasComponent<Transform>(p_entity))
		{
			dst.x = registry->getComponent<Transform>(p_entity)->pos.x;
			dst.y = registry->getComponent<Transform>(p_entity)->pos.y;
		}
		if (registry->hasComponent<Rect>(p_entity))
		{
			dst.w = registry->getComponent<Rect>(p_entity)->rect.w;
			dst.h = registry->getComponent<Rect>(p_entity)->rect.h;
		}

		SDL_RenderTexture(renderer, registry->getComponent<Texture>(p_entity)->texture, &src, &dst);
	}

	void display()
	{
		SDL_RenderPresent(renderer);
	}

	void clear()
	{
		SDL_RenderClear(renderer);
	}
};