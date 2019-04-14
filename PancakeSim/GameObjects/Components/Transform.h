#pragma once

class Vector2;
class FVector2;
class SDL_Rect;

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
	void SetAnchoredPosition(int x_pos, int y_pos, int px_width, int px_height, bool ignoreScale = false);

	FVector2* GetPosition();
	void SetAnchor(TransformAnchor anchor);

	void SetScale(float x, float y);
	FVector2* GetScale();

	SDL_Rect* GetRectScaled(int px_width, int px_height);

private:
	FVector2* position;
	FVector2* scale;

	FVector2* anchor;

	SDL_Rect* rect;

};

