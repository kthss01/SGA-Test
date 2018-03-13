#pragma once

#include "GameNode.h"

// �� ���� ������ �̵�

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

