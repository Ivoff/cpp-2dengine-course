#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../constants.h"
#include "../game.h"
#include "../entity.h"
#include "../component.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>

class TransformComponent: public Component {

public:
	glm::vec2 position;
	glm::vec2 velocity;
	unsigned int width;
	unsigned int height;
	unsigned int scale;

	TransformComponent(int pos_x, int pos_y, int vel_x, int vel_y, int height, int width, int scale){
		this->position = 	glm::vec2(pos_x, pos_y);
		this->velocity = 	glm::vec2(vel_x, vel_y);
		this->width = 		width;
		this->height = 		height;
		this->scale = 		scale;
	};

	void initialize() override {
		
	}

	void update(float delta_time) override {
		float next_pos_x = this->position.x + this->velocity.x * delta_time;
		float next_pos_y = this->position.y + this->velocity.y * delta_time;

		if(next_pos_x >= (float)WINDOW_WIDTH || next_pos_x <= 0 ||
			next_pos_x + this->width >= (float)WINDOW_WIDTH || next_pos_x + this->width <= 0
		){
			this->velocity.x *= -1;
		}

		if(next_pos_y >= (float)WINDOW_HEIGHT || next_pos_y <= 0 ||
			next_pos_y + this->height >= (float)WINDOW_HEIGHT || next_pos_y + this->height <= 0
		){
			this->velocity.y *= -1;
		}

		this->position.x += this->velocity.x * delta_time;
		this->position.y += this->velocity.y * delta_time;
	}

	void render() override {
		SDL_Rect transform_rectangle {
			this->position.x,
			this->position.y,
			this->width,
			this->height
		};

		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::renderer, &transform_rectangle);
	}
};

#endif
