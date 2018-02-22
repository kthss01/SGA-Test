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
	// 10 �̶��� 0.01�� ���� WM_TIMER �����ϰڴ�.
	// �տ� �ִ� 1�� ��ȣ Ÿ�̸� ������ ���� �� ����
	SetTimer(g_hWnd, 1, 10, NULL);	// ��ǻ�Ϳ��� 1�� 1000

	return S_OK;
}

void GameNode::Release()
{
	// Ÿ�̸� ���� �ϴ� ���
	KillTimer(g_hWnd, 1);

	SAFE_DELETE(m_backBuffer);

	INPUT->ReleaseSingleton();
}

void GameNode::Update()
{
	// �Ź� ������ ���� �ʴ��� �����ϰ� �Ǵ� �Լ�

	// ���߿� ���� ���۸��� ���� ������� �ʴ´� (���߿� true -> false �� �ٲܲ�)
	//InvalidateRect(g_hWnd, NULL, TRUE);
	
	// ���� ���۸����� ���� False�� �ٲ����
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
		this->Update();	// this ���̰ԵǸ� gameNode�� ������ �ִ� Update() �� �� ����
		// this �̸� ��ø�Ǵ� ��찡 ���� ��� �Ǵ� ��� �θ����� ������ Ȯ���ϰ� �ϱ� ���ؼ� ���
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
		// â�� ���������� ���� �ɶ�, �޸� ���� �Ǵ� ����, 
		// ������ ��� ���� ��� �ڵ带 �߸�ġ�ų� �ؼ� 
		// ������ �ִ°� ���̷����� ���
		// �̶� �ݸ� �ϴ� ��쵵 �־

		// ���������� �������� ���� ��찡 WM_DESTROY ��
	case WM_DESTROY:	
		PostQuitMessage(0);	// ���� ������ ���������� �����ϴ°�
		break;
	}

	// Default Window Proc �������� Win
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}
