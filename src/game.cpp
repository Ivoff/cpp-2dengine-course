#include <iostream>
#include "./game.h"

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

float projectile_pos_x = 0.0f;
float projectile_pos_y = 0.0f;
float projectile_vel_x = 0.05f;
float projectile_vel_y = 0.05f;

void Game::update() {
	projectile_pos_x += projectile_vel_x;
	projectile_pos_y += projectile_vel_y;
}

void Game::render() {	
	SDL_SetRenderDrawColor(this->renderer, 80, 80, 80, 255);
	SDL_RenderClear(this->renderer);

	SDL_Rect projectile {
		(int)projectile_pos_x, 
		(int)projectile_pos_y, 
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
