#pragma once

#include "SIngletonBase.h"

#define SUBWINSIZEX 256
#define SUBWINSIZEY 640

class Window : public SingletonBase<Window>
{
private:
	HWND hWnd;
	static POINT ptMouse;

	Image * m_backBuffer;
	GameNode * currentScene;

	RECT rc[8][20];
	POINT clickFrame;
public:
	Window();
	~Window();

	void Init();
	void Release();
	void Update();
	void Render();
	void SetScene(GameNode* scene);
	static LRESULT CALLBACK WndLogProc(HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

	POINT GetFramePoint() { return clickFrame; }
	static POINT GetMousePos() { return ptMouse; }

	void SetWindowSize(int x, int y, int width, int height);
};

#define SUBWIN Window::GetSingleton()
