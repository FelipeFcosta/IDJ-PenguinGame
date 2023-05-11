#include "Game.h"
#include "TileMap.h"

int main(int argc, char** argv) {

	Game &game = Game::GetInstance();

	game.Run();

	return 0;
}


//int main(int argc, char** argv) {
//	TileMap* tm = new TileMap(*(GameObject*)NULL, "resources/map/tileMap.txt", nullptr);
//	tm->Load("resources/map/tileMap.txt");
//
//	return 0;
//}