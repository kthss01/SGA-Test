#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

#include "IsoTest.h"
#include "StarcraftScene.h"

MainGame::MainGame()
{
#ifdef SUBWINOPEN
	SUBWIN->Init();
#endif // SUBWINDOW �ʿ�� MainGame.h �ּ� ����
}

MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	isDebug = false;

	IMAGE->AddImage("Battle", "images/battle.bmp", 0, 0, 1536, 79,
		16, 1, true, RGB(255, 0, 255));

	TestScene * test = new TestScene;
	SCENE->AddScene("Test", test);
	SCENE->AddScene("IsoTest", new IsoTest);

	SOUND->Init();
	SOUND->AddSound("Test", "sounds/����3.wav", true, true);

	SCENE->AddScene("Startcraft", new StarcraftScene);

#ifdef SUBWINOPEN
	SUBWIN->SetScene(test);
#endif // SUBWINDOW �ʿ�� MainGame.h �ּ� ����

	//SCENE->ChangeScene("IsoTest");
	SCENE->ChangeScene("Startcraft");

	ShowCursor(false);

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
}

void MainGame::Update()
{
	GameNode::Update();
	SCENE->Update();

#ifdef SUBWINOPEN
	SUBWIN->Update();
#endif // SUBWINDOW �ʿ�� MainGame.h �ּ� ����

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

#ifdef SUBWINOPEN
		SUBWIN->Render();
#endif // SUBWINDOW �ʿ�� MainGame.h �ּ� ����
		
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	FRAME->Render(GetMemDC());
	this->SetBackBuffer()->Render(GetHDC());
}
