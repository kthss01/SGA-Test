#pragma once

#include "GameNode2.h"

/*
	삼각함수
	sin, cos
	cos 이용하면 높이
	sin 이용하면 밑변
	tan 은 사용 할일 없음

	컴퓨터 cos, sin 은 그래프
	sin 0 = 0 sin Pi/2 = 1
	cos 0 = 1 cos Pi = 1;

	acos 이용하면 두 점의 각도를 구할 수 있음

	PI = 180도(degree) (반원)
	PI = 3.14159~

	1 degree = 1 / 180 * PI = 0.0147~

	1 radian = 원에서 반지름과 57.3도 = 약 60도
	1 radian = 57.3

	외워야할 부분
	****************************************
	x = cos(각도 * PI / 180) * 속도(거리)
	y = -sin(각도 * PI / 180) * 속도(거리)
	****************************************


	피타고라스의 정의
	x^2 + y^2 = d^2 (d 빗변)
	*원과 원끼리 충돌했을 때 필요

	원과 원 충돌 때 두 원점에서의 거리 알아야함
	두 중점을 이용해 삼각형 그려서 빗변을 구해야해서

	이 길이가 두 원의 반지름의 합보다 짧으면 충돌했다고 판단

	=================== 예제 ===============
	두 점 사이의 거리 구하고 싶으면

	distance (삼각형의 빗변) 구해야 함
	radius(반지름)

	circle(X1, Y1, radius1) (X2, Y2, radius2) (원 두개 있을 때)
	충돌 여부 확인

	deltaX = X2-X1
	deltaY = Y2-Y1
	distance^2 = deltaX^2 + deltaY^2

	sqrt(반환 정수로 해주는 루트) or sqrtf(실수 루트)

	(나중에 3D에서 구끼리 충돌도 동일한 원리)
	radius1 + radius2 > distance -> 원 충돌


*/

// 두더지 잡기
// 색상을 가지는 녀석 판단
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

	float _timeScale;	// 1000분의 1초 값으로 수정해줄 녀석

	//RECT rc[2];

	//// 현재 컴퓨터에 등록되어잇는 시간 정보를 가진 구조체
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