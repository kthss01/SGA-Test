#pragma once

#include "GameNode.h"

class MainGame12 : public GameNode
{
private:

public:
	MainGame12();
	~MainGame12();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

