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

	// WinAPI에 MainProc 와 같음
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


// 나중에 SceneManager 할 때 더 설명해주실꺼
// 일단은 GameNode는 Game 돌릴 때 필요한 클래스 들어간다고 생각하면 됨
