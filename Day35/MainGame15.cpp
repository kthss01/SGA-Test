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

	_bg->Init("images/메가맨배경.bmp", WINSIZEX, WINSIZEY);

	return S_OK;
}

void MainGame15::Release()
{
	GameNode::Release();

	SAFE_DELETE(_bg);
}

void MainGame15::Update()
{
	GameNode::Update();

	// 검색하고 싶은 범위 (이미지 픽셀의 좌표)
	for (int i = 0; i < 10; i++) {
		// 100, 100 x, y라고 보면 됨
		for (int j = 0; j < _bg->GetHeight(); j++) {
			COLORREF color = GetPixel(_bg->GetMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			// 여기 조건은 본인이 원하는 색을 넣으면 됨
			if (r == 255 && g == 0 && b == 255) {
				// 충돌 처리
			}
		}
	}
}

void MainGame15::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	// 검색하고 싶은 범위 (이미지 픽셀의 좌표)
	for (int i = 0; i < _bg->GetWidth(); i++) {
		// 100, 100 x, y라고 보면 됨
		for (int j = 0; j < _bg->GetHeight(); j++) {
			COLORREF color = GetPixel(_bg->GetMemDC(), i, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			int gray = (r + b + g) / 3;
			SetPixel(memDC, i, j, RGB(gray, gray, gray));
		}
	}
	//_bg->Render(memDC);
	


	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
