#pragma once

#include "GameNode.h"

class MainGame18 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame18();
	~MainGame18();


	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

