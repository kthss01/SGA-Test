#include "stdafx.h"
#include "MainGame17.h"


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

	return S_OK;
}

void MainGame17::Release()
{
	GameNode::Release();
}

void MainGame17::Update()
{
	GameNode::Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame17::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{

	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
