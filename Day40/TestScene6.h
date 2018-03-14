#pragma once

#include "GameNode.h"

class TestScene6 : public GameNode
{
private:
	Image * charactor;
public:
	TestScene6();
	~TestScene6();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

