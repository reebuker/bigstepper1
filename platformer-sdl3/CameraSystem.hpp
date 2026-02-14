#pragma once

#include "ConfigManager.h"
#include "Registry.hpp"

class CameraSystem
{
private:
	Registry* reg = NULL;
	ConfigManager* config = NULL;

	Vec2f screenSize;

public:
	CameraSystem() {}
	CameraSystem(ConfigManager* p_config, Registry* p_reg)
		: config(p_config), reg(p_reg)
	{
		screenSize.x = config->getWindow().W;
		screenSize.y = config->getWindow().H;
	}

	void Update()
	{
		Transform* cameraTransform = reg->getComponent<Transform>(reg->getCamera());
		Transform* playerTransform = reg->getComponent<Transform>(reg->getPlayer());
		Camera* camera = reg->getComponent<Camera>(reg->getCamera());

		cameraTransform->pos = playerTransform->pos;

		camera->offset = screenSize / 2 - cameraTransform->pos;
	}

};