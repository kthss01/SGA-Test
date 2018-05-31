#pragma once

typedef struct tagRay {
	Vector2 origin;
	Vector2 direction;
	tagRay() {
		origin = Vector2(0, 0);
		direction = Vector2(0, 0);
	}
	tagRay(Vector2 origin, Vector2 direction) {
		this->origin = origin;
		this->direction = direction;
	}
} Ray, *LPRay;

class Util
{
public:
	Util();
	~Util();

	// view matrix ��� ���ļ� -1 ~ 1 ���̰� �޴� ��
	static void GetMousePos(Vector2 * out);
	// ��ũ�� �� �޴°�
	static void GetMousePosWithScreen(Vector2 * out);
	static float GetRandomSeed();
	static float RandomFloatRange(float min, float max);
	// value-����� ��, ����� ���� min ���� ������ min���� max���� ũ�� max�� ���ִ�
	// min max ���̰����� ��ȯ
	static float Clamp(float value, float min, float max);
	// value�� ������ 0, 1 ����
	static float Clamp01(float value);
	
};

