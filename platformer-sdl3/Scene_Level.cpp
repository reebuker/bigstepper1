#include "Scene_Level.h"
#include "Engine.h"

Scene_Level::Scene_Level()
{}

Scene_Level::Scene_Level(Engine* p_engine, ConfigManager* p_config)
	: engine(p_engine), config(p_config)
{
	levelLoader = std::make_unique<LevelLoader>(p_config, &reg);
	GAME_UNIT = config->getGame().tilesize;
	init();
}

void Scene_Level::init()
{
	levelLoader->loadCSV("res/config/Collision.csv");

	std::vector<std::vector<int>> tiles = levelLoader->getTileMatrix();

	for (int y = 0; y < tiles.size(); ++y)
	{
		for (int x = 0; x < tiles[y].size(); ++x)
		{
			createTile(tiles[y][x], x, y);
		}
	}

	createCamera();
	createPlayer();
}

void Scene_Level::doAction()
{

}

void Scene_Level::sUserInput()
{
	Entity player = reg.getPlayer();
	if (!reg.hasComponent<UserInput>(player))
	{
		std::cout << "Player has no userinput component\n";
		return;
	}

	if (engine->isActionActive(JUMP))
		reg.getComponent<UserInput>(player)->jump = true;
	else
		reg.getComponent<UserInput>(player)->jump = false;

	if (engine->isActionActive(DASH))
		reg.getComponent<UserInput>(player)->dash = true;
	else
		reg.getComponent<UserInput>(player)->dash = false;

	if (engine->isActionActive(MOVELEFT))
		reg.getComponent<UserInput>(player)->moveLeft = true;
	else
		reg.getComponent<UserInput>(player)->moveLeft = false;

	if (engine->isActionActive(MOVERIGHT))
		reg.getComponent<UserInput>(player)->moveRight = true;
	else
		reg.getComponent<UserInput>(player)->moveRight = false;

	if (engine->isActionActive(RESPAWN))
		reg.getComponent<UserInput>(player)->respawn = true;
	else
		reg.getComponent<UserInput>(player)->respawn = false;
}

void Scene_Level::createPlayer()
{
	Entity player = reg.addEntity();
	Player& cfg = config->getPlayer();
	reg.setPlayer(player);
	reg.addComponent<GravityTag>(player, GravityTag());
	reg.addComponent<Transform>(player, Transform(200, 200));
	reg.addComponent<Rect>(player, { cfg.W, cfg.H });
	reg.addComponent<Texture>(player, config->getTexturePos(6));
	reg.addComponent<UserInput>(player, UserInput());
	reg.addComponent<BoundingBox>(player, BoundingBox(cfg.W, cfg.H));
	reg.addComponent<State>(player, State());
	reg.addComponent<Movement>(player, { cfg.MAX_VEL_X, cfg.ACCEL, cfg.JUMP });

	Entity footSensor = reg.addEntity();
	reg.setFootSensor(footSensor);
	reg.addComponent<Transform>(footSensor, Transform());
	reg.addComponent<Rect>(footSensor, { cfg.W , 1});
	reg.addComponent<Texture>(footSensor, config->getTexturePos(12));
	reg.addComponent<BoundingBox>(footSensor, BoundingBox(cfg.W, 1));

	Entity headSensor = reg.addEntity();
	reg.setHeadSensor(headSensor);
	reg.addComponent<Transform>(headSensor, Transform());
	reg.addComponent<Rect>(headSensor, { cfg.W , 1});
	reg.addComponent<Texture>(headSensor, config->getTexturePos(12));
	reg.addComponent<BoundingBox>(headSensor, BoundingBox(cfg.W, 1));
}

void Scene_Level::createCamera()
{
	Entity camera = reg.addEntity();
	Window& cfg = config->getWindow();
	reg.setCamera(camera);
	reg.addComponent<Transform>(camera, Transform(cfg.W / 2.f, cfg.H / 2.f));
	reg.addComponent<Rect>(camera, { cfg.W, cfg.H });
	reg.addComponent<Camera>(camera, Camera());
}

void Scene_Level::createTile(int id, int x, int y)
{

	if (id == -1)	// hadrcoded tile_id of air 
	{
		return;
	}

	Entity tile = reg.addEntity();
	reg.addComponent<BlockTag>(tile, BlockTag());
	reg.addComponent<Transform>(tile, Transform(GAME_UNIT * x, GAME_UNIT * y));
	reg.addComponent<Rect>(tile, { GAME_UNIT, GAME_UNIT });
	reg.addComponent<Texture>(tile, config->getTexturePos(id));
	reg.addComponent<BoundingBox>(tile, BoundingBox(GAME_UNIT, GAME_UNIT));
}

Registry* Scene_Level::getRegistry()
{
	return &reg;
}

