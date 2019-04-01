#include "Vector2.h"



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