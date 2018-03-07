#pragma once

#include "GameNode.h"

class MainGame15 : public GameNode
{
private:
	Image * _ball; // �浹 ��ų �༮
	Image * _bg; // �浹 ����� �� �̹���
public:
	MainGame15();
	~MainGame15();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

