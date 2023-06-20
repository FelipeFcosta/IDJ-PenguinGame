#include "State.h"
#include "Game.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#include "Camera.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "Alien.h"

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

	TileSet* tileSet = new TileSet(TILE_SIZE, TILE_SIZE, "resources/img/tileset.png");
	TileMap* tileMap = new TileMap(*tileObj, "resources/map/tileMap.txt", tileSet);
	tileObj->AddComponent(tileMap);
	objectArray.emplace_back(tileObj);

	// alien
	GameObject* alienObj = new GameObject();
	Alien* alien = new Alien(*alienObj, 1);
	alienObj->AddComponent(alien);
	alienObj->box.w = ((Sprite*) alienObj->GetComponent("Sprite"))->GetWidth();
	alienObj->box.h = ((Sprite*) alienObj->GetComponent("Sprite"))->GetHeight();
	alienObj->box.x = 512 - alienObj->box.w/2;
	alienObj->box.y = 300 - alienObj->box.h/2;
	objectArray.emplace_back(alienObj);

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

	InputManager& inputManager = InputManager::GetInstance();

	if (inputManager.IsKeyDown(ESCAPE_KEY) || inputManager.QuitRequested()) {
		quitRequested = true;
	}
	if (inputManager.KeyPress(SPACE_KEY)) {
		// create object in a random angle in 200 radius distance
		double radAngle = -M_PI + M_PI * (rand() % 1001) / 500.0;	// random angle between -PI and PI
		Vec2 randVector = Vec2(200, 0).GetRotated(radAngle);
		Vec2 mouseVector = Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
		Vec2 objPos = Vec2::Sum(randVector, mouseVector);
		//AddObject((int)objPos.x, (int)objPos.y);
		AddObject(nullptr);
	}

	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			Sprite* associatedSprite = (Sprite*)objectArray[i]->GetComponent("Sprite");
			associatedSprite->SetClip(0, 0, 0, 0);
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
