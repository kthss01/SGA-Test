#pragma once

#include "GameNode.h"

class MainGame15 : public GameNode
{
private:

public:
	MainGame15();
	~MainGame15();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

