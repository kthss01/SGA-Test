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
			// ���ڿ� �񱳷� �ϴ°Ŵ� �� �����Ű�� ��Ÿ ���� �ȵ�
			TwDefine("TweakBar visible=true");	
		// �� ������� ���� �ٲٴ°� �Լ� �ϳ��� ���� ��, 
		// �׷��� ��Ÿ �̷��� �����ؾߵ�
		else			
			TwDefine("TweakBar visible=false");
	}
	void ChangeDarw() { SetDraw(!isDraw); }
	TwBar* GetBar() { return bar; }
};

#define TWEAKBAR TweakBar::GetSingleton()

