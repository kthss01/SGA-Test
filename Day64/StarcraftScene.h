#pragma once

#include "GameNode.h"

class StarcraftScene : public GameNode
{
private:
	class Ship * _battle;	// ���漱��� ���ÿ� ������ ���� �� ����
public:
	StarcraftScene();
	~StarcraftScene();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

