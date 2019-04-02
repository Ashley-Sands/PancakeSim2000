#pragma once

class Vector2;
class FVector2;
class SDL_Rect;

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(int x, int y);
	Vector2* GetPosition();

	void SetScale(float x, float y);
	FVector2* GetScale();

	SDL_Rect* GetRectScaled(int px_width, int px_height);

private:
	Vector2* position;
	FVector2* scale;

	SDL_Rect* rect;

};

