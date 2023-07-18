#pragma once
#ifndef TILE_STATE_H
#define TILE_STATE_H
#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State
{
public:
	TitleState();
	~TitleState();

	void LoadAssets();

	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

private:
	Sprite* bg;
	Text* txt;
	Timer blinkTimer;

};

#endif TILE_STATE_H