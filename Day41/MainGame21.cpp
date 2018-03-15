#include "stdafx.h"
#include "MainGame21.h"

#include "TestScene7.h"

MainGame21::MainGame21()
{
}


MainGame21::~MainGame21()
{
}

HRESULT MainGame21::Init()
{
	GameNode::Init();
	isDebug = false;

	SCENE->AddScene("Test1", new TestScene7);

	SCENE->ChangeScene("Test1");

	return S_OK;
}

void MainGame21::Release()
{
	GameNode::Release();
}

void MainGame21::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame21::Render()
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
