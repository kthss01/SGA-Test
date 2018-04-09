#include "stdafx.h"
#include "Window.h"
#include "GameNode.h"

POINT Window::ptMouse = POINT{ 0,0 };

Window::Window()
{
	// 로그 윈도우 생성
	int x, y, cx, cy;
	WNDCLASS wc;
	RECT rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)Window::WndLogProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "sub";

	RegisterClass(&wc);

	// 부모 윈도우 오른쪽에 위치하게
	RECT rcWin;
	GetWindowRect(g_hWnd, &rcWin);

	cx = 250;
	cy = 600;
	x = rcWin.right;
	y = rcWin.top;

	HWND		hParenthWnd = NULL;
	HINSTANCE	hInst = NULL;

	hWnd = CreateWindow(
		"sub",
		"sub",
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL,
		hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);

	Init();

	m_backBuffer = new Image();
	m_backBuffer->Init(250, 600);
}


Window::~Window()
{
	SAFE_DELETE(m_backBuffer);
}

void Window::Init()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 20; j++) {
			rc[i][j] = RectMake(i * 32, j * 32, 32, 32);
		}
	}
	clickFrame = { 0,0 };
}

void Window::Release()
{

}

void Window::Update()
{
	if (INPUT->GetKeyDown(VK_RBUTTON)) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 20; j++) {
				if (PtInRect(&rc[i][j], ptMouse)) {
					clickFrame = { i, j };
				}
			}
		}
	}

	/////////////////////////////////////
	int x, y, cx, cy;

	RECT rcWin;
	GetWindowRect(g_hWnd, &rcWin);

	cx = SUBWINSIZEX;
	cy = SUBWINSIZEY;
	x = rcWin.right;
	y = rcWin.top;

	SetWindowPos(hWnd, NULL, x, y, cx, cy, 0);

	//AdjustWindowRect(&rcWin, WINSTYLE, FALSE);

	//SetWindowPos(hWnd, NULL, x, y,
	//	(rcWin.right - rcWin.left), (rcWin.bottom - rcWin.top), SWP_NOZORDER | SWP_NOMOVE);

	if (currentScene != NULL)
	{
		currentScene->Update();
	}
}

void Window::Render()
{
	HDC hdc = GetDC(hWnd);
	PatBlt(m_backBuffer->GetMemDC(), 0, 0, SUBWINSIZEX, SUBWINSIZEY, WHITENESS);
	//==============================
	if (currentScene != NULL)
	{
		currentScene->Render(m_backBuffer->GetMemDC());
	}
	IMAGE->Render("tileMap", m_backBuffer->GetMemDC(), 0, 0);



	//=============================
	m_backBuffer->Render(hdc);
	ReleaseDC(hWnd, hdc);
}

void Window::SetScene(GameNode * scene)
{
	currentScene = scene;
	currentScene->Init();
}

LRESULT Window::WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_MOUSEMOVE:
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		break;
	case WM_PAINT:
	{
		//HDC hdc = GetDC(hWnd);
		//IMAGE->FindImage("sub_bg")->Render(hdc);
		//ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::SetWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = SUBWINSIZEX;
	rc.bottom = SUBWINSIZEY;

	AdjustWindowRect(&rc, WINSTYLE, FALSE);

	SetWindowPos(hWnd, NULL, x, y,
		(rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}
