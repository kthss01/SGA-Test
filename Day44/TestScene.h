#pragma once

#include "GameNode.h"

class TestScene : public GameNode
{
private:
	bool isDebug;

	float sour;

	Image* test;
public:
	TestScene();
	~TestScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

