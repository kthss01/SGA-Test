#include "stdafx.h"
#include "Vector2.h"


namespace MyDirectX {
	Vector2::Vector2()
	{
	}
	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	bool Vector2::operator==(const Vector2 & vec)
	{
		// floatÇüµµ °í¹ÎÇØºÁ¾ßÇÔ
		return x == vec.x && y == vec.y;
	}
	bool Vector2::operator!=(const Vector2 & vec)
	{
		return false;
	}
	Vector2 Vector2::operator+(const Vector2 & vec)
	{
		Vector2 temp;
		temp.x = x + vec.x;
		temp.y = y + vec.y;

		return temp;
	}
	Vector2 Vector2::operator-(const Vector2 & vec)
	{
		return Vector2();
	}
	Vector2 Vector2::operator*(float f)
	{
		return Vector2();
	}
}


