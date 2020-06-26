#include <iostream>
#include "./constants.h"
#include "./game.h"
#include "../lib/glm/glm.hpp"

Game::Game() {
    this->running = false;
}

Game::~Game() {

}

bool Game::is_running() {
    return this->running;
}

void Game::initialize(unsigned int width, unsigned int height) {
		
    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        std::cerr << "Something went wrong initializing" << std::endl;
        return;
    }

    this->window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_ALWAYS_ON_TOP
    );
    if( !window ) {
        std::cerr << "Something went wrong initializing" << std::endl;
        return;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, NULL);
    if ( !this->renderer ) {
        std::cerr << "Something went wrong initializing" << std::endl;
        return;
    }

	this->running = true;
	return;
}

void Game::process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch( event.type ){
		case SDL_QUIT:
			this->running = false;
		break;

		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_ESCAPE ) {
				this->running = false;
			}
		break;

		default:
			break;
	}
}


glm::vec2 projectile_pos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectile_vel = glm::vec2(25.0f, 25.0f);

void Game::update() {
	
	unsigned int available_miliseconds = MIN_FPS_TIME - (SDL_GetTicks() - this->last_frame_ticks);
	if (available_miliseconds > 0 && available_miliseconds < MIN_FPS_TIME) {
		SDL_Delay(available_miliseconds);
	}

	float delta_time = (SDL_GetTicks() - this->last_frame_ticks) / 1000.0f;
	delta_time = delta_time > 0.05f ? 0.05f : delta_time;

	this->last_frame_ticks = SDL_GetTicks();

	projectile_pos = glm::vec2(
		projectile_pos.x + projectile_vel.x * delta_time,
		projectile_pos.y + projectile_vel.y * delta_time
	);
	std::cout << projectile_pos.x << ", " << projectile_pos.y << std::endl;
}

void Game::render() {	
	SDL_SetRenderDrawColor(this->renderer, 80, 80, 80, 255);
	SDL_RenderClear(this->renderer);

	SDL_Rect projectile {
		(int)projectile_pos.x, 
		(int)projectile_pos.y, 
		10, 
		10			
	};

	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(this->renderer, &projectile);
	SDL_RenderPresent(this->renderer);
}

void Game::destroy(){
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
