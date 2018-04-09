#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

MainGame::MainGame()
{
	SUBWIN->Init();
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	isDebug = false;

	TestScene * test = new TestScene;
	SCENE->AddScene("Test", test);

	SOUND->Init();
	SOUND->AddSound("Test", "sounds/¿µÀü3.wav", true, true);

	SUBWIN->SetScene(test);

	SCENE->ChangeScene("Test");

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
}

void MainGame::Update()
{
	GameNode::Update();
	SUBWIN->Update();
	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame::Render()
{
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		SCENE->Render();
		SUBWIN->Render();
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	FRAME->Render(GetMemDC());
	this->SetBackBuffer()->Render(GetHDC());
}
