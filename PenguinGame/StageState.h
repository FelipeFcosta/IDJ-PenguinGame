#pragma once
#ifndef STAGE_STATE_H
#define STAGE_STATE_H
#include "SDL.h"
#include "Sprite.h"
#include "Music.h"
#include "State.h"
#include "TileSet.h"
#include <vector>
#include <memory>

class StageState : public State
{
public:
	StageState();
	~StageState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

private:
	TileSet* tileSet;
	Music music;
};

#endif // STAGE_STATE_H