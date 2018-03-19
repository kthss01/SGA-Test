#include "stdafx.h"
#include "TweakBar.h"


TweakBar::TweakBar()
{
}


TweakBar::~TweakBar()
{
	TwTerminate(); // TweakBar ���� ��Ű�� �Լ�
}

void TweakBar::Init(HDC hdc)
{
	isDraw = false;
	bool result = TwInit(TW_DIRECT3D9, hdc);

	if (result == false) {
		// MessageBox ���� �������� �� â �ߴ°� ������
		// handle�� �ȳ־ ����� ����
		// Error �޼��� �ڽ� â �̸� �� ������ ���� �޼����ڽ� Ÿ�� (���� MB_OK�� ��)
		MessageBox(g_hWnd, "Error", "TweakBar Initialize failed", MB_OK);
	}

	bar = TwNewBar("TweakBar");
	// tweakBar ���� ����
	TwDefine("TweakBar color='0 128 255' alpha=128");
	// tweakBar ������ ����
	TwDefine("TweakBar size='250 700'");
	// ���� �ʺ�
	TwDefine("TweakBar valueswidth=120");
	TwDefine("TweakBar visible=false");
}

void TweakBar::InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// event�� �ൿ�� ������ �� ����� �ִ°�
	// ex) ���콺 Ŭ�� �̺�Ʈ
	TwEventWin(hwnd, msg, wParam, lParam);
}

void TweakBar::Render()
{
	TwDraw();
}
