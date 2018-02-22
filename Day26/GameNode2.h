#pragma once

#include "Image3.h"

class GameNode2
{
private:
	Image3 * m_backBuffer;
	void SetBackBuffer();
public:
	GameNode2();
	~GameNode2();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Image3* GetBackBuffer() { return m_backBuffer; }

	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

