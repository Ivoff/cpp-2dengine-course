#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H 

#include <vector>
#include <string>
#include "./entity.h"

class Entity;

class EntityManager {

private:
	std::vector<Entity*> entities;	

public:
	void 	clear();
	void 	update(float delta_time);
	void 	render();
	bool 	has_entities();
	Entity&	add_entity(std::string entity_name);

	std::vector<Entity*> 	get_entities();
	unsigned int 			length();
};

#endif
