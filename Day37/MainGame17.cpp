#include "stdafx.h"
#include "MainGame17.h"

#include "TestScene1.h"
#include "TestScene2.h"

MainGame17::MainGame17()
{
}


MainGame17::~MainGame17()
{
}

HRESULT MainGame17::Init()
{
	GameNode::Init();
	isDebug = false;

	SCENE->AddScene("Test1", new TestScene1);
	SCENE->AddScene("Test2", new TestScene2);

	SCENE->ChangeScene("Test1");

	return S_OK;
}

void MainGame17::Release()
{
	GameNode::Release();
	SCENE->Release();
}

void MainGame17::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame17::Render()
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
