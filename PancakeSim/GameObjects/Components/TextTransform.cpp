#include "TextTransform.h"



TextTransform::TextTransform(TTF_Font* font) : Transform()
{
	fontFace = font;
}


TextTransform::~TextTransform()
{
}

void TextTransform::SetFontFace(TTF_Font* font)
{
	fontFace = font;
}