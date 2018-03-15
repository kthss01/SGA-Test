#pragma once

#include "GameNode.h"

class MainGame21 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame21();
	~MainGame21();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

