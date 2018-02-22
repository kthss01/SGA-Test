#pragma once

#include "GameNode.h"

// 똥 피하기
#define BULLETMAX 50

struct tagBullet {
	RECT rc;
	int x, y;	// top, bottom으로 내리기 귀찮으니 실질적 좌표 이동 x y 이용
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

// 선언은 여기서
