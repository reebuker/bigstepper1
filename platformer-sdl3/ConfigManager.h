#pragma once

#include "Vec2.h"
#include <unordered_map>
#include <iostream>
#include <SDL3_image/SDL_image.h>

struct Game { size_t tilesize; };
struct Window { float W, H; };
struct Player { float W, H, ACCEL, BRAKE, JUMP, DASH, DASH_TIME, MAX_VEL_X; };
struct Physics { float GRAVITY, MAX_VEL_Y, COYOTE_TIME, CAN_DASH_TIME; };
struct Level { size_t width, height; };
struct Asset
{
	size_t size, width, height;
	std::string path;
};

typedef std::vector<std::tuple<std::string, std::string>> TileVec;

class ConfigManager
{
private:
	Game	gameCfg;
	Window	windowCfg;
	Player	playerCfg;
	Physics physicsCfg;
	Level	levelCfg;
	Asset	assetCfg;
	TileVec tiles;
	
	SDL_Texture* tileSet = NULL;

	std::string filepath;

public:
	ConfigManager() = default;
	ConfigManager(const std::string& path);

	void loadFromFile();
	void loadTileSet(SDL_Renderer* renderer);

	Game&		getGame();
	Window&		getWindow();
	Player&		getPlayer();
	Physics&	getPhysics();
	Level&		getLevel();
	Asset&		getAsset();

	SDL_Texture* getTileSet();

	Vec2i getTexturePos(int id);
};