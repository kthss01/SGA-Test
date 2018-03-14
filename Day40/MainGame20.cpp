#include "stdafx.h"
#include "MainGame20.h"

#include "TestScene6.h"

MainGame20::MainGame20()
{
}


MainGame20::~MainGame20()
{
}

HRESULT MainGame20::Init()
{
	GameNode::Init();
	isDebug = false;

	SCENE->AddScene("Test1", new TestScene6);
	SCENE->ChangeScene("Test1");

	return S_OK;
}

void MainGame20::Release()
{
	GameNode::Release();
}

void MainGame20::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame20::Render()
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
