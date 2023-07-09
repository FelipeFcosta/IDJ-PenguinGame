#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
#include "SDL_Image.h"
#include "Component.h"
#include "Timer.h"
#include <string>

class Sprite : public Component
{
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1, Vec2 scale = {1, 1}, float secondsToSelfDestruct = 0);
	~Sprite();
	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	int GetWidth();
	int GetHeight();
	bool IsOpen();

	void SetScale(float scaleX, float scaleY);
	Vec2 GetScale();

	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	int GetFrame();
	int GetFrameCount();
	float GetFrameTime();

	void SetAngleDeg(double angleDeg);
	double GetAngleDeg();

	void Update(float dt);
	void Render();
	void Render(int x, int y, int w, int h);
	bool Is(std::string file);

private:
	SDL_Texture* texture;
	int width, height;
	SDL_Rect clipRect;		// clip rectangle of the image to be rendered
	Vec2 scale;

	double angleDeg;

	int frameCount;
	int currentFrame;
	float frameTime;
	float timeElapsed;

	float secondsToSelfDestruct;
	Timer selfDestructCount;

};

#endif // SPRITE_H