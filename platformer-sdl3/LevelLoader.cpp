#include <fstream>
#include <iostream>
#include <sstream>

#include "LevelLoader.h"


LevelLoader::LevelLoader(ConfigManager* p_config, Registry* p_reg)
	: config(config), reg(p_reg)
{

}

void LevelLoader::loadCSV(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		std::cout << "Failed to open file, path: " << path << std::endl;

	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		
		std::string id;
		std::vector<int> row;

		while (std::getline(iss, id, ','))
		{
			row.push_back(std::stoi(id));
		}

		tileMatrix.push_back(row);
	}

	std::cout << "DEBUG OUTPUT" << std::endl;
	for (int i = 0; i < tileMatrix.size(); ++i)
	{
		for (int j = 0; j < tileMatrix[i].size(); ++j)
		{
			std::cout << tileMatrix[i][j] << ",";
		}
		std::cout << "\n";
	}
}

std::vector<std::vector<int>>& LevelLoader::getTileMatrix()
{
	return tileMatrix;
}