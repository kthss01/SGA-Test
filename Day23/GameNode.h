#pragma once

#include "Image2.h"

class GameNode
{
private:
	Image2* m_backBuffer;
	void SetBackBuffer();

public:
	GameNode();
	~GameNode();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Image2* GetBackBuffer() { return m_backBuffer; }

	// WinAPI�� MainProc �� ����
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


// ���߿� SceneManager �� �� �� �������ֽǲ�
// �ϴ��� GameNode�� Game ���� �� �ʿ��� Ŭ���� ���ٰ� �����ϸ� ��
