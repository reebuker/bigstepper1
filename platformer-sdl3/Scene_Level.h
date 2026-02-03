#pragma once

#include "Registry.hpp"
#include "Action.h"

class Engine;

class Scene_Level
{
private:
	Engine*		engine = nullptr;
	Registry	registry;

public:
	Scene_Level();
	Scene_Level(Engine* p_engine);

	void init();
	void doAction();

	void sUserInput();

	Registry* getRegistry();

};