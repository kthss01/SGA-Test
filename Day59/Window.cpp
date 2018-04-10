#include "stdafx.h"
#include "Window.h"
#include "GameNode.h"

#include "MainGame.h"

POINT Window::ptMouse = POINT{ 0,0 };
CTRL Window::_currentCTRL = CTRL_TERRAINDRAW;

// define cpp에 하면 여기만 사용 가능하게 됨 include 할때

#define SUBWINSIZEX 400
#define SUBWINSIZEY 600

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

	hParenthWnd = g_hWnd;
	hInst = GetModuleHandle(NULL);

	hWnd = CreateWindow(
		"sub",
		"sub",
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL,
		hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);

	Init();

	m_backBuffer = new Image();
	m_backBuffer->Init(SUBWINSIZEX, SUBWINSIZEY);
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

	// 버튼도 조그만한 윈도우라고 생각하면 됨
	// MFC 문법임 색깔을 바꾸거나 이러긴 힘듬
	// 클릭시 HMENU 메시지 발생
	_btnTerrainDraw = CreateWindow("button", "Terrain",
		// 자식으로 생성하면 안쪽에 만들어짐
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		// 클릭했을때 어떤 값을 반환할지 hMenu
		280, 50, 100, 20, hWnd, HMENU(0), g_hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "Object",
		// 자식으로 생성하면 안쪽에 만들어짐
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		// 클릭했을때 어떤 값을 반환할지 hMenu
		280, 80, 100, 20, hWnd, HMENU(1), g_hInstance, NULL);
	_btnEraser = CreateWindow("button", "Eraser",
		// 자식으로 생성하면 안쪽에 만들어짐
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		// 클릭했을때 어떤 값을 반환할지 hMenu
		280, 110, 100, 20, hWnd, HMENU(2), g_hInstance, NULL);

	_btnSave = CreateWindow("button", "Save",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		280, 140, 100, 20, hWnd, HMENU(3), g_hInstance, NULL);

	_btnLoad = CreateWindow("button", "Load",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		280, 170, 100, 20, hWnd, HMENU(4), g_hInstance, NULL);
	isActive = false;
}

void Window::Release()
{

}

void Window::Update()
{
	if (isActive &&
		INPUT->GetKeyDown(VK_LBUTTON)) {
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

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = cx;
	rc.bottom = cy;

	AdjustWindowRect(&rc, WINSTYLE, FALSE);

	SetWindowPos(hWnd, NULL, x, y,
		(rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER);

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
		SUBWIN->SetIsActive(true);
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
	case WM_COMMAND:
		// 프로그램 실행 중 사용자가 메뉴 항목을 선택하면 발생하는 메세지
		switch (LOWORD(wParam))
		{
		default:
			//// 클릭했을 때 0,1,2 값 중 하나가 들어옴 
			//_currentCTRL = (CTRL)(LOWORD(wParam));
			switch (LOWORD(wParam)) {
			case CTRL_TERRAINDRAW:
			case CTRL_OBJECTDRAW:
			case CTRL_ERASER:
				_currentCTRL = (CTRL)(LOWORD(wParam));
				break;
			case CTRL_SAVE:
				SUBWIN->GetMainGame()->Save();
				break;
			case CTRL_LOAD:
				SUBWIN->GetMainGame()->Load();
				break;
			}
			break;
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