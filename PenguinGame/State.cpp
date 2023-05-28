#include "State.h"
#include "Game.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#include "Camera.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "InputManager.h"

#define PI 3.14159
#define TILE_SIZE 64

State::State() : quitRequested(false) {
	bg = new GameObject();	// bg is a gameObject that contains the ocean image component
	Sprite* oceanSprite = new Sprite(*bg, "resources/img/ocean.jpg");
	CameraFollower* cameraFollower = new CameraFollower(*bg);
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

	music.Open("resources/audio/stageState.ogg");
	if (music.IsOpen()) {
		music.Play();
	}
}

State::~State() {
	objectArray.clear();
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject* enemyObject = new GameObject();	// holds enemy with sprite, sound and properties
	Sprite* enemySprite = new Sprite(*enemyObject, "resources/img/penguinface.png");
	enemyObject->AddComponent(enemySprite);

	enemyObject->box.x = mouseX - (float)enemySprite->GetHeight() / 2.0f;
	enemyObject->box.y = mouseY - (float)enemySprite->GetWidth() / 2.0f;
	enemyObject->box.w = enemySprite->GetWidth();
	enemyObject->box.h = enemySprite->GetHeight();

	Sound* enemySound = new Sound(*enemyObject, "resources/audio/boom.wav");
	enemyObject->AddComponent(enemySound);

	Face* enemyProps = new Face(*enemyObject);
	enemyObject->AddComponent(enemyProps);

	objectArray.emplace_back(enemyObject);
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
		double radAngle = -PI + PI * (rand() % 1001) / 500.0;	// random angle between -PI and PI
		Vec2 randVector = Vec2(200, 0).GetRotated(radAngle);
		Vec2 mouseVector = Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
		Vec2 objPos = Vec2::Sum(randVector, mouseVector);
		AddObject((int)objPos.x, (int)objPos.y);
	}

	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i].get()->Update(dt);
	}

	for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get()->IsDead()) {
			Sound* soundComponent = (Sound*)objectArray[i]->GetComponent("Sound");

			// avoid erasing while sound component still playing
			if (soundComponent == nullptr || !soundComponent->IsPlaying()) {
				objectArray.erase(objectArray.begin() + i);
			}
			else {
				// make dead object's sprite disappear
				Sprite* associatedSprite = (Sprite*)objectArray[i]->GetComponent("Sprite");
				associatedSprite->SetClip(0, 0, 0, 0);
			}
		}
	}
}

void State::Render() {
	for (auto it = objectArray.begin(); it != objectArray.end(); it++) {
		(*it).get()->Render();
	}
}

bool State::QuitRequested() {
	return quitRequested;
}
