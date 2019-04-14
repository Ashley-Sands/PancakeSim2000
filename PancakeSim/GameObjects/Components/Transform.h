#pragma once

class Vector2;
class FVector2;
class SDL_Rect;

#define out
//TODO: Add set Position/Scale Anchor
//      And make Get/Set Posdition take it into account :)

enum TransformAnchor		//TODO: implerment the rest iv only done the ones i need :/
{
	TopLeft,
	Center
};

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(int x, int y);
	FVector2* GetPosition();
	FVector2* GetAnchoredPosition(int px_width, int px_height, bool ignoreScale = false);
	void SetAnchor(TransformAnchor anchor);

	void SetScale(float x, float y);
	FVector2* GetScale();

	SDL_Rect* GetRectScaled(int px_width, int px_height);

private:
	FVector2* position;
	FVector2* scale;

	TransformAnchor anchor = TransformAnchor::TopLeft;
	FVector2* anchorPosition;

	SDL_Rect* rect;

};

