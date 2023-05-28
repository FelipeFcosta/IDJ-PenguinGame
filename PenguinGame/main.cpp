#include "Game.h"
#include "TileMap.h"

int main(int argc, char** argv) {

	Game& game = Game::GetInstance();

	game.Run();

	return 0;
}
