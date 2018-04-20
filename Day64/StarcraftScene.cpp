#include "stdafx.h"
#include "StarcraftScene.h"

// ¾È½áµµ µÊ
//#include "Ship.h"
#include "Battle.h"

StarcraftScene::StarcraftScene()
{
}


StarcraftScene::~StarcraftScene()
{
}

HRESULT StarcraftScene::Init()
{
	_battle = new Battle;
	_battle->Init("Battle", WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}

void StarcraftScene::Release()
{
	SAFE_DELETE(_battle);
}

void StarcraftScene::Update()
{
	_battle->Update();
}

void StarcraftScene::Render()
{
	_battle->Render();
}
