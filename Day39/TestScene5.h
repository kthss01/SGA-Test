#pragma once

#include "GameNode.h"

class TestScene5 : public GameNode
{
private:
	Image * charactor;
public:
	TestScene5();
	~TestScene5();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

