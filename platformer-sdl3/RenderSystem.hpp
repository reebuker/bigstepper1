#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Registry.hpp"

class RenderSystem
{
private:
	ConfigManager* config = NULL;
	Registry* reg = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* tileSet = NULL;

	int	GAME_UNIT = 0;


public:
	RenderSystem() {}
	RenderSystem(ConfigManager* p_config, Registry* p_reg, SDL_Renderer* p_renderer)
		: config(p_config), reg(p_reg), renderer(p_renderer)
	{
		tileSet = config->getTileSet();
		GAME_UNIT = config->getAsset().size;
	}

	void Update()
	{
		SDL_SetRenderDrawColor(renderer, 100, 150, 255, 200);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		renderDebugInfo();

		if (reg)
		{
			for (Entity e : reg->getRenderEntities())
			{
				renderEntity(e);
			}
		}

		SDL_RenderPresent(renderer);
	}

	void Update(Registry* p_reg)
	{
		reg = p_reg;
	}

	void renderEntity(Entity p_entity)
	{
		Texture* texture = reg->getComponent<Texture>(p_entity);
		SDL_FRect rect = reg->getComponent<Rect>(p_entity)->rect;
		Vec2f pos = reg->getComponent<Transform>(p_entity)->pos;

		SDL_FRect src;	// actual size of texture
		if (reg->hasComponent<Rect>(p_entity))
		{
			src.w = rect.w;
			src.h = rect.h;
		}
		if (texture)
		{
			src.x = texture->x;
			src.y = texture->y;
		}

		SDL_FRect dst = worldToScreen(rect, pos);

		if (!reg->getComponent<Texture>(p_entity))
		{
			std::cout << "Entity doesn`t have a texture component \n";
			return;
		}

		if (!tileSet)
		{
			std::cout << "TileSet is null \n";
			return;
		}

		SDL_RenderTexture(renderer, tileSet, &src, &dst);
	}

	SDL_FRect worldToScreen(SDL_FRect rect, Vec2f pos)
	{
		// takes entity rect and pos
		// returns texture rect (size and pos)

		SDL_FRect dst;

		Camera* camera = reg->getComponent<Camera>(reg->getCamera());

		// adjust position of entity from center to upper left corner
		Vec2f entityWorldPos = { pos.x - rect.w / 2, pos.y - rect.h / 2 };

		dst.x = entityWorldPos.x + camera->offset.x;
		dst.y = entityWorldPos.y + camera->offset.y;

		dst.w = GAME_UNIT;
		dst.h = GAME_UNIT;

		return dst;
	}

	void renderDebugInfo()
	{
		Transform* transform = reg->getComponent<Transform>(reg->getPlayer());
		Transform* transformCam = reg->getComponent<Transform>(reg->getCamera());
		Transform* transformFoot = reg->getComponent<Transform>(reg->getFootSensor());
		Transform* transformHead = reg->getComponent<Transform>(reg->getHeadSensor());
		State* state = reg->getComponent<State>(reg->getPlayer());

		Window window = config->getWindow();

		SDL_RenderDebugTextFormat(renderer, 8, window.H - 64, "MOVE:    press W A S D");
		SDL_RenderDebugTextFormat(renderer, 8, window.H - 48, "JUMP:    press SPACE");
		SDL_RenderDebugTextFormat(renderer, 8, window.H - 32, "DASH:    press L SHIFT");
		SDL_RenderDebugTextFormat(renderer, 8, window.H - 16, "RESPAWN: press R");

		//SDL_RenderDebugTextFormat(renderer, 0, 0, "Vel: %f, %f\n", transform->vel.x, transform->vel.y);
		//SDL_RenderDebugTextFormat(renderer, 0, 16, "Pos: %f, %f\n", transform->pos.x, transform->pos.y);
		//SDL_RenderDebugTextFormat(renderer, 0, 32, "Cam Pos: %f, %f\n", transformCam->pos.x, transformCam->pos.y);
		//SDL_RenderDebugTextFormat(renderer, 0, 48, "Sensor Foot Pos: %f, %f\n", transformFoot->pos.x, transformFoot->pos.y);
		//SDL_RenderDebugTextFormat(renderer, 0, 64, "Sensor Head Pos: %f, %f\n", transformHead->pos.x, transformHead->pos.y);
	}

};