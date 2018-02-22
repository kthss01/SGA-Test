#pragma once

#include "GameNode2.h"

/*
	�ﰢ�Լ�
	sin, cos
	cos �̿��ϸ� ����
	sin �̿��ϸ� �غ�
	tan �� ��� ���� ����

	��ǻ�� cos, sin �� �׷���
	sin 0 = 0 sin Pi/2 = 1
	cos 0 = 1 cos Pi = 1;

	acos �̿��ϸ� �� ���� ������ ���� �� ����

	PI = 180��(degree) (�ݿ�)
	PI = 3.14159~

	1 degree = 1 / 180 * PI = 0.0147~

	1 radian = ������ �������� 57.3�� = �� 60��
	1 radian = 57.3

	�ܿ����� �κ�
	****************************************
	x = cos(���� * PI / 180) * �ӵ�(�Ÿ�)
	y = -sin(���� * PI / 180) * �ӵ�(�Ÿ�)
	****************************************


	��Ÿ����� ����
	x^2 + y^2 = d^2 (d ����)
	*���� ������ �浹���� �� �ʿ�

	���� �� �浹 �� �� ���������� �Ÿ� �˾ƾ���
	�� ������ �̿��� �ﰢ�� �׷��� ������ ���ؾ��ؼ�

	�� ���̰� �� ���� �������� �պ��� ª���� �浹�ߴٰ� �Ǵ�

	=================== ���� ===============
	�� �� ������ �Ÿ� ���ϰ� ������

	distance (�ﰢ���� ����) ���ؾ� ��
	radius(������)

	circle(X1, Y1, radius1) (X2, Y2, radius2) (�� �ΰ� ���� ��)
	�浹 ���� Ȯ��

	deltaX = X2-X1
	deltaY = Y2-Y1
	distance^2 = deltaX^2 + deltaY^2

	sqrt(��ȯ ������ ���ִ� ��Ʈ) or sqrtf(�Ǽ� ��Ʈ)

	(���߿� 3D���� ������ �浹�� ������ ����)
	radius1 + radius2 > distance -> �� �浹


*/

// �δ��� ���
// ������ ������ �༮ �Ǵ�
enum CURRENTRECT {
	CURRENTRECT_0,
	CURRENTRECT_1,
	CURRENTRECT_2,
	CURRENTRECT_3,
	CURRENTRECT_4,
	CURRENTRECT_5,
	CURRENTRECT_6,
	CURRENTRECT_7,
	CURRENTRECT_NULL,
};

class MainGame7 : public GameNode2
{
private:
	CURRENTRECT _currentRect;
	RECT _rc[8];
	DWORD _prevTime;
	DWORD _curTime;

	int _time;
	int _score;
	int _index;

	bool _isSelected;
	bool _isOnceCheck;

	float _timeScale;	// 1000���� 1�� ������ �������� �༮

	//RECT rc[2];

	//// ���� ��ǻ�Ϳ� ��ϵǾ��մ� �ð� ������ ���� ����ü
	//SYSTEMTIME st;
public:
	MainGame7();
	~MainGame7();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	bool isCollision();
};