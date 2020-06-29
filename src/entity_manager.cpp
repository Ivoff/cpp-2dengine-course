#include "./entity_manager.h"

void EntityManager::clear() {
	for(auto& entity : this->entities)
		entity->destroy();
}

void EntityManager::update(float delta_time){
	for(auto& entity : this->entities)
		entity->update(delta_time);
}

void EntityManager::render(){
	for(auto& entity : this->entities)
		entity->render();
}

bool EntityManager::has_entities() {
	return this->entities.size() > 0;	
}

Entity& EntityManager::add_entity(std::string name){
	Entity* entity = new Entity(*this, name);
	this->entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::get_entities() {
	return this->entities;
}

unsigned int EntityManager::length() {
	return this->entities.size();
}