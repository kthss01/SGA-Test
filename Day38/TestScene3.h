#pragma once

#include "GameNode.h"

class TestScene3 : public GameNode
{
public:
	TestScene3();
	~TestScene3();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

