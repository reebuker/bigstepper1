#pragma once

#include "ConfigManager.h"
#include "Registry.hpp"

class LevelLoader
{
private:
	ConfigManager* config;
	Registry* reg;

	std::vector<std::vector<int>> tileMatrix;

public:
	LevelLoader(ConfigManager* p_config, Registry* p_reg);

	void loadCSV(const std::string& path);
	std::vector<std::vector<int>>& getTileMatrix();
};