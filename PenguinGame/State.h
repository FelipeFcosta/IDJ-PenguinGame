#pragma once
#ifndef STATE_H
#define STATE_H

#include "GameObject.h"
#include <memory>

class State
{
public:
	State();
	virtual ~State();

	virtual void LoadAssets() = 0;

	// called every frame (if on top of stack)
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void Start() {};
	virtual void Pause() = 0;	// when another state is stacked above it
	virtual void Resume() = 0;	// when above state is popped

	virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);

	// engine communication interface
	bool PopRequested();
	bool QuitRequested();

protected:
	void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool popRequested;
	bool quitRequested;
	bool started;

	std::vector<std::shared_ptr<GameObject>> objectArray;

};

#endif // !STATE_H
