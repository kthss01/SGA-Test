#include "stdafx.h"
#include "GameNode4.h"


GameNode4::GameNode4()
{
	SetBackBuffer();
}


GameNode4::~GameNode4()
{
}

void GameNode4::SetBackBuffer()
{
	m_backBuffer = new Image5;
	m_backBuffer->Init(WINSIZEX, WINSIZEY);
}

HRESULT GameNode4::Init()
{
	SetTimer(g_hWnd, 1, 10, NULL);

	return S_OK;
}

void GameNode4::Release()
{
	KillTimer(g_hWnd, 1);

	SAFE_DELETE(m_backBuffer);

	INPUT->ReleaseSingleton();
}

void GameNode4::Update()
{
	InvalidateRect(g_hWnd, NULL, FALSE);
}

void GameNode4::Render(HDC hdc)
{
}

LRESULT GameNode4::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) {
	case WM_TIMER:
		this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->Render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}
