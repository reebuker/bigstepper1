#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Action.h"

#include "ConfigManager.h"
#include "Scene_Level.h"
#include "Registry.hpp"

#include "RenderSystem.hpp"
#include "MovementSystem.hpp"
#include "PhysicsSystem.hpp"
#include "AbilitySystem.hpp"
#include "CameraSystem.hpp"

class Engine
{
private:
	SDL_Window*		window		= NULL;
	SDL_Renderer*	renderer	= NULL;

	std::unique_ptr<ConfigManager>	config;
	std::unique_ptr<Scene_Level>	currentScene;

	std::unique_ptr<RenderSystem>	renderSys;	
	std::unique_ptr<MovementSystem> movementSys;
	std::unique_ptr<PhysicsSystem>	physicsSys;
	std::unique_ptr<AbilitySystem>	abilitySys;
	std::unique_ptr<CameraSystem>	cameraSys;

	Uint64 lastTick = 0;
	Uint64 currTick = 0;
	float deltaTime = 0;

	bool gameRunning = false;

	std::unordered_map<Action, bool> actionStates = {
		{ JUMP, false },
		{ DASH, false },
		{ MOVELEFT, false },
		{ MOVERIGHT, false },
		{ RESPAWN, false } 
	};

public:
	Engine();
	~Engine();

	void init();
	void run();
	void update();
	void quit();

	void HadleInput();
	bool isActionActive(Action action);

	SDL_Texture* loadTexture(const char* p_filePath);
	
	Scene_Level& getCurrentScene();

};