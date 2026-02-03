#pragma once

#include "Registry.hpp"

class MovementSystem
{
private:
	Registry* registry = NULL;

public:
	MovementSystem() { }
	MovementSystem(Registry* p_registry) : registry(p_registry) {}

	void Movement()
	{
		// player movement
		registry->getComponent<Transform>(registry->getPlayer())->vel = { 0,0 };

		Transform* transform = registry->getComponent<Transform>(registry->getPlayer());
		UserInput* input = registry->getComponent<UserInput>(registry->getPlayer());

		if (input && transform) 
		{
			if (input->moveUp)
				transform->vel.y -= 5;

			if (input->moveDown)
				transform->vel.y += 5;

			if (input->moveLeft)
				transform->vel.x -= 5;

			if (input->moveRight)
				transform->vel.x += 5;
		}

		for (Entity e : registry->getStorage<Transform>()->getEntities())
		{
			moveEntity(e);
		}
	}

	void moveEntity(Entity entity)
	{
		if (!registry->hasComponent<Transform>(entity))
			return;
		registry->getComponent<Transform>(entity)->pos += registry->getComponent<Transform>(entity)->vel;
	}

};