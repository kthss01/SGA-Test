#pragma once

namespace MyDirectX {
	struct Vector2 {
		// 2D 로 하려니 선생님이 너무 헷갈려서 
		// 3D로 하는대신 z값을 0으로 해서 하려고 하심
		float x, y, z = 0;

		Vector2();
		Vector2(float x, float y);

		bool operator== (const Vector2& vec);
		bool operator!= (const Vector2& vec);

		Vector2 operator+(const Vector2& vec);
		Vector2 operator-(const Vector2& vec);
		Vector2 operator*(float f);	// 스칼라 곱

		float Length();
		Vector2 Normalize();	// 길이를 1로 바꿔주는거

		static float Dot(Vector2& v1, Vector2& v2);	// 내적
		static Vector2 Cross(Vector2& v1, Vector2& v2); // 외적

														// Coord 위치값을 나타내는 녀석이라고 보면됨 position 이라고 하던거
														// Transform 크기 (Scale), 위치(Position), 회전(Lotate)
														// 세 값이 들어간거라고 보면 됨
														// matrix에 의해서 위치가 이동하는게 Coord
		Vector2 TransformCoord(class Matrix& mat);
		// matrix에 의해서 축(방향)이 회전하는게 Normal
		Vector2 TransformNormal(class Matrix& mat);
	};

}

// 과제 연산자 마저 채우기