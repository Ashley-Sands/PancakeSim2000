#include "Transform.h"
#include "Vector2.h"
#include "SDL.h"
#include "Debug/Console.h"

Transform::Transform()
{

	position = new FVector2(0, 0);
	scale = new FVector2(1, 1);
	size_px = new Vector2(1, 1);
	rect = new SDL_Rect();
	rect_scaled = new SDL_Rect();
	anchor = new FVector2(0, 0);
	anchoredPosition = new FVector2(0, 0);
}

Transform::~Transform()
{

	delete position;
	delete scale;
	delete size_px;
	delete rect;
	delete rect_scaled;
	delete anchor;
	delete anchoredPosition;

}

void Transform::SetPosition(int x, int y)
{

	position->SetVector(x, y);

}

void Transform::SetPosition(Vector2* pos)
{
	position->x = pos->x;
	position->y = pos->y;
}

void Transform::SetAnchoredPosition(int x_pos, int y_pos, bool ignoreScale /*= false*/)
{

	if (!ignoreScale)
	{
		position->x = x_pos - ((size_px->x * scale->x) * anchor->x);
		position->y = y_pos - ((size_px->y * scale->y) * anchor->y);
	}
	else
	{
		position->x = x_pos - (size_px->x * anchor->x);
		position->y = y_pos - (size_px->y * anchor->y);
	}

}

FVector2* Transform::GetPosition()
{
	return position;
}

FVector2* Transform::GetAnchoredPosition(bool ignoreScale /*= false*/)
{

	if (!ignoreScale)
	{
		anchoredPosition->x = position->x + ((size_px->x * scale->x) * anchor->x);
		anchoredPosition->y = position->y + ((size_px->y * scale->y) * anchor->y);
	}
	else
	{
		anchoredPosition->x = position->x + (size_px->x * anchor->x);
		anchoredPosition->y = position->y + (size_px->y * anchor->y);
	}

	return anchoredPosition;
}

void Transform::SetAnchor(TransformAnchor transfromAnchor)
{
	switch (transfromAnchor)
	{
	case TransformAnchor::TopLeft:
		anchor->x = anchor->y = 0.0;
		break;
	case TransformAnchor::Center:
		anchor->x = anchor->y = 0.5f;
		break;
	case TransformAnchor::BottomCenter:
		anchor->x = 0.5f;
		anchor->y = 1.0f;
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

void Transform::SetSize(int px_x, int px_y) 
{
	size_px->SetVector(px_x, px_y);
}

Vector2* Transform::GetSize()
{
	return size_px;
}

void Transform::SetRotation(int rot)
{
	rotation = rot;
}

int Transform::GetRotation()
{
	return rotation;
}

SDL_Rect* Transform::GetRectScaled()
{
	rect_scaled->x = position->x;
	rect_scaled->y = position->y;

	rect_scaled->w = size_px->x * scale->x;
	rect_scaled->h = size_px->y * scale->y;

	return rect_scaled;
}

SDL_Rect* Transform::GetRect()
{
	rect->x = position->x;
	rect->y = position->y;

	rect->w = size_px->x;
	rect->h = size_px->y;

	return rect;
}