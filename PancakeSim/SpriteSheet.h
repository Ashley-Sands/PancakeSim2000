#pragma once
#include "Sprite.h"

// loads and optimizis sprite sheets and splits it into indervidule space, horizontily :)
class SpriteSheet : public Sprite
{
public:
	SpriteSheet();
	SpriteSheet(int width, int spacingX);
	~SpriteSheet();

	void SetSpriteSize(int width, int spacingX);
	
	//TODO override GetSprite();
	//TODO Add version on GetSprite to return sprite @ ID
	//TODO Add GetID_byPrecentage


private:

	int spriteWidth;
	int spriteSpacingX;
	int totalSprites;

};

