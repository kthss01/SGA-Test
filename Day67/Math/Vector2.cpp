#include "stdafx.h"
#include "Vector2.h"

#include "Matrix.h"

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
		if (fabsf(this->x - vec.x) > EPSILON) return false;
		if (fabsf(this->y - vec.y) > EPSILON) return false;
		return true;
	}
	bool Vector2::operator!=(const Vector2 & vec)
	{

		return !(*this == vec);
	}
	Vector2 Vector2::operator+(const Vector2 & vec)
	{
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 Vector2::operator-(const Vector2 & vec)
	{
		return Vector2(x - vec.x, y - vec.y);
	}
	Vector2 Vector2::operator*(float f)
	{
		return Vector2(x * f, y * f);
	}
	float Vector2::Length()
	{
		// 피타고라스의 정의 사용하면 됨
		return sqrtf(x*x + y * y);;
	}
	Vector2 Vector2::Normalize()
	{
		float len = Length();
		return Vector2(x / len, y / len);
	}
	float Vector2::Dot(Vector2 & v1, Vector2 & v2)
	{
		// cos로도 계산 할 수 잇음
		return (v1.x * v2.x) + (v1.y * v2.y);
	}
	Vector2 Vector2::Cross(Vector2 & v1, Vector2 & v2)
	{
		Vector2 temp;
		temp.x = v1.y * v2.z - v1.z * v2.y;
		temp.y = v1.z * v2.x - v1.x * v2.z;
		temp.x = v1.x * v2.y - v1.z * v2.x;

		return temp;
	}
	Vector2 Vector2::TransformCoord(Matrix & mat)
	{
		Vector2 temp;

		temp.x = mat[0][0] * x + mat[1][0] * y + mat[2][0] * z + mat[3][0];
		temp.y = mat[0][1] * x + mat[1][1] * y + mat[2][1] * z + mat[3][1];
		temp.z = mat[0][2] * x + mat[1][2] * y + mat[2][2] * z + mat[3][2];
		// 동치 좌표였던가 그럼 찾아보자
		float w = mat[0][3] * x + mat[1][3] * y + mat[2][3] * z + mat[3][3];

		if (fabs(w) > EPSILON) {
			temp.x /= w;
			temp.y /= w;
			temp.z /= w;
		}

		return temp;
	}
	Vector2 Vector2::TransformNormal(Matrix & mat)
	{
		Vector2 temp;
		temp.x = mat[0][0] * x + mat[1][0] * y + mat[2][0] * z;
		temp.y = mat[0][1] * x + mat[1][1] * y + mat[2][1] * z;
		temp.z = mat[0][2] * x + mat[1][2] * y + mat[2][2] * z;

		return temp;
	}
}


