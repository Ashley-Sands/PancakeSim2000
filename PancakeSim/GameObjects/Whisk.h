#pragma once
#include "Components/SpriteObject.h"

class sprite;

class Whisk : public SpriteObject
{
public:
	
	Whisk(Sprite* sprite);
	~Whisk();

	void Upadate(bool isWhisking);

private:

	const float whiskSpeed = 500.0f; //dgress per sec
	const int maxRotation = 45;

	float currentRotation = 0;
	int rotationDirection = 1; // 1 = clockrise, 0 static. 2 anti-clock

};

