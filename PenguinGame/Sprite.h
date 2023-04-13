#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "SDL_Image.h"

#include <string>
using namespace std;

class Sprite
{
public:
	Sprite();
	Sprite(string file);
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y);
	int GetWidth();
	int GetHeight();
	bool IsOpen();

private:
	SDL_Texture* texture;	// our image
	int width, height;		// dimensions of our image
	SDL_Rect clipRect;		// clip rectangle of the image to be rendered
};

#endif // SPRITE_H