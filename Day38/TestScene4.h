#pragma once

#include "GameNode.h"

class TestScene4 : public GameNode
{
public:
	TestScene4();
	~TestScene4();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

