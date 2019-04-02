#pragma once
#include "Sprite.h"

class SDL_Rect;

// loads and optimizis sprite sheets and splits it into indervidule space, horizontily :)
class SpriteSheet : public Sprite
{
public:
	SpriteSheet();
	SpriteSheet(int width, int spacingX);
	~SpriteSheet();

	void SetSpriteSize(int width, int spacingX);
	
	//TODO override GetSprite();
	void GetSpriteRectByID(int id, SDL_Rect* outRect );
	float GetSpriteIdByPercentage(float percentage);

	//TODO Add version on GetSprite to return sprite @ ID
	//TODO Add GetID_byPrecentage


private:

	int spriteWidth;
	int totalSprites;

};

