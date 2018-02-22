#pragma once

#include "GameNode.h"

// �� ���ϱ�
#define BULLETMAX 50

struct tagBullet {
	RECT rc;
	int x, y;	// top, bottom���� ������ �������� ������ ��ǥ �̵� x y �̿�
	float speed;
};

class MainGame6 : public GameNode
{
private:
	//RECT rc[5];
	//
	//int count;
	//
	//float prevTime;
	//float currentTime;

	RECT m_player;
	tagBullet m_bullet[BULLETMAX];
	int m_score;

public:
	MainGame6();
	~MainGame6();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

// ������ ���⼭
