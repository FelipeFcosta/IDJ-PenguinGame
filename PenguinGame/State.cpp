#include "State.h"
#include "Game.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#include "Camera.h"
#include "TileMap.h"
#include "Collider.h"
#include "Collision.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "Alien.h"
#include "Collision.h"
#include "PenguinBody.h"
//#include "Collider.h"

#define TILE_SIZE 64

State::State() : quitRequested(false), started(false) {
	bg = new GameObject();	// bg is a gameObject that contains the ocean image component
	Sprite* oceanSprite = new Sprite(*bg, "resources/img/ocean.jpg");
	CameraFollower* cameraFollower = new CameraFollower(*bg);	// bg will follow camera
	bg->AddComponent(oceanSprite);
	bg->AddComponent(cameraFollower);
	objectArray.emplace_back(bg);

	GameObject* tileObj = new GameObject();
	tileObj->box.x = 0;
	tileObj->box.y = 0;

	TileSet* tileSet = new TileSet(*tileObj, TILE_SIZE, TILE_SIZE, "resources/img/tileset.png");
	TileMap* tileMap = new TileMap(*tileObj, "resources/map/tileMap.txt", tileSet);
	tileObj->AddComponent(tileMap);
	objectArray.emplace_back(tileObj);

	// alien
	GameObject* alienObj = new GameObject();
	Alien::alienCount = 0;
	Alien* alien = new Alien(*alienObj, DEFAULT_QTD_MINIONS);
	alienObj->AddComponent(alien);
	alienObj->box.x = 512 - alienObj->box.w/2;
	alienObj->box.y = 300 - alienObj->box.h/2;
	objectArray.emplace_back(alienObj);

	// penguins
	GameObject* pBodyObj = new GameObject();
	PenguinBody* pBody = new PenguinBody(*pBodyObj);
	pBodyObj->AddComponent(pBody);
	pBodyObj->box.x = 704 - pBodyObj->box.w/2;
	pBodyObj->box.y = 640 - pBodyObj->box.h/2;
	objectArray.emplace_back(pBodyObj);
	Camera::Follow(pBodyObj);

	music.Open("resources/audio/stageState.ogg");
	if (music.IsOpen()) {
		music.Play();
	}

}

State::~State() {
	objectArray.clear();
}

// create all gameObjects in the begining, since there will be components dependent on other gameObjects
void State::Start() {
	LoadAssets();
	if (!started) {
		for (int i = 0; i < objectArray.size(); i++) {
			objectArray[i]->Start();
		}
	}
	started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {

	if (go == nullptr) {
		std::cout << "error trying to add GameObject to state" << std::endl;
		return std::weak_ptr<GameObject>();
	}

	std::shared_ptr<GameObject> go_ptr(go);
	objectArray.emplace_back(go_ptr);

	if (started) go->Start();

	std::weak_ptr<GameObject> weak_go_ptr(go_ptr);
	return weak_go_ptr;
}

// used to obtain weak_ptr of object where its pure pointer is already in objectArray
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	std::weak_ptr<GameObject> weak_ptr;

	for (auto it = objectArray.begin(); it != objectArray.end(); it++) {
		if (go == (*it).get()) {
			weak_ptr = *it;
			break;
		}
	}
	return weak_ptr;
}

void State::LoadAssets() {

}


void State::Update(float dt) {
	Camera::Update(dt);

	InputManager& input = InputManager::GetInstance();

	if (input.IsKeyDown(ESCAPE_KEY) || input.QuitRequested()) {
		quitRequested = true;
	}

	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	// verify collisions
	for (int i = 0; i < objectArray.size(); i++) {
		Collider* collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
		if (collider1 != nullptr) {
			double angle1 = ((Sprite*)objectArray[i]->GetComponent("Sprite"))->GetAngleDeg();
			for (int j = i+1; j < objectArray.size(); j++) {
				Collider* collider2 = (Collider*)objectArray[j]->GetComponent("Collider");
				if (collider2 != nullptr) {
					double angle2 = ((Sprite*)objectArray[j]->GetComponent("Sprite"))->GetAngleDeg();
					if (Collision::IsColliding(collider1->box, collider2->box, 0, 0)) {
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}
	}

	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			Sprite* associatedSprite = (Sprite*)objectArray[i]->GetComponent("Sprite");
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render() {
	for (auto it = objectArray.begin(); it != objectArray.end(); it++) {
		(*it)->Render();
	}
}

bool State::QuitRequested() {
	return quitRequested;
}
