#include "TitleState.h"
#include "InputManager.h"
#include "Resources.h"
#include "Camera.h"
#include "Game.h"
#include "Text.h"
#include <iostream>


TitleState::TitleState() {
	blinkTimer = Timer();
	blinkTimer.Restart();
}

TitleState::~TitleState() {
}

void TitleState::LoadAssets() {
	GameObject* titleObj = new GameObject();
	bg = new Sprite(*titleObj, "resources/img/title.jpg");
	titleObj->AddComponent(bg);
	AddObject(titleObj);

	GameObject* txtObj = new GameObject();
	txt = new Text(*txtObj, "resources/font/Call me maybe.ttf", 36, Text::BLENDED, "Press SPACE to start!", { 255, 0, 0, 0 });
	txtObj->AddComponent(txt);
	txtObj->box.x = GAME_WIDTH / 2 - txtObj->box.w / 2;
	txtObj->box.y = GAME_HEIGHT * 4 / 5;
	AddObject(txtObj);
}

void TitleState::Update(float dt) {
	InputManager& input = InputManager::GetInstance();
	
	if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
		quitRequested = true;
	}

	if (input.KeyPress(SPACE_KEY)) {
		Game::GetInstance().Push(new StageState());
	}

	blinkTimer.Update(dt);
	if (blinkTimer.Get() > 0.5) {
		blinkTimer.Restart();
		txt->SetColor({ 255, 0, 0, (Uint8) (txt->GetColor().a == 0 ? 1 : 0) });
	}

	UpdateArray(dt);
}

void TitleState::Render() {
	RenderArray();
}

void TitleState::Start() {
	LoadAssets();
}

void TitleState::Resume() {
	Camera::pos = { 0, 0 };
}

void TitleState::Pause() {}
