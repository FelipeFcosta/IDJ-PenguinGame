#pragma once
#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "State.h"
#include <string>

#define GAME_WIDTH 1024
#define GAME_HEIGHT 600
#define FPS 30

class Game
{
public:
	~Game();	// destructor
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();	// returns a reference to the instance of the class

	void CalculateDeltaTime();
	float GetDeltaTime();

private:
	Game(std::string title, int width, int height);
	
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;

	int frameStart;
	float dt;	// time passed since last frame (in seconds)
};

#endif // GAME_H