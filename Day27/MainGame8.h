#pragma once

#include "GameNode3.h"

// 시계 풀이
struct tagArrow {
	POINT endPosition;
	int length;
	float angle;
};

/*
	두 점 사이의 각도 구하는 방법
	deltaX 두 점 x 의 차
	distance 두 점 사이의 거리
	float angle = acos(deltaX / distance);
*/

struct tagBullet{
	RECT rc;
	bool isFire;
	int x, y;
};

#define BULLETMAX 100

/*
	갤로그 이따 다시 정렬하는거
	베지어 곡선 이용해서 하는거
*/

class MainGame8 : public GameNode3
{
private:
	tagBullet _bullet[BULLETMAX];

	RECT _player;

	RECT rc[2];

	//tagArrow arrow[3];		// 0 초 1 분 2 시간
	//POINT startPosition;	// 구체의 시작지점, 침들의 가운데 모이는 점
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
	과제
	에어하키 2인용
	wasd TOP, RIGHT, BOTTOM, LEFT
	컴퓨터 또는 2인 플레이 자유롭게
	반은 넘어가면 안됨

	팅겨나가는건 맘대로 팅겨나가게 해도 됨

	충돌햇을 때 팅겨나와야함
	골대는 들어가고
	세개 나가는건 충돌시 내속도를 상대에게 더해주면됨

	충돌시 각도를 2PI에서 빼줌됨

	참고 나중에 벽돌깨기도 해야함
*/