#pragma once

class Vector2;
class FVector2;
class SDL_Rect;

//TODO: Add set Position/Scale Anchor
//      And make Get/Set Posdition take it into account :)

enum TransformAnchor		//TODO: implerment the rest iv only done the ones i need :/
{
	TopLeft,
	Center,
	BottomCenter
};

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(int x, int y);
	void SetAnchoredPosition(int x_pos, int y_pos, bool ignoreScale = false);

	FVector2* GetPosition();
	FVector2* GetAnchoredPosition(bool ignoreScale = false);

	void SetAnchor(TransformAnchor anchor);

	void SetScale(float x, float y);
	FVector2* GetScale();

	// Sets the size of the transform in px
	// This should be the size of the final rect when the scale is set 1,1
	void SetSize(int px_x, int px_y);
	Vector2* GetSize();

	void SetRotation(int rot);
	int GetRotation();

	// Get the transfors rect (scaled)
	SDL_Rect* GetRectScaled();

	// Get the transfors rect (unscaled)
	SDL_Rect* GetRect();

private:
	FVector2* position;
	int       rotation;			// rotation around the center of the sprite, in degres.
	FVector2* scale;

	Vector2* size_px;			// The size of the transform in px.

	FVector2* anchor;
	FVector2* anchoredPosition; // This is only updated when GetAnchoredPosition is called

	SDL_Rect* rect;
	SDL_Rect* rect_scaled;

};

