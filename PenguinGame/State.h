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
	void Start();
	std::weak_ptr<GameObject> AddObject(GameObject *go);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject *go);
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();


private:
	// manage game objects, shared_ptr for auto memory management of a GameObject
	std::vector<std::shared_ptr<GameObject>> objectArray;
	GameObject* bg;
	Music music;
	bool quitRequested;
	bool started;
};

#endif // STATE_H