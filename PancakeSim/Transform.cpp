#include "Transform.h"
#include "Vector2.h"
#include "SDL.h"

Transform::Transform()
{

	position = new Vector2(0, 0);
	scale = new Vector2(1, 1);
	rect = new SDL_Rect();
}

Transform::~Transform()
{

	delete position;
	delete scale;
	delete rect;

}

void Transform::SetPosition(int x, int y)
{

	position->SetVector(x, y);

}

Vector2* Transform::GetPosition()
{
	return position;
}

void Transform::SetScale(int x, int y)
{

	scale->SetVector(x, y);

}

Vector2* Transform::GetScale()
{
	return scale;
}

SDL_Rect* Transform::GetRectScaled(int px_width, int px_height)
{
	rect->x = position->x;
	rect->y = position->y;
	rect->w = px_width * scale->x;
	rect->h = px_height * scale->y;

	return rect;
}