#pragma once
#ifndef END_STATE_H
#define END_STATE_H
#include "SDL.h"
#include "Sprite.h"
#include "Music.h"
#include "State.h"
#include "TileSet.h"
#include "Text.h"
#include "Timer.h"
#include <vector>
#include <memory>

class EndState : public State
{
public:
	EndState();
	~EndState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

private:
	Music backgroundMusic;
	Text* txt;
	Timer showTimer;
};

#endif // END_STATE_H