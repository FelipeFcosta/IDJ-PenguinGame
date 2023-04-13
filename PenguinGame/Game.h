#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "State.h"

#include <string>

using namespace std;

class Game
{
public:
	~Game();	// destructor
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();	// returns a reference to the instance of the class

private:
	Game(string title, int width, int height);
	
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
};

