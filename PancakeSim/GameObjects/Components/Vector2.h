#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	void SetVector(int x, int y);

	int x;
	int y;
};

class FVector2 // float V2
{
public:
	FVector2();
	FVector2(float x, float y);
	~FVector2();

	void SetVector(float x, float y);

	float x;
	float y;
};
