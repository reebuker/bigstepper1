#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <type_traits>

#include "Components.hpp"
#include "ComponentStorage.hpp"

class Registry
{
private:
	std::vector<Entity> aliveEntities;
	std::vector<Entity> toRemove;

	Entity camera;
	Entity player;
	Entity footSensor;
	Entity headSensor;

	ComponentStorage<BlockTag>		blockTags;
	ComponentStorage<GravityTag>	gravityTags;
	ComponentStorage<Camera>		cameras;
	

	ComponentStorage<Transform>		transforms;
	ComponentStorage<Rect>			rects;
	ComponentStorage<Texture>		textures;
	ComponentStorage<UserInput>		userinputs;
	ComponentStorage<BoundingBox>	boundingboxes;
	ComponentStorage<State>			states;
	ComponentStorage<Movement>		movements;
	

	Entity totalEntities = 0;

public:
	Registry()
	{}

	// Entity manager
	Entity addEntity()
	{
		Entity entity = totalEntities;
		aliveEntities.push_back(entity);
		totalEntities++;
		return entity;
	}

	void setCamera(Entity entity)
	{
		camera = entity;
	}
	
	void setPlayer(Entity entity)
	{
		player = entity;
	}
	
	void setFootSensor(Entity entity)
	{
		footSensor = entity;
	}

	void setHeadSensor(Entity entity)
	{
		headSensor = entity;
	}

	Entity getCamera()
	{
		return camera ;
	}

	Entity getPlayer()
	{
		return player;
	}

	Entity getFootSensor()
	{
		return footSensor;
	}

	Entity getHeadSensor()
	{
		return headSensor;
	}

	std::vector<Entity> getAllEntities()
	{
		return aliveEntities;
	}

	std::vector<Entity> getRenderEntities()
	{
		return textures.getEntities();
	}

	// Component Manager

	template<typename T>
	ComponentStorage<T>* getStorage()
	{
		if constexpr (std::is_same_v<T, BlockTag>)
		{
			return &blockTags;
		}
		if constexpr (std::is_same_v<T, GravityTag>)
		{
			return &gravityTags;
		}
		if constexpr (std::is_same_v<T, Camera>)
		{
			return &cameras;
		}
		if constexpr (std::is_same_v<T, Transform>)
		{
			return &transforms;
		}
		if constexpr (std::is_same_v<T, Rect>)
		{
			return &rects;
		}
		if constexpr (std::is_same_v<T, Texture>)
		{
			return &textures;
		}
		if constexpr (std::is_same_v<T, UserInput>)
		{
			return &userinputs;
		}
		if constexpr (std::is_same_v<T, BoundingBox>)
		{
			return &boundingboxes;
		}
		if constexpr (std::is_same_v<T, State>)
		{
			return &states;
		}
		if constexpr (std::is_same_v<T, Movement>)
		{
			return &movements;
		}
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		ComponentStorage<T>* storage = getStorage<T>();
		storage->add(entity, component);

	}

	template<typename T>
	bool hasComponent(Entity entity)
	{
		ComponentStorage<T>* storage = getStorage<T>();
		return storage->has(entity);
	}

	template<typename T>
	T* getComponent(Entity entity)
	{
		ComponentStorage<T>* storage = getStorage<T>();
		return storage->get(entity);
	}

};