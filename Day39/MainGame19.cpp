#include "stdafx.h"
#include "MainGame19.h"
#include "TestScene5.h"

MainGame19::MainGame19()
{
}


MainGame19::~MainGame19()
{
}

HRESULT MainGame19::Init()
{
	GameNode::Init();
	isDebug = false;

	SCENE->AddScene("Test1", new TestScene5);
	SCENE->ChangeScene("Test1");

	return S_OK;
}

void MainGame19::Release()
{
	GameNode::Release();
}

void MainGame19::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame19::Render()
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
