#pragma once

#include "Vec2.h"
#include "Registry.hpp"

class PhysicsSystem
{
private:
	ConfigManager* config = NULL;
	Registry* reg = NULL;

public:
	PhysicsSystem() {}
	PhysicsSystem(ConfigManager* p_config, Registry* p_reg) 
		: config(p_config), reg(p_reg) {}

	void Update(float deltaTime)
	{
		Vec2f playerPrevPos = reg->getComponent<Transform>(reg->getPlayer())->prevPos;
		State* state = reg->getComponent<State>(reg->getPlayer());

		state->grounded		= false;	// entity is not colliding with ground by default 
		state->hitCeiling	= false;	// entity is not colliding with ceiling by default 
		
		for (Entity entity : reg->getStorage<BlockTag>()->getEntities())
		{
			Vec2f overlap		= getOverlap(entity, reg->getPlayer());
			Vec2f prevOverLap	= getPrevOverlap(entity, reg->getPlayer());
			Vec2f entityPos		= reg->getComponent<Transform>(entity)->pos;

			if (overlap.isPositive() && prevOverLap.y > 0)	// came from X direction
			{
				if (playerPrevPos.x <= entityPos.x) // came from left
				{
					reg->getComponent<Transform>(reg->getPlayer())->pos.x -= overlap.x;
					reg->getComponent<Transform>(reg->getFootSensor())->pos.x -= overlap.x;
					reg->getComponent<Transform>(reg->getHeadSensor())->pos.x -= overlap.x;
				}
				if (playerPrevPos.x > entityPos.x) // came from right
				{
					reg->getComponent<Transform>(reg->getPlayer())->pos.x += overlap.x;
					reg->getComponent<Transform>(reg->getFootSensor())->pos.x += overlap.x;
					reg->getComponent<Transform>(reg->getHeadSensor())->pos.x += overlap.x;
				}
			}

			// recalculate after correcting player`s position
			overlap = getOverlap(entity, reg->getPlayer());

			if (overlap.isPositive() && prevOverLap.x > 0) // came from Y direction
			{
				if (playerPrevPos.y <= entityPos.y) // came from top
				{
					reg->getComponent<Transform>(reg->getPlayer())->pos.y -= overlap.y;
					reg->getComponent<Transform>(reg->getFootSensor())->pos.y -= overlap.y;
					reg->getComponent<Transform>(reg->getHeadSensor())->pos.y -= overlap.y;
				}
				if (playerPrevPos.y > entityPos.y) // came from bottom
				{
					reg->getComponent<Transform>(reg->getPlayer())->pos.y += overlap.y;
					reg->getComponent<Transform>(reg->getFootSensor())->pos.y += overlap.y;
					reg->getComponent<Transform>(reg->getHeadSensor())->pos.y += overlap.y;
				}
			}

			// sensors check
			Vec2f footSensorOL = getOverlap(entity, reg->getFootSensor());
			Vec2f headSensorOL = getOverlap(entity, reg->getHeadSensor());

			if (footSensorOL.isPositive())
				reg->getComponent<State>(reg->getPlayer())->grounded = true;
			
			if (headSensorOL.isPositive())
				reg->getComponent<State>(reg->getPlayer())->hitCeiling = true;
		}

		// updating counters 
		updateStateTimers(state, deltaTime);

		stayOnScreen(config->getWindow().W, config->getWindow().H);
	}

	Vec2f getOverlap(Entity a, Entity b)
	{
		Vec2f pos_a = reg->getComponent<Transform>(a)->pos;
		Vec2f pos_b = reg->getComponent<Transform>(b)->pos;

		Vec2f half_a = reg->getComponent<BoundingBox>(a)->halfSize;
		Vec2f half_b = reg->getComponent<BoundingBox>(b)->halfSize;

		float dx = abs(pos_a.x - pos_b.x);
		float overlap_x = half_a.x + half_b.x - dx;

		float dy = abs(pos_a.y - pos_b.y);
		float overlap_y = half_a.y + half_b.y - dy;

		return { overlap_x, overlap_y };
	}

	Vec2f getPrevOverlap(Entity a, Entity b)
	{
		Vec2f pos_a = reg->getComponent<Transform>(a)->prevPos;
		Vec2f pos_b = reg->getComponent<Transform>(b)->prevPos;

		Vec2f half_a = reg->getComponent<BoundingBox>(a)->halfSize;
		Vec2f half_b = reg->getComponent<BoundingBox>(b)->halfSize;

		float dx = abs(pos_a.x - pos_b.x);
		float overlap_x = half_a.x + half_b.x - dx;

		float dy = abs(pos_a.y - pos_b.y);
		float overlap_y = half_a.y + half_b.y - dy;

		return { overlap_x, overlap_y };
	}

	void stayOnScreen(size_t w, size_t h)
	{
		Transform* transform = reg->getComponent<Transform>(reg->getPlayer());
		BoundingBox* bbox = reg->getComponent<BoundingBox>(reg->getPlayer()); 
		
		// upper down border control
		if (transform->pos.y - bbox->halfSize.y < 0)
			transform->pos.y = bbox->halfSize.y;
		
		if (transform->pos.y + bbox->halfSize.y > h)
			transform->pos.y = h - bbox->halfSize.y;
		
	}

	void updateStateTimers(State* state, float deltaTime)
	{	
		if (state->grounded == true)
		{
			// increase grounded timer
			state->timeSinceLanding += deltaTime;
			state->timeSinceAirborne = 0;
		}
		else
		{
			// increase airborne timer
			state->timeSinceLanding = 0;
			state->timeSinceAirborne += deltaTime;
		}

	}
};