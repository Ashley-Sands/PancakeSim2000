#pragma once
#include "Transform.h"
#include "SDL_ttf.h"

class TextTransform : public Transform
{
public:
	TextTransform(TTF_Font* font);
	~TextTransform();

	void SetFontFace(TTF_Font* font);

private:
	TextTransform();

	TTF_Font* fontFace;
};

