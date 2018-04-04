#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

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

	IMAGE->AddImage(
		"ufo", "images/ufo.bmp", 0, 0, 530, 32, 10, 1, true,
		RGB(255, 0, 255));

	for (int i = 0; i < 10; i++) {
		object[i] = new Object;
		object[i]->SetImage(IMAGE->FindImage("ufo"));
		object[i]->SetID(i);
		object[i]->SetActive(true);
	}

	SCENE->AddScene("Test", new TestScene);

	//SCENE->ChangeScene("Test");

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
	for (int i = 0; i < 10; i++)
		SAFE_DELETE(object[i]);
}

void MainGame::Update()
{
	GameNode::Update();

	//SCENE->Update();

	for (int i = 0; i < 10; i++) {
		object[i]->Update();
	}

	if (INPUT->GetKeyDown(VK_SPACE))
	{
		
		removeObject = RND->GetInt(10);
		// 이렇게 안해도 SetActive()에서 처리함
		// 스페이스 씹히는건 반복문으로 처리
		if(object[removeObject]->GetActive())
			object[removeObject]->SetActive(false);
	}

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
		//SCENE->Render();
		for (int i = 0; i < 10; i++) {
			object[i]->Render();
		}
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	FRAME->Render(GetMemDC());
	this->SetBackBuffer()->Render(GetHDC());
}
