#pragma once

#include "GameNode.h"

class MainGame14 : public GameNode
{
private:

public:
	MainGame14();
	~MainGame14();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

