#pragma once

#include "Components/SpriteAnimator.h"

class Vector2;

class FryingPan : public SpriteAnimator
{
public:
	FryingPan(SpriteSheet* sprite);
	~FryingPan();

	virtual void Begin() override;
	void Update(float inputValue, float hobValue);

	int GetCurrentSpriteId();

	void SetPanBottom_LocalOffset(float offset);
	float GetPanBottom();							// returns the botom of the pans, in world space  

private:
	int currentSpriteID = 0;
	FVector2* startPosition;
	
	float panBottom_localOffset = 55;
};

