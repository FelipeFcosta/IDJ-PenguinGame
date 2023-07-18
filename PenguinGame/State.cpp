#include "State.h"
#include <iostream>

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object) {
	if (object == nullptr) {
		std::cout << "error trying to add GameObject to state" << std::endl;
		return std::weak_ptr<GameObject>();
	}

	std::shared_ptr<GameObject> go_ptr(object);
	objectArray.emplace_back(go_ptr);

	if (started) object->Start();

	std::weak_ptr<GameObject> weak_go_ptr(go_ptr);
	return weak_go_ptr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) {
	std::weak_ptr<GameObject> weak_ptr;

	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == object) {
			weak_ptr = objectArray[i];
			break;
		}
	}
	return weak_ptr;
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::StartArray() {
	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i].get()->Start();
	}
}

void State::UpdateArray(float dt) {
	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i].get()->Update(dt);
	}

	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray() {
	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i].get()->Render();
	}
}
