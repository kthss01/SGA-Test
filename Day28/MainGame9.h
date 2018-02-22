#pragma once

#include "GameNode4.h"

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

class MainGame9 : public GameNode4
{
private:
	tagBall m_ball;
	tagRacket m_racket[2];
	RECT m_coat[2];
	RECT m_goal[2];
	int m_score[2];
	char m_score1[24];	// 점수를 화면에 띄우는 문자열
	char m_score2[24];	// 점수를 화면에 띄우는 문자열

public:
	MainGame9();
	~MainGame9();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void BallMove();
	void Smash();
};

/*
	주말 과제

	1. 지렁이 게임
	움직이면 꼬리 늘어나는 게임
	우선
	원 50 개 만들어서 이어져서  
	방향키로 움직일 수 있게 (좌 우만 필요)
	겹치지말고 떨어지게 끔
	화면 경계 나가면 안됨

	2. 포탄 발사
	화면이 있으면 
	가운데 대포처럼 생긴 반원 있음
	포신이 직각으로 내려가지는 않음 살짝 뜸
	포신 있음 가운데 대포 움직임
	스페이스 누르면 그 각도로 원 모양에 총 발사
	화면 경계에서 충돌
	자기들끼리 부딪쳐도 충돌
	총알 2개 3개 계속 발사 할 수 있음
	원끼리 충돌은 for문으로 모두 검사해야됨 매 update마다
	화면 경계 나가면 안됨

	3. 사과 떨구기
	오른쪽에 사과 나무 잇음
	왼쪽에 탱크 (사각형 원 머리 포신 있음) 발사 시
	포물선으로 날라가야됨
	
	중력 처리 해주면됨
	두가지 방식
	날라가는 순간 중력 감소
	어느 속도까지 날라가다 최고 속도 이후부터 중력 감소

	사과 랑 부딪치면 떨어지고 포탄 사라짐
	사각형과 원 충돌은 조금 다름 (모서리 충돌일때 길이가 좀 다름)
	사과는 원으로 처리하는게 좋음
	사과는 바닥에 부딪치면 사라짐

	난이도 추가 파워 게이지
	누르고 있음 더 멀리 날아가게
*/