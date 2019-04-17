#pragma once
#include "Transform.h"
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

class TextTransform : public Transform
{
public:
	TextTransform(TTF_Font* font);
	~TextTransform();

	void SetFontFace(TTF_Font* font);
	void SetFontColor(int r, int g, int b, int a = 255);

	void SetText(std::string text);

	void Render(SDL_Renderer* renderer);

private:
	TextTransform();

	TTF_Font* fontFace;
	SDL_Color* fontColor;

	SDL_Surface* fontRenderSurface;
	SDL_Texture* fontRenderTexture;

	std::string text;
	bool textHasChanged = false;

	void UpdateFontTexture(SDL_Renderer* renderer);



};

