#pragma once

#include "Registry.hpp"

class MovementSystem
{
private:
	ConfigManager* config = NULL;
	Registry* reg = NULL;
	size_t GAME_UNIT;

public:
	MovementSystem() {}
	MovementSystem(ConfigManager* p_config, Registry* p_reg)
		: config(p_config), reg(p_reg)
	{
		GAME_UNIT = config->getAsset().size;
	}

	void Update(float deltaTime)
	{
		movePlayer(reg->getPlayer(), deltaTime);

	}

	void movePlayer(Entity player, float deltaTime)
	{
		Transform*	transform	= reg->getComponent<Transform>(player);
		UserInput*	input		= reg->getComponent<UserInput>(reg->getPlayer());
		State*		state		= reg->getComponent<State>(reg->getPlayer());
		Physics		physicsCfg	= config->getPhysics();
		Player		playerCfg	= config->getPlayer();

		transform->prevPos = transform->pos;	// tracking previous position

		if (input->respawn) { respawnPlayer(); }

		yDirMove(transform, input, state, physicsCfg, playerCfg, deltaTime);

		if (!state->inDash)
		{
			xDirMove(transform, input, state, physicsCfg, playerCfg, deltaTime);
		}
		else
		{
			dashMove(transform, input, state, physicsCfg, playerCfg, deltaTime);
		}

		transform->pos += transform->vel * deltaTime;
		sensorsUpdate();
	}

	void yDirMove(Transform* transform, UserInput* input, State* state, 
				  Physics physicsCfg, Player playerCfg, float deltaTime)
	{
		/********************** Y direction movement **********************/

		// If grounded 
		if (state->grounded || state->hitCeiling)
		{
			transform->vel.y = 0;					// Set gravity to zero
		}

		// jump only if possible
		if (input->jump && state->canJump)
		{
			transform->vel.y = -playerCfg.JUMP * GAME_UNIT;
		}

		// Gravity apply if in the air
		if (!state->grounded && !state->inDash)
		{
			// Increase falling speed if not maximum
			if (transform->vel.y > physicsCfg.MAX_VEL_Y * GAME_UNIT)
			{
				transform->vel.y = physicsCfg.MAX_VEL_Y * GAME_UNIT * deltaTime;
			}
			else
			{
				transform->vel.y += physicsCfg.GRAVITY * GAME_UNIT * deltaTime;
			}
		}
	}

	void xDirMove(Transform* transform, UserInput* input, State* state, 
				  Physics physicsCfg, Player playerCfg, float deltaTime)
	{
		/********************** X direction movement **********************/

		float targetSpeed = 0;

		// Left right movement
		if (input->moveLeft) { targetSpeed = -playerCfg.MAX_VEL_X * GAME_UNIT; }
		if (input->moveRight) { targetSpeed = playerCfg.MAX_VEL_X * GAME_UNIT; }

		// if current vel and target have same direction
		if (transform->vel.x * targetSpeed >= 0)
		{
			// approach target speed with acceleration
			transform->vel.x = approach(transform->vel.x, targetSpeed, playerCfg.ACCEL * GAME_UNIT * deltaTime);
		}
		else
		{
			// approach still positon (target and curr vel will have same direction) with brake acceleration
			transform->vel.x = approach(transform->vel.x, targetSpeed, 4 * playerCfg.ACCEL * GAME_UNIT * deltaTime);
		}

		// slow down with hard friction
		if (targetSpeed == 0 && transform->vel.x != 0)
		{
			// dead zone
			if (abs(transform->vel.x) > 0.1)
			{
				transform->vel.x *= pow(0.05f, deltaTime * 4);
			}
			else
			{
				transform->vel.x = 0;
			}
		}
	}

	void dashMove(Transform* transform, UserInput* input, State* state,
		Physics physicsCfg, Player playerCfg, float deltaTime)
	{
		/********************** Dash movement (x dir) **********************/
		
		transform->vel.x = state->dashDir * playerCfg.MAX_VEL_X * 3 * GAME_UNIT;

	}

	void sensorsUpdate()
	{
		Entity footSensor = reg->getFootSensor();
		Entity headSensor = reg->getHeadSensor();
		Entity player = reg->getPlayer();

		// *** foot sensor update *** //
		reg->getComponent<Transform>(footSensor)->pos.x =
			reg->getComponent<Transform>(player)->pos.x;			// x coordinate on center

		reg->getComponent<Transform>(footSensor)->pos.y =
			reg->getComponent<Transform>(player)->pos.y +			// y coordinate 
			reg->getComponent<BoundingBox>(player)->halfSize.y +	// is lower
			reg->getComponent<BoundingBox>(footSensor)->halfSize.y;
		
		// *** head sensor update *** //
		reg->getComponent<Transform>(headSensor)->pos.x =
			reg->getComponent<Transform>(player)->pos.x;			// x coordinate on center

		reg->getComponent<Transform>(headSensor)->pos.y =
			reg->getComponent<Transform>(player)->pos.y -			// y coordinate 
			reg->getComponent<BoundingBox>(player)->halfSize.y -	// is higher
			reg->getComponent<BoundingBox>(headSensor)->halfSize.y;

		// rect update for debug drawing (foot)
		reg->getComponent<Rect>(footSensor)->rect.x =
			reg->getComponent<Transform>(footSensor)->pos.x -
			reg->getComponent<BoundingBox>(footSensor)->halfSize.x;

		reg->getComponent<Rect>(footSensor)->rect.y =
			reg->getComponent<Transform>(footSensor)->pos.y -
			reg->getComponent<BoundingBox>(footSensor)->halfSize.y;

		// rect update for debug drawing (head)
		reg->getComponent<Rect>(headSensor)->rect.x =
			reg->getComponent<Transform>(headSensor)->pos.x -
			reg->getComponent<BoundingBox>(headSensor)->halfSize.x;

		reg->getComponent<Rect>(headSensor)->rect.y =
			reg->getComponent<Transform>(headSensor)->pos.y -
			reg->getComponent<BoundingBox>(headSensor)->halfSize.y;
	}

	float approach(float velocity, float targetVel, float accel_DT)
	{
		// targetVel is signed, accel_DT is unsigned!
		if (targetVel > 0)
		{
			velocity += accel_DT;
			if (velocity > targetVel) { velocity = targetVel; }
		}
		if (targetVel < 0)
		{
			velocity -= accel_DT;
			if (velocity < targetVel) { velocity = targetVel; }
		}

		return velocity;
	}

	void respawnPlayer()
	{
		reg->getComponent<Transform>(reg->getPlayer())->pos = { 200, 200 };
		reg->getComponent<Transform>(reg->getPlayer())->vel = { 0, 0 };
	}


};

