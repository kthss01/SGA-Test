#include "stdafx.h"
#include "MainGame7.h"

// 비주얼스튜디오에 기본적으로 sin cos 이런거 있지만
// #include <math.h> 하면 수학 관련 함수들 들어있다. sin cos 같은거

MainGame7::MainGame7()
{
}


MainGame7::~MainGame7()
{
}

HRESULT MainGame7::Init()
{
	GameNode2::Init();

	_currentRect = CURRENTRECT_NULL;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			_rc[i * 4 + j] = RectMakeCenter(
				200 + j * 200, 200 + i * 200, 100, 100);
		}
	}

	_time = RND->GetFromInto(3, 5);
	_prevTime = GetTickCount();
	_timeScale = 1 / 1000;
	_score = 0;
	_index = 0;
	_isSelected = false;
	_isOnceCheck = false;

	//rc[0] = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 100, 100);
	//rc[1] = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 100, 100);

	return S_OK;
}

void MainGame7::Release()
{
	GameNode2::Release();
}

void MainGame7::Update()
{
	GameNode2::Update();

	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		if (PtInRect(&_rc[_index], g_ptMouse) && !_isOnceCheck) {
			_score += 100;
			_isOnceCheck = true;
		}
	}

	if (_isSelected == false) {
		// 두더지가 없다
		if ((_curTime - _prevTime )> _time * 1000 ) {
			// 일정 시간이 지났으면
			_isOnceCheck = false;		// 중복 클릭 방지
			_prevTime = GetTickCount();
			_index = RND->GetInt(8);
			_currentRect = (CURRENTRECT)_index;
			_isSelected = true;
			_time = RND->GetFromInto(3, 5);
		}
	}
	else {
		// 두더지 있다
		if ((_curTime - _prevTime )> _time * 1000) {
			// 일정 시간이 지났으면
			_isSelected = false;
			_isOnceCheck = false;
			_currentRect = CURRENTRECT_NULL;
			_time = RND->GetFromInto(3, 5);
			_prevTime = GetTickCount();
			_index = -1;	// 두더지가 사라졌을 때 인덱스 바꿔주는거
		}
	}

	_curTime = GetTickCount();

	
	//// 각도에 따라 달라짐
	//// 각도는 사분면에서 왼쪽으로 회전하는 거임 

	//if (INPUT->GetKey(VK_LBUTTON)) {
	//	rc[0] = RectMakeCenter(g_ptMouse.x, g_ptMouse.y, 100, 100);
	//}


	//// 이에 대한 문제 해결 필요 -> 해결 함 충돌 함수에서 delatY 값쪽 계산 오타
	//if (INPUT->GetToggleKey(VK_SPACE)) {
	//	rc[0].left += cos(0 * PI / 180) * 3.0f;
	//	rc[0].right += cos(0 * PI / 180) * 3.0f;
	//	rc[0].top += -sin(0 * PI / 180) * 3.0f;
	//	rc[0].bottom += -sin(0 * PI / 180) * 3.0f;
	//}

	//if (isCollision() == true) {
	//	rc[1].left += cos(45.0f * PI / 180) * 3.0f;
	//	rc[1].right += cos(45.0f * PI / 180) * 3.0f;
	//	rc[1].top += -sin(45.0f * PI / 180) * 3.0f;
	//	rc[1].bottom += -sin(45.0f * PI / 180) * 3.0f;
	//}

	//GetLocalTime(&st);
}

void MainGame7::Render(HDC hdc)
{
	for (int i = 0; i < CURRENTRECT_NULL; i++) {
		Rectangle(hdc, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}

	if (_isSelected == true) {
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(hdc, &_rc[_index], brush);
		DeleteObject(brush);
	}

	char str[128];
	sprintf_s(str, "Scroe : %d", _score);
	TextOut(hdc, 10, 10, str, strlen(str));

	sprintf_s(str, "x : %d, y : %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, 10, 30, str, strlen(str));

	//char str[128];
	//sprintf_s(str, "%d시 %d분 %d 초", st.wHour, st.wMinute, st.wSecond);
	//TextOut(hdc, 10, 10, str, strlen(str));

	//sprintf_s(str, "%d %d %d %d", rc[0].left, rc[0].top, rc[0].right, rc[0].bottom);
	//TextOut(hdc, 30, 30, str, strlen(str));

	//sprintf_s(str, "%d %d %d %d", rc[1].left, rc[1].top, rc[1].right, rc[1].bottom);
	//TextOut(hdc, 30, 50, str, strlen(str));

	//if (isCollision())
	//	TextOut(hdc, 0, 0, "test", strlen("test"));

	//for (int i = 0; i < 2; i++)
	//	Ellipse(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
	
}

bool MainGame7::isCollision()
{
	//int circleX1 = rc[0].left + (rc[0].right - rc[0].left) / 2;	 // 너비의 절반 더한거
	//int circleY1 = rc[0].top + (rc[0].bottom - rc[0].top) / 2;	 // 높이의 절반 더한거

	//int circleX2 = (rc[1].left + rc[1].right) / 2;	// 이 값도 같은 값
	//int circleY2 = (rc[1].top + rc[1].bottom) / 2;	// 이 값도 같은 값

	//int deltaX = circleX2 - circleX1;
	//int deltaY = circleY2 - circleY1;

	//int distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	//// 반지름 각각 50
	//if ((50 + 50) > distance)
	//	return true;

	return false;
}

/*
	숙제

	아날로그 시계 만들기

	시 분 초 세가지 필요
	
	시
	분
	초
	길이 다르게 해서 시간 만들기

	힌트 시간 분 초 0으로 초기화됨 이거에 대한 처리 필요

	촬영할 때는 시계 띄어놓고 하자

	바늘에 따라 색깔 다르게 하길 추천

	이번 주 금요일 휴강
*/