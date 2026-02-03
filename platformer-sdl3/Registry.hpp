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
	Entity				player;

	ComponentStorage<Tag>		tags;
	ComponentStorage<Transform> transforms;
	ComponentStorage<Rect>		rects;
	ComponentStorage<Texture>	textures;
	ComponentStorage<UserInput> userinputs;

	/*std::unordered_map<std::type_index, IComponentStorage*> componentMap;*/

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
		std::cout << "Entity added\n";
		return entity;
	}

	void setPlayer(Entity entity)
	{
		player = entity;
		std::cout << "player set to " << entity << std::endl;
	}

	Entity getPlayer()
	{
		return player;
	}

	std::vector<Entity> getEntities()
	{
		return aliveEntities;
	}

	// Component Manager

	template<typename T>
	ComponentStorage<T>* getStorage()
	{
		if constexpr (std::is_same_v<T, Tag>)
		{
			return &tags;
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