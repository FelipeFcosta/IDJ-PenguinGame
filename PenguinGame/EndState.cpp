#include "EndState.h"
#include "GameData.h"
#include "GameObject.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "TitleState.h"
#include "Resources.h"
#include "Game.h"

EndState::EndState() {
	GameObject* bg = new GameObject();
	bg->AddComponent(new CameraFollower(*bg));

	if (GameData::playerVictory) {
		Sprite* victorySprite = new Sprite(*bg, "resources/img/win.jpg");
		bg->AddComponent(victorySprite);
	} else {
		Sprite* loseSprite = new Sprite(*bg, "resources/img/lose.jpg");
		bg->AddComponent(loseSprite);
	}

	AddObject(bg);

	GameObject* txtObj = new GameObject();
	txt = new Text(*txtObj, "resources/font/Call me maybe.ttf", 28, Text::SOLID, "Press SPACE to play again or ESC to quit", { 255, 0, 0, 1 });
	txtObj->AddComponent(txt);
	txtObj->box.x = GAME_WIDTH/2 - txtObj->box.w/2;
	txtObj->box.y = GAME_HEIGHT*9/10;
	AddObject(txtObj);
	showTimer = Timer();
}

EndState::~EndState() {
	backgroundMusic.Stop(0);
}

void EndState::LoadAssets() {
}

void EndState::Update(float dt) {
	InputManager& input = InputManager::GetInstance();

	if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
		quitRequested = true;
	}

	if (input.KeyPress(SPACE_KEY)) {
		popRequested = true;
	}

	UpdateArray(dt);

	showTimer.Update(dt);
	if (showTimer.Get() > 2) {
		txt->SetColor({ 255, 0, 0, 0 });
	}
}

void EndState::Render() {
	RenderArray();
}

void EndState::Start() {
	if (!started) {
		if (GameData::playerVictory) {
			backgroundMusic.Open("resources/audio/endStateWin.ogg");
		} else {
			backgroundMusic.Open("resources/audio/endStateLose.ogg");
		}

		if (backgroundMusic.IsOpen()) {
			backgroundMusic.Play();
		}
	}
	started = true;
}

void EndState::Pause()
{
}

void EndState::Resume()
{
}
