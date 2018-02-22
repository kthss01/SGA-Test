#pragma once

#include "GameNode3.h"

// �ð� Ǯ��
struct tagArrow {
	POINT endPosition;
	int length;
	float angle;
};

/*
	�� �� ������ ���� ���ϴ� ���
	deltaX �� �� x �� ��
	distance �� �� ������ �Ÿ�
	float angle = acos(deltaX / distance);
*/

struct tagBullet{
	RECT rc;
	bool isFire;
	int x, y;
};

#define BULLETMAX 100

/*
	���α� �̵� �ٽ� �����ϴ°�
	������ � �̿��ؼ� �ϴ°�
*/

class MainGame8 : public GameNode3
{
private:
	tagBullet _bullet[BULLETMAX];

	RECT _player;

	RECT rc[2];

	//tagArrow arrow[3];		// 0 �� 1 �� 2 �ð�
	//POINT startPosition;	// ��ü�� ��������, ħ���� ��� ���̴� ��
	//SYSTEMTIME st;
public:
	MainGame8();
	~MainGame8();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	bool Collision();
	float GetAngle();
};


/*
	����
	������Ű 2�ο�
	wasd TOP, RIGHT, BOTTOM, LEFT
	��ǻ�� �Ǵ� 2�� �÷��� �����Ӱ�
	���� �Ѿ�� �ȵ�

	�ðܳ����°� ����� �ðܳ����� �ص� ��

	�浹���� �� �ðܳ��;���
	���� ����
	���� �����°� �浹�� ���ӵ��� ��뿡�� �����ָ��

	�浹�� ������ 2PI���� ���ܵ�

	���� ���߿� �������⵵ �ؾ���
*/