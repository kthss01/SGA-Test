#include "stdafx.h"
#include "MainGame15.h"


MainGame15::MainGame15()
{
}


MainGame15::~MainGame15()
{
}

HRESULT MainGame15::Init()
{
	GameNode::Init();

	_bg = new Image;

	// 픽셀 충돌이 렉트 충돌보다 더 정확하게 할 수 있음
	// 그러나 문제점이 렉트 충돌보다 계산이 느림

	_bg->Init("images/mountain.bmp", 800, 600, true, RGB(255,0,255));

	_ball = new Image;
	_ball->Init("images/ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 - 30;

	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());

	_probeY = _y + _ball->GetHeight() / 2;

	return S_OK;
}

void MainGame15::Release()
{
	GameNode::Release();

	SAFE_DELETE(_bg);
	SAFE_DELETE(_ball);
}

void MainGame15::Update()
{
	GameNode::Update();

	if (INPUT->GetKey(VK_LEFT)) {
		_x -= 2.0f;
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		_x += 2.0f;
	}
	_probeY = _y + _ball->GetHeight() / 2;

	// 검색하고 싶은 범위 (이미지 픽셀의 좌표)
	for (int i = _probeY - 10; i < _probeY + 10; i++) {

		COLORREF color = GetPixel(_bg->GetMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// 여기 조건은 본인이 원하는 색을 넣으면 됨
		if (!(r == 255 && g == 0 && b == 255)) {
			// 마젠타 값이 아닐때 위로 올릴꺼
			_y = i - _ball->GetHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _ball->GetWidth(), _ball->GetHeight());
}

void MainGame15::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		_bg->Render(memDC);
		_ball->Render(memDC, _rc.left, _rc.top);
	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
