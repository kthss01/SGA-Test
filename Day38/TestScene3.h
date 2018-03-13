#pragma once

#include "GameNode.h"

// 씬 간의 데이터 이동

class TestScene3 : public GameNode
{
private:
	int data = 100;
public:
	TestScene3();
	~TestScene3();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	int GetData() { return data; }
};

