#pragma once

class Vector2;

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(int x, int y);
	Vector2* GetPosition();

	void SetScale(int x, int y);
	Vector2* GetScale();

private:
	Vector2* position;
	Vector2* scale;

};

