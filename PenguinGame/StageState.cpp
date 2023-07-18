#include "StageState.h"
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
#include "EndState.h"
#include "GameData.h"

#define TILE_SIZE 64
#define QTD_ALIENS 4

StageState::StageState() {
	// background
	GameObject* bg = new GameObject();
	Sprite* oceanSprite = new Sprite(*bg, "resources/img/ocean.jpg");
	CameraFollower* cameraFollower = new CameraFollower(*bg);	// bg will follow camera
	bg->AddComponent(oceanSprite);
	bg->AddComponent(cameraFollower);
	AddObject(bg);

	// tileMap 1
	GameObject* tileObj = new GameObject();
	tileObj->box.x = 0;
	tileObj->box.y = 0;
	tileSet = new TileSet(*tileObj, TILE_SIZE, TILE_SIZE, "resources/img/tileset.png");
	TileMap* tileMap = new TileMap(*tileObj, "resources/map/tileMap.txt", tileSet);
	tileObj->AddComponent(tileMap);
	AddObject(tileObj);

	// aliens
	srand(time(NULL));
	Alien::alienCount = 0;
	for (int i = 0; i < QTD_ALIENS; i++) {
		GameObject* alienObj = new GameObject();
		float offset = ((float)rand() / RAND_MAX);
		Alien* alien = new Alien(*alienObj, DEFAULT_QTD_MINIONS, offset * ALIEN_REST_TIME);
		alienObj->AddComponent(alien);

		// random position for the alien
		int posX = rand() % 1408;
		int posY = rand() % 1280;
		//  not too close to penguin!
		while ((posX < (704 + 300) && posX > (704 - 300)) && (posY < (640 + 500) && posY > (640 - 300))) {
			posX = rand() % 1408;
			posY = rand() % 1280;
		}

		alienObj->box.x = posX;
		alienObj->box.y = posY;
		AddObject(alienObj);
	}

	// penguins
	GameObject* pBodyObj = new GameObject();
	PenguinBody* pBody = new PenguinBody(*pBodyObj);
	pBodyObj->AddComponent(pBody);
	pBodyObj->box.x = 704 - pBodyObj->box.w / 2;
	pBodyObj->box.y = 640 - pBodyObj->box.h / 2;
	AddObject(pBodyObj);
	Camera::Follow(pBodyObj);


	// music
	music.Open("resources/audio/stageState.ogg");
	if (music.IsOpen()) {
		music.Play();
	}

}

StageState::~StageState() {
	music.Stop(0);
}


void StageState::LoadAssets() {

}

// create all gameObjects in the begining, since there will be components dependent on other gameObjects
void StageState::Start() {
	LoadAssets();
	if (!started) {
		StartArray();
	}
	started = true;
}

void StageState::Pause() {}

void StageState::Resume() {}


void StageState::Update(float dt) {
	Camera::Update(dt);

	InputManager& input = InputManager::GetInstance();

	if (input.QuitRequested()) {
		quitRequested = true;
	}

	if (input.IsKeyDown(ESCAPE_KEY)) {
		Camera::shakeTime = 0;
		popRequested = true;
	}

	UpdateArray(dt);

	if (Alien::alienCount == 0) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	} else if (PenguinBody::player == nullptr) {
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}

	// verify collisions
	for (int i = 0; i < objectArray.size(); i++) {
		Collider* collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
		if (collider1 != nullptr) {
			double angle1 = ((Sprite*)objectArray[i]->GetComponent("Sprite"))->GetAngleDeg();
			for (int j = i + 1; j < objectArray.size(); j++) {
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
}

void StageState::Render() {
	RenderArray();
}

