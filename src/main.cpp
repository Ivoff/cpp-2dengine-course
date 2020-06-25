#include <iostream>
#include "./game.h"
#include "./constants.h"

int main() {
	Game *game = new Game();

	game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);	

	while ( game->is_running() ) {
		game->process_input();
		game->update();
		game->render();
	}


	return 0;
}
