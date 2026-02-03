#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Action.h"
#include "Scene_Level.h"
#include "Registry.hpp"
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"

class Engine
{

private:
	SDL_Window*		window		= NULL;
	SDL_Renderer*	renderer	= NULL;

	bool gameRunning = false;

	std::unique_ptr<Scene_Level> currentScene;

	std::unique_ptr<RenderSystem>	renderSys;	
	std::unique_ptr<MovementSystem> movementSys;

	std::unordered_map<Action, bool> actionStates = {
	{ MOVEUP, false },
	{ MOVEDOWN, false },
	{ MOVELEFT, false },
	{ MOVERIGHT, false }};

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