#pragma once

namespace MyDirectX {
	struct Vector2 {
		// 2D �� �Ϸ��� �������� �ʹ� �򰥷��� 
		// 3D�� �ϴ´�� z���� 0���� �ؼ� �Ϸ��� �Ͻ�
		float x, y, z = 0;

		Vector2();
		Vector2(float x, float y);

		bool operator== (const Vector2& vec);
		bool operator!= (const Vector2& vec);

		Vector2 operator+(const Vector2& vec);
		Vector2 operator-(const Vector2& vec);
		Vector2 operator*(float f);	// ��Į�� ��

		float Length();
		Vector2 Normalize();	// ���̸� 1�� �ٲ��ִ°�

		static float Dot(Vector2& v1, Vector2& v2);	// ����
		static Vector2 Cross(Vector2& v1, Vector2& v2); // ����

														// Coord ��ġ���� ��Ÿ���� �༮�̶�� ����� position �̶�� �ϴ���
														// Transform ũ�� (Scale), ��ġ(Position), ȸ��(Lotate)
														// �� ���� ���Ŷ�� ���� ��
														// matrix�� ���ؼ� ��ġ�� �̵��ϴ°� Coord
		Vector2 TransformCoord(class Matrix& mat);
		// matrix�� ���ؼ� ��(����)�� ȸ���ϴ°� Normal
		Vector2 TransformNormal(class Matrix& mat);
	};

}

// ���� ������ ���� ä���