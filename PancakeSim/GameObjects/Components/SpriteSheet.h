#pragma once
#include "Sprite.h"

class SDL_Rect;

// loads and optimizis sprite sheets and splits it into indervidule sprites tiles.
// each row is considered a sigle animaion sequence.
// All tiles MUST be the same size
class SpriteSheet : public Sprite
{
public:
	SpriteSheet();
	~SpriteSheet();

	// sets the size of a single sprite within the sprite sheet
	// if hiehgt is not ser....  the height of the sheet is used.
	void SetSpriteSize(int width, int height = -1);
	
	void GetSpriteRectByID(int id, int rowId, SDL_Rect* outRect );
	int GetSpriteIdByPercentage(float percentage) const;

	int GetTotalSprites();
	int GetTotalSpriteRows();
	//TODO Add version on GetSprite to return sprite @ ID
	//TODO Add GetID_byPrecentage

private:

	int totalSprites;

	int totalSpriteRows = 1;

};

