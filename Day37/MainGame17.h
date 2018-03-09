#pragma once

#include "GameNode.h"

class MainGame17 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame17();
	~MainGame17();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

