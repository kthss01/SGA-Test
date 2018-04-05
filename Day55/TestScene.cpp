#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
{
	isDebug = false;

	SOUND->Play("Test", 0.5f);

	return S_OK;
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	SOUND->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void TestScene::Render()
{
	//=================================================
	{

	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
}
