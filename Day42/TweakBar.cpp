#include "stdafx.h"
#include "TweakBar.h"


TweakBar::TweakBar()
{
}


TweakBar::~TweakBar()
{
	TwTerminate(); // TweakBar 종료 시키는 함수
}

void TweakBar::Init(HDC hdc)
{
	isDraw = false;
	bool result = TwInit(TW_DIRECT3D9, hdc);

	if (result == false) {
		// MessageBox 게임 오류있을 때 창 뜨는거 같은거
		// handle값 안넣어도 상관은 없음
		// Error 메세지 박스 창 이름 그 다음은 내용 메세지박스 타입 (보통 MB_OK면 됨)
		MessageBox(g_hWnd, "Error", "TweakBar Initialize failed", MB_OK);
	}

	bar = TwNewBar("TweakBar");
	// tweakBar 색상 설정
	TwDefine("TweakBar color='0 128 255' alpha=128");
	// tweakBar 사이즈 설정
	TwDefine("TweakBar size='250 700'");
	// 값의 너비값
	TwDefine("TweakBar valueswidth=120");
	TwDefine("TweakBar visible=false");
}

void TweakBar::InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// event는 행동을 취했을 때 결과가 있는거
	// ex) 마우스 클릭 이벤트
	TwEventWin(hwnd, msg, wParam, lParam);
}

void TweakBar::Render()
{
	TwDraw();
}
