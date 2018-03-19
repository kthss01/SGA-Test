#pragma once

#include "SingletonBase.h"

class TweakBar : public SingletonBase<TweakBar>
{
private:
	bool isDraw;
	TwBar* bar;
public:
	TweakBar();
	~TweakBar();

	void Init(HDC hdc);
	void InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Render();

	void GetDraw(bool* isDraw) { *isDraw = this->isDraw; }
	void SetDraw(bool isDraw) { 
		this->isDraw = isDraw; 

		if (isDraw == true)
			// 문자열 비교로 하는거니 값 변경시키니 오타 나면 안됨
			TwDefine("TweakBar visible=true");	
		// 이 방법으로 설정 바꾸는건 함수 하나만 있음 됨, 
		// 그러나 오타 이런거 조심해야됨
		else			
			TwDefine("TweakBar visible=false");
	}
	void ChangeDarw() { SetDraw(!isDraw); }
	TwBar* GetBar() { return bar; }
};

#define TWEAKBAR TweakBar::GetSingleton()

