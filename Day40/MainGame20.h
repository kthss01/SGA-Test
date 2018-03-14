#pragma once

#include "GameNode.h"

class MainGame20 : public GameNode
{
private:
	bool isDebug;
public:
	MainGame20();
	~MainGame20();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

/*
	2D 이미지는 타일로 다 짤려있음
*/

