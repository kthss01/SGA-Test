#pragma once

#include "GameNode.h"

class MainGame16 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame16();
	~MainGame16();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

