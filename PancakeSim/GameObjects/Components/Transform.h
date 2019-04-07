#pragma once

class Vector2;
class FVector2;
class SDL_Rect;

//TODO: Add set Position/Scale Anchor
//      And make Get/Set Posdition take it into account :)

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(int x, int y);
	FVector2* GetPosition();

	void SetScale(float x, float y);
	FVector2* GetScale();

	SDL_Rect* GetRectScaled(int px_width, int px_height);

private:
	FVector2* position;
	FVector2* scale;

	SDL_Rect* rect;

};

