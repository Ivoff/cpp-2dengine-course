#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game {
private:
	bool 			running;
	SDL_Window* 	window;
	SDL_Renderer* 	renderer;
	unsigned int 	last_frame_ticks;

public:
	Game();
	~Game();
	
	void initialize(unsigned int width, unsigned int height);	
	bool is_running();
	void process_input();
	void update();
	void render();
	void destroy();
};

#endif
