#include "./entity.h"

Entity::Entity(EntityManager& manager): manager {manager} {
	this->active 	= true;
}

Entity::Entity(EntityManager& manager, std::string name): manager {manager} {
	this->active 	= true;
	this->name 		= name;
}

void Entity::update(float delta_time) {
	for (auto& component : this->components) {
		component->update(delta_time);
	}
}

void Entity::render() {
	for (auto& component : this->components) {
		component->render();
	}
}

void Entity::destroy() {
	this->active = false;
}

bool Entity::is_active(){
	return this->active;
}
