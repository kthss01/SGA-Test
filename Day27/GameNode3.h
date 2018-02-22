#pragma once

#include "Image4.h"

class GameNode3
{
private:
	Image4 * m_backBuffer;
	void SetBackBuffer();
public:
	GameNode3();
	~GameNode3();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Image4* GetBackBuffer() { return m_backBuffer; }

	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

