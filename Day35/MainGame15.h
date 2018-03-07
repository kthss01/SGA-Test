#pragma once

#include "GameNode.h"

class MainGame15 : public GameNode
{
private:
	Image * _ball; // 충돌 시킬 녀석
	Image * _bg; // 충돌 계산을 할 이미지
public:
	MainGame15();
	~MainGame15();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

