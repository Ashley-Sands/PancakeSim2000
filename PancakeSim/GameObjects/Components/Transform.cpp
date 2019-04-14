#include "Transform.h"
#include "Vector2.h"
#include "SDL.h"
#include "Debug/Console.h"

Transform::Transform()
{

	position = new FVector2(0, 0);
	scale = new FVector2(1, 1);
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

FVector2* Transform::GetPosition()
{
	return position;
}

FVector2* Transform::GetAnchoredPosition(int px_width, int px_height, bool ignoreScale /*= false*/)
{

	if (!ignoreScale)
	{
		px_width  *= scale->x;
		px_height *= scale->y;
	}

	anchorPosition->x = position->x + (px_width  * anchor->x);
	anchorPosition->y = position->y + (px_height * anchor->y);

	return anchorPosition;

}

void Transform::SetAnchor(TransformAnchor transfromAnchor)
{
	switch (transfromAnchor)
	{
	case TransformAnchor::TopLeft:
		anchor->x = anchor->y = 0;
		break;
	case TransformAnchor::Center:
		anchor->x = anchor->y = 0.5f;
		break;
	default:
		Console::LogMessage(MessageType::Error, " Transfrom Anchor not found");
		break;
	}

}

void Transform::SetScale(float x, float y)
{

	scale->SetVector(x, y);

}

FVector2* Transform::GetScale()
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