#include "Vector2.h"


// Int Vector
///////////////////

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int x_axis, int y_axis)
{
	x = x_axis;
	y = y_axis;
}

Vector2::~Vector2()
{
}

void Vector2::SetVector(int x_axis, int y_axis)
{

	x = x_axis;
	y = y_axis;

}

// Float Vector
///////////////////

FVector2::FVector2()
{
	x = 0;
	y = 0;
}

FVector2::FVector2(float x_axis, float y_axis)
{
	x = x_axis;
	y = y_axis;
}

FVector2::~FVector2()
{
}

void FVector2::SetVector(float x_axis, float y_axis)
{

	x = x_axis;
	y = y_axis;

}
