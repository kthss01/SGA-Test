#pragma once

#include "GameNode.h"

class MainGame13 : public GameNode
{
public:
	MainGame13();
	~MainGame13();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

