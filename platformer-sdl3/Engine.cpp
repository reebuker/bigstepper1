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
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Game v1.0", 1280, 720, SDL_WINDOW_OPENGL);
	
	if (window == NULL)
		std::cout << "Window failed to init. Error:" << SDL_GetError() << "\n";

	renderer = SDL_CreateRenderer(window, NULL);

	if (renderer == NULL)
		std::cout << "Renderer failed to init. Error:" << SDL_GetError() << "\n";
	
	if (!SDL_SetRenderVSync(renderer, 1))
		std::cout << "Failed to turn on vsync. Error:" << SDL_GetError() << "\n";
	
	// Scene initialization
	currentScene = std::make_unique<Scene_Level>(this);

	// Systems initialization
	renderSys = std::make_unique<RenderSystem>(renderer, getCurrentScene().getRegistry());
	movementSys = std::make_unique<MovementSystem>(getCurrentScene().getRegistry());

}

void Engine::run() 
{

	gameRunning = true;

	while (gameRunning)
	{
		renderSys->Render();
		currentScene->sUserInput();
		HadleInput();
		movementSys->Movement();
	}

}

void Engine::update()
{
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
			case SDL_SCANCODE_W:
				actionStates[MOVEUP] = true;
				std::cout << "W pressed, \n";
				break;
			case SDL_SCANCODE_S:
				actionStates[MOVEDOWN] = true;
				std::cout << "S pressed\n";
				break;
			case SDL_SCANCODE_A:
				actionStates[MOVELEFT] = true;
				std::cout << "A pressed\n";
				break;
			case SDL_SCANCODE_D:
				actionStates[MOVERIGHT] = true;
				std::cout << "D pressed\n";
				break;
			}
		}

		if (event.type == SDL_EVENT_KEY_UP)
		{
			switch (event.key.scancode)
			{
			case SDL_SCANCODE_W:
				actionStates[MOVEUP] = false;
				std::cout << "W released, \n";
				break;
			case SDL_SCANCODE_S:
				actionStates[MOVEDOWN] = false;
				std::cout << "S released\n";
				break;
			case SDL_SCANCODE_A:
				actionStates[MOVELEFT] = false;
				std::cout << "A released\n";
				break;
			case SDL_SCANCODE_D:
				actionStates[MOVERIGHT] = false;
				std::cout << "D released\n";
				break;
			}
		}

	}
}

bool Engine::isActionActive(Action action)
{
	if (actionStates.at(action))
		return true;

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