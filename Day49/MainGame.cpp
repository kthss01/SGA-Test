#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"
#include "Rocket.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	isDebug = false;

	IMAGE->AddImage("bg", "images/background.bmp", 0, -WINSIZEY,
		WINSIZEX, WINSIZEY * 2, false, RGB(255, 0, 255));
	IMAGE->AddImage(
		"bullet", "images/bullet.bmp", 0, 0, 21, 21, true, 
		RGB(255, 0, 255));
	IMAGE->AddImage(
		"ufo", "images/ufo.bmp", 0, 0, 530, 32, 10, 1, true,
		RGB(255, 0, 255));

	_em = new EnemyManager;
	_em->Init();

	SCENE->AddScene("Test", new TestScene);
	_em->SetRocket((Rocket*)SCENE->AddScene("Rocket", new Rocket));

	//SCENE->ChangeScene("Test");
	SCENE->ChangeScene("Rocket");


	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
	_em->Release();
	SAFE_DELETE(_em);
}

void MainGame::Update()
{
	GameNode::Update();

	SCENE->Update();

	_em->Update();

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
		IMAGE->FindImage("bg")->Render(GetMemDC(), 0, -WINSIZEY);

		SCENE->Render();

		_em->Render();
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
