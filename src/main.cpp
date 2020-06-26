#include <iostream>
#include "./constants.h"
#include "./game.h"

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
