#pragma once
#ifndef STATE_H
#define STATE_H
#include "SDL.h"
#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>

// responsable for the logic of our game
class State {
public:
	State();
	~State();
	void AddObject(int mouseX, int mouseY);
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();

private:
	// manage game objects, unique_ptr for auto memory management of a GameObject
	std::vector<std::unique_ptr<GameObject>> objectArray;
	GameObject* bg;
	Music music;
	bool quitRequested;
};

#endif // STATE_H