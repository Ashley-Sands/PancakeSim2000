#pragma once
#include "Sprite.h"

class SDL_Rect;

// loads and optimizis sprite sheets and splits it into indervidule space, horizontily :)
class SpriteSheet : public Sprite
{
public:
	SpriteSheet();
	~SpriteSheet();

	// sets the size of a single sprite within the sprite sheet
	void SetSpriteSize(int width);
	
	void GetSpriteRectByID(int id, SDL_Rect* outRect );
	int GetSpriteIdByPercentage(float percentage) const;

	//TODO Add version on GetSprite to return sprite @ ID
	//TODO Add GetID_byPrecentage

private:

	int totalSprites;

};

