#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>

#include "Components.hpp"

typedef uint32_t Entity;

class IComponentStorage
{
public:
	IComponentStorage() = default;
};

template<typename T>
class ComponentStorage : public IComponentStorage
{
private:
	std::vector<T> components;		// вектор компонентов
	std::vector<Entity> entities;	// какие сущности имеют этот компонент
	std::unordered_map<Entity, size_t> entity_to_index;	// найти компонент по сущности

public:
	ComponentStorage()
	{}

	size_t size()
	{
		return components.size();
	}

	bool has(Entity entity)
	{
		if (std::find(entities.begin(), entities.end(), entity) != entities.end())
		{
			return true;
		}
		return false;
	}

	void add(Entity entity, T component)
	{
		entity_to_index[entity] = components.size();
		components.push_back(component);
		entities.push_back(entity);
	}

	T* get(Entity entity)
	{
		// TODO: add index range check
		if (components.size() <= entity_to_index[entity])
		{
			std::cout << "Index error at ComponentStorage::get() with entity " << entity << std::endl;
			return nullptr;
		}

		if (!has(entity))
		{
			std::cout << "Entity does not have component: " << entity << std::endl;
			return nullptr;
		}
		return &components[entity_to_index[entity]];
	}

	std::vector<Entity>& getEntities()
	{
		return entities;
	}

};