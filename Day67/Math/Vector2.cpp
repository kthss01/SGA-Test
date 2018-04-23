#include "stdafx.h"
#include "Vector2.h"

#define EPSILON 0.001f

namespace MyDirectX {
	Vector2::Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	bool Vector2::operator==(const Vector2 & vec)
	{
		if (x - vec.x > EPSILON || y - vec.y > EPSILON) return false;
		return true;
	}
	bool Vector2::operator!=(const Vector2 & vec)
	{
		if (x - vec.x > EPSILON || y - vec.y > EPSILON) return true;
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
		Vector2 temp;
		temp.x = x - vec.x;
		temp.y = y - vec.y;
		return temp;
	}
	Vector2 Vector2::operator*(float f)
	{
		Vector2 temp;
		temp.x = x * f;
		temp.y = y * f;
		return temp;
	}
}


