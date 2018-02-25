#pragma once

#include "GameNode.h"

// 에어 하키
#define RACKET_SPEED 5

struct tagBall {
	float x, y;
	float angle;
	float speed;
	float radius;
	bool smash;
};

struct tagRacket {
	float x, y;
	float angle;
	float radius;
};

class MainGame10 : public GameNode
{
private:
	tagBall m_ball;
	tagRacket m_racket[2];
	RECT m_coat[2];
	RECT m_goal[2];
	int m_score[2];
	char m_score1[24];
	char m_score2[24];
public:
	MainGame10();
	~MainGame10();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void BallMove();
	void Smash();
};

