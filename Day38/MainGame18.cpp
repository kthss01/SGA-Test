#include "stdafx.h"
#include "MainGame18.h"

#include "TestScene3.h"
#include "TestScene4.h"
#include "MineGame.h"


MainGame18::MainGame18()
{
}


MainGame18::~MainGame18()
{
}

HRESULT MainGame18::Init()
{
	GameNode::Init();
	isDebug = false;

	//SCENE->AddScene("Test1", new TestScene3);
	//SCENE->AddScene("Test2", new TestScene4);
	SCENE->AddScene("MineGame", new MineGame);
	
	TestScene3* test1 = new TestScene3;
	TestScene4* test2 = new TestScene4;

	test1->Init();
	test2->SetSceneLink(test1);
	test2->Init();

	SCENE->AddScene("Test1", test1);
	SCENE->AddScene("Test2", test2);

	// reinterpret_cast<> 
	// 포인터로 되어잇는거 주소 연관이 없을 때 캐스팅 해주는거
	int* data;
	reinterpret_cast<char*>(data);
	// const_cast<> const로 묶음 바꿀 수 없는데 바꿀 수 있게 해주는거
	
	SCENE->ChangeScene("Test1");
	//SCENE->ChangeScene("MineGame");

	return S_OK;
}

void MainGame18::Release()
{
	GameNode::Release();
	SCENE->Release();
}

void MainGame18::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame18::Render()
{
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		SCENE->Render();
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
