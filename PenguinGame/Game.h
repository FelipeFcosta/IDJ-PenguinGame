#pragma once
#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "StageState.h"
#include "State.h"
#include <stack>
#include <string>

#define GAME_WIDTH 1024
#define GAME_HEIGHT 600
#define FPS 30

class Game
{
public:
	Game(std::string title, int width, int height);
	~Game();
	static Game& GetInstance();	// returns a reference to the instance of the class
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();

	void Push(State* state);
	void Run();

	float GetDeltaTime();

private:
	void CalculateDeltaTime();

	static Game* instance;

	int frameStart;
	float dt;	// time passed since last frame (in seconds)

	State* storedState;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::stack<std::unique_ptr<State>> stateStack;

};

#endif // GAME_H