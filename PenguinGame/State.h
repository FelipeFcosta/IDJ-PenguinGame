#pragma once

#ifndef STATE_H
#define STATE_H

#include "SDL.h"
#include "Sprite.h"
#include "Music.h"

#include <iostream>

// responsable for the logic of our game
class State {
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();

private:
	Sprite bg;
	Music music;
	bool quitRequested;
};

#endif // STATE_H