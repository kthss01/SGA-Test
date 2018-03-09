#pragma once

#include "GameNode.h"

class TestScene1 : public GameNode
{
private:
	Image * bg;
public:
	TestScene1();
	~TestScene1();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

