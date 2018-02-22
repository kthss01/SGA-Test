#pragma once

#include "Image5.h"

class GameNode4
{
private:
	Image5 * m_backBuffer;
	void SetBackBuffer();
public:
	GameNode4();
	~GameNode4();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	Image5* GetBackBuffer() { return m_backBuffer; }

	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

