#pragma once

namespace MyDirectX {
	struct Vector2 {
		float x, y;

		Vector2();
		Vector2(float x, float y);

		bool operator== (const Vector2& vec);
		bool operator!= (const Vector2& vec);

		Vector2 operator+(const Vector2& vec);
		Vector2 operator-(const Vector2& vec);
		Vector2 operator*(float f);
	};

}

// 과제 연산자 마저 채우기