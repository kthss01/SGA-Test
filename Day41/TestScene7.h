#pragma once

#include "GameNode.h"

class TestScene7 : public GameNode
{
public:
	TestScene7();
	~TestScene7();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

