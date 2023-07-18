#include "Game.h"
#include "TitleState.h"
#include "TileMap.h"

int main(int argc, char** argv) {

	Game& game = Game::GetInstance();
	TitleState* titleState = new TitleState();
	
	game.Push(titleState);
	game.Run();

	return 0;
}
