#pragma once

#include "ConfigManager.h"
#include "LevelLoader.h"
#include "Registry.hpp"
#include "Action.h"

class Engine;

class Scene_Level
{
private:
	Engine*			engine = nullptr;
	ConfigManager*	config = nullptr;

	float	GAME_UNIT;

	Registry		reg;
	std::unique_ptr<LevelLoader> levelLoader;

public:
	Scene_Level();
	Scene_Level(Engine* p_engine, ConfigManager* config);

	void init();
	void doAction();

	void sUserInput();

	void createCamera();
	void createPlayer();
	void createTile(int id, int x, int y);

	Registry* getRegistry();

};