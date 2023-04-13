#include "State.h"
#include "Game.h"


State::State() : quitRequested(false) {
	bg.Open("resources/img/ocean.jpg");
	music.Open("resources/audio/stageState.ogg");
	if (music.IsOpen()) {
		music.Play();
	}
}

void State::LoadAssets() {

}

void State::Update(float dt) {
	quitRequested = SDL_QuitRequested();
}

void State::Render() {
	bg.Render(0, 0);
}

bool State::QuitRequested() {
	return quitRequested;
}