#pragma once

#include "GameNode.h"

class MainGame15 : public GameNode
{
private:
	Image* _ball;	// 움직일 이미지
	Image* _bg;		// 충돌 계산을 할 이미지

	float _x, _y;	// 위치
	int _probeY;	// 탐지 범위

	RECT _rc;
public:
	MainGame15();
	~MainGame15();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

/*
	기본적 픽셀 검사
	화면에 띄울 녀석(DC), 계산을 할 녀석(DC)으로 구분 이미지 DC가 두개
*/

/*
	과제

	계단 이미지 (만들거나 구해서)
	횡으로 보이는 계단
	일정 높이 미만의 계단은 올라갈 수 있게 만들기

	이미지 2장 필요
	(계단 렌더링용 픽셀 충돌용)

	캐릭터가 있음
	점프키 없이 왼쪽 오른쪽으로 이동
	이동했을 때 일정 높이 (내가 설정한 높이)보다 낮으면 올라감
	(픽셀 충돌하는 방법 활용)
	높으면 못 올라감
	왼쪽키 누르면 떨어지게
*/

