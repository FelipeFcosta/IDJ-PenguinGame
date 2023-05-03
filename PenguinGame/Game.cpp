#include "Game.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
	if (instance == nullptr) {
		instance = new Game("Felipe Costa - 190027592", 1024, 600);
	}
	return *instance;
}

Game::Game(string title, int width, int height) : window(nullptr), renderer(nullptr), state(nullptr) {
	if (instance == nullptr) {
		instance = this;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
			cout << "Error initializing SDL: " << SDL_GetError();
			exit(EXIT_FAILURE);
		}

		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
			cout << "Error initializing SDL_Image: " << IMG_GetError();
			exit(EXIT_FAILURE);
		}

		if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD) == 0) {
			cout << "Error initializing SDL_Mixer: " << Mix_GetError();
			exit(EXIT_FAILURE);
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
			cout << "Error opening SDL_Mixer audio" << endl;
			exit(EXIT_FAILURE);
		}
		Mix_AllocateChannels(32); // simultaneous audio channels

		int windowFlags = 0; // window properties, e.g. SDL_WINDOW_FULLSCREEN
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
		if (window == nullptr) {
			cout << "Error creating SDL_Window" << endl;
			exit(EXIT_FAILURE);
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) {
			cout << "Error creating SDL_Renderer" << endl;
			exit(EXIT_FAILURE);
		}

		state = new State();	// fow now the only state of the game
	}
}


/* game loop
    1. Checks, controls and loads the screens
	2. Receives and processes input data from user
	3. Updates object states (position, HP, ...)
	4. Draws the objects to the screen
*/
void Game::Run() {
	while (state->QuitRequested() == false) {
		state->Update(0);
		state->Render();

		SDL_RenderPresent(renderer);

		int FPS = 30;
		SDL_Delay(1000/FPS);
	}
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

State& Game::GetState() {
	return *state;
}

Game::~Game() {
	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}
