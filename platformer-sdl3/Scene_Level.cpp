#include "Scene_Level.h"
#include "Engine.h"

Scene_Level::Scene_Level()
{}

Scene_Level::Scene_Level(Engine* p_engine)
	: engine(p_engine)
{
	init();
}

void Scene_Level::init()
{
	SDL_Texture* grassTexture = engine->loadTexture("res/gfx/ground_grass_1.png");

	for (int i = 0; i < 40; ++i)
	{
		Entity block = registry.addEntity();
		registry.addComponent<Tag>(block, Tag("grass_block"));
		registry.addComponent<Transform>(block, Transform(32 * i, 500));
		registry.addComponent<Rect>(block, { 0, 0, 32, 32 });
		registry.addComponent<Texture>(block, Texture(grassTexture));
	}

	Entity player = registry.addEntity();
	registry.setPlayer(player);
	registry.addComponent<Transform>(player, Transform(200, 200));
	registry.addComponent<Rect>(player, { 0, 0, 32, 32 });
	registry.addComponent<Texture>(player, Texture(grassTexture));
	registry.addComponent<UserInput>(player, UserInput());
}

void Scene_Level::doAction()
{

}

void Scene_Level::sUserInput() 
{ 
	Entity player = registry.getPlayer();
	if (!registry.hasComponent<UserInput>(player))
	{
		std::cout << "Player has no userinput component\n";
		return;
	}

	if (engine->isActionActive(MOVEUP))
		registry.getComponent<UserInput>(player)->moveUp = true;
	else
		registry.getComponent<UserInput>(player)->moveUp = false;

	if (engine->isActionActive(MOVEDOWN))
		registry.getComponent<UserInput>(player)->moveDown = true;
	else
		registry.getComponent<UserInput>(player)->moveDown = false;

	if (engine->isActionActive(MOVELEFT))
		registry.getComponent<UserInput>(player)->moveLeft = true;
	else
		registry.getComponent<UserInput>(player)->moveLeft = false;

	if (engine->isActionActive(MOVERIGHT))
		registry.getComponent<UserInput>(player)->moveRight = true;
	else
		registry.getComponent<UserInput>(player)->moveRight = false;
}

Registry* Scene_Level::getRegistry()
{
	return &registry;
}

