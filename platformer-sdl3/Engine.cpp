#include "Engine.h"
#include "Registry.hpp"

#include <vector>

Engine::Engine()
{
	init();
}

Engine::~Engine()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Engine::init()
{
	config = std::make_unique<ConfigManager>("res/config/config.json");

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Game v1.0", config->getWindow().W, config->getWindow().H, SDL_WINDOW_OPENGL);

	if (window == NULL)
		std::cout << "Window failed to init. Error:" << SDL_GetError() << "\n";

	renderer = SDL_CreateRenderer(window, NULL);

	if (renderer == NULL)
		std::cout << "Renderer failed to init. Error:" << SDL_GetError() << "\n";
	
	if (!SDL_SetRenderVSync(renderer, 1))
		std::cout << "Failed to turn on vsync. Error:" << SDL_GetError() << "\n";
	
	config->loadTileSet(renderer);

	// Scene initialization
	currentScene = std::make_unique<Scene_Level>(this, config.get());

	// Systems initialization
	renderSys = std::make_unique<RenderSystem>(config.get(), getCurrentScene().getRegistry(), renderer);
	movementSys = std::make_unique<MovementSystem>(config.get(), getCurrentScene().getRegistry());
	physicsSys	= std::make_unique<PhysicsSystem>(config.get(), getCurrentScene().getRegistry());
	abilitySys	= std::make_unique<AbilitySystem>(config.get(), getCurrentScene().getRegistry());
	cameraSys	= std::make_unique<CameraSystem>(config.get(), getCurrentScene().getRegistry());
}

void Engine::run() 
{
	gameRunning = true;

	while (gameRunning)
	{
		update();
		currentScene->sUserInput();
		HadleInput();
		movementSys->Update(deltaTime);
		physicsSys->Update(deltaTime);
		abilitySys->Update(deltaTime);
		cameraSys->Update();
		renderSys->Update();
	}

}

void Engine::update()
{
	lastTick = currTick;
	currTick = SDL_GetTicks();
	deltaTime = (currTick - lastTick) / 1000.0f;
}

void Engine::quit()
{
	gameRunning = false;
}

void Engine::HadleInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			quit();
		}

		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			switch (event.key.scancode)
			{
			case SDL_SCANCODE_SPACE:
				actionStates[JUMP] = true;
				break;
			case SDL_SCANCODE_LSHIFT:
				actionStates[DASH] = true;
				break;
			case SDL_SCANCODE_A:
				actionStates[MOVELEFT] = true;
				break;
			case SDL_SCANCODE_D:
				actionStates[MOVERIGHT] = true;
				break;
			case SDL_SCANCODE_R:
				actionStates[RESPAWN] = true;
				break;
			}
		}

		if (event.type == SDL_EVENT_KEY_UP)
		{
			switch (event.key.scancode)
			{
			case SDL_SCANCODE_SPACE:
				actionStates[JUMP] = false;
				break;
			case SDL_SCANCODE_LSHIFT:
				actionStates[DASH] = false;
				break;
			case SDL_SCANCODE_A:
				actionStates[MOVELEFT] = false;
				break;
			case SDL_SCANCODE_D:
				actionStates[MOVERIGHT] = false;
				break;
			case SDL_SCANCODE_R:
				actionStates[RESPAWN] = false;
				break;
			}
		}

	}
}

bool Engine::isActionActive(Action action)
{
	if (actionStates.find(action) != actionStates.end())
	{
		if (actionStates.at(action)) { return true; }
	}
	else
	{
		std::cout << "Error: couldn`t find action " << action << " in actionStates\n";
	}
		
	return false;
}

SDL_Texture* Engine::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error:" << SDL_GetError() << "\n";

	return texture;
}

Scene_Level& Engine::getCurrentScene()
{
	return *currentScene;
}