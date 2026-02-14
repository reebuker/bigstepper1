#include "ConfigManager.h"

#include <nlohmann/json.hpp>
#include <fstream>

std::string PATH = "res/config/config.json";
using json = nlohmann::json;

namespace nlohmann
{
	template<>
	struct adl_serializer<Game>
	{
		static void to_json(json& j, const Game& s)
		{
			j = json{
				{"tilesize", s.tilesize },
			};
		}

		static void from_json(const json& j, Game& s)
		{
			try
			{
				s.tilesize = j.at("Game").at("tilesize").get<size_t>();
			}
			catch (std::exception& e)
			{
				std::cout << "Invalid JSON format (Game)" << e.what() << std::endl;
			}
		}
	};

	template<>
	struct adl_serializer<Window>
	{
		static void to_json(json& j, const Window& s)
		{
			j = json{
				{"W", s.W},
				{"H", s.H},
			};
		}

		static void from_json(const json& j, Window& s)
		{
			try
			{
				s.W = j.at("Window").at("W").get<float>();
				s.H = j.at("Window").at("H").get<float>();
			}
			catch (const std::exception& e)
			{
				std::cout << "Invalid JSON format (Window)" << e.what() << std::endl;
			}
		}
	};

	template<>
	struct adl_serializer<Player>
	{
		static void to_json(json& j, const Player& s)
		{
			j = json{
				{"W", s.W},
				{"H", s.H},
				{"ACCEL", s.ACCEL},
				{"BRAKE", s.BRAKE},
				{"JUMP", s.JUMP},
				{"DASH", s.DASH},
				{"DASH_TIME", s.DASH_TIME},
				{"MAX_VEL_X", s.MAX_VEL_X},
			};
		}

		static void from_json(const json& j, Player& s)
		{
			try
			{
				s.W			= j.at("Player").at("W").get<float>();
				s.H			= j.at("Player").at("H").get<float>();
				s.ACCEL		= j.at("Player").at("ACCEL").get<float>();
				s.BRAKE		= j.at("Player").at("BRAKE").get<float>();
				s.JUMP		= j.at("Player").at("JUMP").get<float>();
				s.DASH		= j.at("Player").at("DASH").get<float>();
				s.DASH_TIME	= j.at("Player").at("DASH_TIME").get<float>();
				s.MAX_VEL_X = j.at("Player").at("MAX_VEL_X").get<float>();
			}
			catch (const std::exception& e)
			{
				std::cout << "Invalid JSON format (Player)" << e.what() << std::endl;
			}
		}
	};

	template<>
	struct adl_serializer<Physics>
	{
		static void to_json(json& j, const Physics& s)
		{
			j = json{
				{"GRAVITY", s.GRAVITY},
				{"MAX_VEL_Y", s.MAX_VEL_Y},
				{"COYOTE_TIME", s.COYOTE_TIME},
				{"CAN_DASH_TIME", s.CAN_DASH_TIME},
			};
		}

		static void from_json(const json& j, Physics& s)
		{
			try
			{
				s.GRAVITY		= j.at("Physics").at("GRAVITY").get<float>();
				s.MAX_VEL_Y		= j.at("Physics").at("MAX_VEL_Y").get<float>();
				s.COYOTE_TIME	= j.at("Physics").at("COYOTE_TIME").get<float>();
				s.CAN_DASH_TIME	= j.at("Physics").at("CAN_DASH_TIME").get<float>();
			}
			catch (const std::exception& e)
			{
				std::cout << "Invalid JSON format (Physics)" << e.what() << std::endl;
			}
		}
	};

	template<>
	struct adl_serializer<Level>
	{
		static void to_json(json& j, const Level& s)
		{
			j = json{
				{"width", s.width},
				{"height", s.height},
			};
		}

		static void from_json(const json& j, Level& s)
		{
			try
			{
				s.width = j.at("Level_1").at("width").get<size_t>();
				s.height = j.at("Level_1").at("height").get<size_t>();
			}
			catch (std::exception& e)
			{
				std::cout << "Invalid JSON format (Level)" << e.what() << std::endl;
			}
		}
	};

	template<>
	struct adl_serializer<Asset>
	{
		static void to_json(json& j, const Asset& s)
		{
			j = json{
				{"size", s.size},
				{"width", s.width},
				{"height", s.height},
				{"path", s.path},
			};
		}

		static void from_json(const json& j, Asset& s)
		{
			try
			{
				s.size		= j.at("Asset").at("size").get<size_t>();
				s.width		= j.at("Asset").at("width").get<size_t>();
				s.height	= j.at("Asset").at("height").get<size_t>();
				s.path		= j.at("Asset").at("path").get<std::string>();
			}
			catch (std::exception& e)
			{
				std::cout << "Invalid JSON format (Asset)" << e.what() << std::endl;
			}
		}
	};
}

ConfigManager::ConfigManager(const std::string& path)
	: filepath(path)
{
	loadFromFile();
}

void ConfigManager::loadFromFile()
{
	std::ifstream input_file(filepath);

	if (!input_file.is_open())
	{
		std::cout << "File failed to open\n";
	}

	json loaded_config;

	input_file >> loaded_config;

	gameCfg		= loaded_config.get<Game>();
	windowCfg	= loaded_config.get<Window>();
	playerCfg	= loaded_config.get<Player>();
	physicsCfg	= loaded_config.get<Physics>();
	levelCfg	= loaded_config.get<Level>();
	assetCfg	= loaded_config.get<Asset>();

	std::cout << loaded_config.dump(4) << std::endl;
}


void ConfigManager::loadTileSet(SDL_Renderer* renderer)
{
	tileSet = IMG_LoadTexture(renderer, assetCfg.path.c_str());

	if (tileSet == NULL)
	{
		std::cout << "Failed to load texture. Error:" << SDL_GetError() << "\n";
		return;
	}
}

Game& ConfigManager::getGame()
{
	return gameCfg;
}


Window& ConfigManager::getWindow()
{
	return windowCfg;
}

Player& ConfigManager::getPlayer()
{
	return playerCfg;
}

Physics& ConfigManager::getPhysics()
{
	return physicsCfg;
}

Level& ConfigManager::getLevel()
{
	return levelCfg;
}


Asset& ConfigManager::getAsset()
{
	return assetCfg;
}

SDL_Texture* ConfigManager::getTileSet()
{
	if (tileSet)
		return tileSet;

	return nullptr;
}

Vec2i ConfigManager::getTexturePos(int id)
{
	int w = static_cast<int>(assetCfg.width / assetCfg.size);

	int y = (id / w) * static_cast<int>(assetCfg.size);
	int x = (id % w) * static_cast<int>(assetCfg.size);
	
	return { x, y };
}