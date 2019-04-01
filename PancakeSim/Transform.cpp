#include "Transform.h"
#include "Vector2.h"


Transform::Transform()
{

	position = new Vector2();
	scale = new Vector2();

}

Transform::~Transform()
{

	delete position;
	delete scale;

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