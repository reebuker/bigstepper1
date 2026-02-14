#pragma once

#include "ConfigManager.h"
#include "Registry.hpp"

class AbilitySystem
{
private:
	ConfigManager* config = NULL;
	Registry* reg = NULL;

public:
	AbilitySystem() {}
	AbilitySystem(ConfigManager* p_config, Registry* p_reg)
		: config(p_config), reg(p_reg)
	{}

	void Update(float deltaTime)
	{
		jumpUpdate();
		dashUpdate(deltaTime);
	}

	void jumpUpdate()
	{
		State*	state = reg->getComponent<State>(reg->getPlayer());
		Physics	physicsCfg = config->getPhysics();

		if (state->grounded || (state->timeSinceAirborne < physicsCfg.COYOTE_TIME))
		{
			state->canJump = true;
		}
		else
		{
			state->canJump = false;
		}
	}

	void dashUpdate(float deltaTime)
	{
		UserInput*	input = reg->getComponent<UserInput>(reg->getPlayer());
		State*		state = reg->getComponent<State>(reg->getPlayer());
		Transform*	transform = reg->getComponent<Transform>(reg->getPlayer());
		Physics		physicsCfg = config->getPhysics();
		Player		playerCfg = config->getPlayer();
		
		// window after landing to dash
		if ((state->timeSinceLanding < physicsCfg.CAN_DASH_TIME) && state->grounded)
		{
			if (input->dash)		// if player pressed dash button
			{
				state->inDash = true;
				state->dashDir = transform->vel.x >= 0 ? 1 : -1;
			}

		}	
		
		// updating timer if in dash
		if (state->inDash)
		{
			state->timeInDash += deltaTime;

			// if dash time is over, reset timer to zero
			if (state->timeInDash > playerCfg.DASH_TIME)
			{
				state->inDash = false;
				state->timeInDash = 0;
			}
		}
	}

	
	
};