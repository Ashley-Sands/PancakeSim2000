#include "TextTransform.h"
#include "../Debug/Console.h"


TextTransform::TextTransform(TTF_Font* font) : Transform()
{
	fontFace = font;
	fontColor = new SDL_Color();

}


TextTransform::~TextTransform()
{
}

void TextTransform::SetFontFace(TTF_Font* font)
{
	if (font == nullptr)
	{
		Console::LogMessage(MessageType::Error, "Can not set font face to null");
		return;
	}
	fontFace = font;
}

void TextTransform::SetFontColor(int r, int g, int b, int a /* = 255 */)
{
	fontColor->r = r;
	fontColor->g = g;
	fontColor->b = b;
	fontColor->a = a;
}

void TextTransform::SetText(std::string str)
{

	if (str == text) return; //no change

	text = str;
	textHasChanged = true;

}

void TextTransform::Render(SDL_Renderer* renderer)
{
	// update the font render texture only if the text has changed
	if (textHasChanged || fontRenderTexture == nullptr)	
		UpdateFontTexture(renderer);
	

	SDL_RenderCopy(renderer, fontRenderTexture, NULL, GetRectScaled());	//TODO: i really need to add size to Transform :(

}

void TextTransform::UpdateFontTexture(SDL_Renderer* renderer)
{

	//Clear the old fontRenderTexter 
	if (fontRenderTexture != nullptr)
		SDL_DestroyTexture(fontRenderTexture);

	// Creat the new texture
	fontRenderSurface = TTF_RenderText_Solid(fontFace, text.c_str(), *fontColor);
	fontRenderTexture = SDL_CreateTextureFromSurface(renderer, fontRenderSurface);
	
	//Update the transform size
	SetSize( fontRenderSurface->w, fontRenderSurface->h);

	// Clean up the old surface.
	SDL_FreeSurface(fontRenderSurface);

	textHasChanged = false;

}