#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"


Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) 
	: Component(associated), fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color), texture(nullptr) {
	RemakeTexture();
}

Text::~Text() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}


void Text::Update(float dt) {}

void Text::Render() {
	if (texture) {
		SDL_Rect clipRect = { 0, 0, associated.box.w, associated.box.h };
		SDL_Rect destRect = { associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y, associated.box.w, associated.box.h };
		SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
	}
}

bool Text::Is(std::string type) {
	return type == "Text";
}

void Text::SetText(std::string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

SDL_Color Text::GetColor() {
	return this->color;
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
	this->fontFile = fontFile;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture() {
	if (texture) texture = nullptr;

	font = Resources::GetFont(fontFile, fontSize);

	if (font) {
		SDL_Surface* tmpSurface;
		switch (style)
		{
		case Text::SOLID:
			tmpSurface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case Text::SHADED:
			tmpSurface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0, 0, 0, 0});
			break;
		case Text::BLENDED:
			tmpSurface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
		default:
			tmpSurface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		}

		texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), tmpSurface);

		int width, height;

		if (texture) {
			SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
			associated.box.w = width;
			associated.box.h = height;
		}

		SDL_FreeSurface(tmpSurface);
	}

}
