#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "./entity_manager.h"
#include "./component.h"

class Component;
class EntityManager;

class Entity {

private:
	EntityManager& 				manager;
	bool 						active;
	std::vector<Component*> 	components;

public:
	std::string name;

	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name);
	void update(float delta_time);
	void render();
	void destroy();
	bool is_active();

	template <typename T, typename... TArgs>
	T& add_component(TArgs&&... args){
		T* component {new T(std::forward<TArgs>(args)...)};
		component->owner = this;
		this->components.emplace_back(component);
		component->initialize();
		return *component;
	}
};

#endif
