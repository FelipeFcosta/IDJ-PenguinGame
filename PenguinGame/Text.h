#pragma once
#include <iostream>
#include "GameObject.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Component.h"
#include <memory>

class Text : public Component
{
public:
	enum TextStyle { SOLID, SHADED, BLENDED };

	Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);

	~Text();

	void Update(float dt);
	void Render();
	bool Is(std::string type);

	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(std::string fontFile);
	void SetFontSize(int fontSize);
	SDL_Color GetColor();

private:
	void RemakeTexture();

	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;

	std::string text;
	SDL_Color color;
	TextStyle style;
	std::string fontFile;
	int fontSize;
};

