#include "stdafx.h"
#include "GameNode.h"

GameNode::GameNode()
{
	SetBackBuffer();
}


GameNode::~GameNode()
{
}

void GameNode::SetBackBuffer()
{
	m_backBuffer = new Image2;
	m_backBuffer->Init(WINSIZEX, WINSIZEY);
}

HRESULT GameNode::Init()
{
	// 10 이란건 0.01초 마다 WM_TIMER 동작하겠다.
	// 앞에 있는 1은 번호 타이머 여러개 만들 수 있음
	SetTimer(g_hWnd, 1, 10, NULL);	// 컴퓨터에서 1초 1000

	return S_OK;
}

void GameNode::Release()
{
	// 타이머 해제 하는 방법
	KillTimer(g_hWnd, 1);

	SAFE_DELETE(m_backBuffer);

	INPUT->ReleaseSingleton();
}

void GameNode::Update()
{
	// 매번 동작을 하지 않더라도 실행하게 되는 함수

	// 나중에 더블 버퍼링을 쓰면 사용하지 않는다 (나중에 true -> false 로 바꿀꺼)
	//InvalidateRect(g_hWnd, NULL, TRUE);
	
	// 더블 버퍼링으로 쓰면 False로 바꿔야함
	InvalidateRect(g_hWnd, NULL, FALSE);

}

void GameNode::Render(HDC hdc)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	switch (msg) {
	case WM_TIMER:
		this->Update();	// this 붙이게되면 gameNode가 가지고 있는 Update() 할 수 있음
		// this 이름 중첩되는 경우가 있음 상속 되는 경우 부모인지 내껀지 확실하게 하기 위해서 사용
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
		// 창이 순간적으로 삭제 될때, 메모리 부족 또는 오류, 
		// 강력한 백신 같은 경우 코드를 잘못치거나 해서 
		// 오류가 있는거 바이러스로 취급
		// 이때 격리 하는 경우도 있어서

		// 자의적으로 종료하지 않은 경우가 WM_DESTROY 임
	case WM_DESTROY:	
		PostQuitMessage(0);	// 남은 데이터 강제적으로 종료하는거
		break;
	}

	// Default Window Proc 나머지는 Win
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}
