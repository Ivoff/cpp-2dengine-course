#include <iostream>
#include "./constants.h"
#include "./game.h"
#include "./components/transform_component.h"
#include "../lib/glm/glm.hpp"
#include "./entity_manager.h"

EntityManager entity_manager;
SDL_Renderer* Game::renderer;

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

	Game::renderer = SDL_CreateRenderer(this->window, -1, NULL);
    if ( !Game::renderer ) {
        std::cerr << "Something went wrong initializing" << std::endl;
        return;
    }
		
	this->load_level(0);
	this->running = true;
	return;
}

void Game::load_level(int levelNumber) {
    Entity& entity(entity_manager.add_entity("projectile"));
    entity.add_component<TransformComponent>(0, 0, 500, 500, 32, 32, 1);

    Entity& entity1(entity_manager.add_entity("projectile"));
    entity1.add_component<TransformComponent>(100, 50, 500, 500, 32, 32, 1);

    Entity& entity2(entity_manager.add_entity("projectile"));
    entity2.add_component<TransformComponent>(600, 100, 500, 500, 32, 32, 1);

    Entity& entity3(entity_manager.add_entity("projectile"));
    entity3.add_component<TransformComponent>(123, 321, 500, 500, 32, 32, 1);

    Entity& entity4(entity_manager.add_entity("projectile"));
    entity4.add_component<TransformComponent>(0, 500, 500, 500, 32, 32, 1);
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

void Game::update() {
	
	unsigned int available_miliseconds = MIN_FPS_TIME - (SDL_GetTicks() - this->last_frame_ticks);
	if (available_miliseconds > 0 && available_miliseconds < MIN_FPS_TIME) {
		SDL_Delay(available_miliseconds);
	}

	float delta_time = (SDL_GetTicks() - this->last_frame_ticks) / 1000.0f;
	delta_time = delta_time > 0.05f ? 0.05f : delta_time;

	this->last_frame_ticks = SDL_GetTicks();

	entity_manager.update(delta_time);
}

void Game::render() {	
	SDL_SetRenderDrawColor(Game::renderer, 30, 30, 30, 255);
	SDL_RenderClear(Game::renderer);

	if(!entity_manager.has_entities()){		
		return;
	}
	entity_manager.render();

	SDL_RenderPresent(Game::renderer);
}

void Game::destroy(){
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
