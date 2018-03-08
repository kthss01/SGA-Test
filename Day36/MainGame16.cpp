#include "stdafx.h"
#include "MainGame16.h"


MainGame16::MainGame16()
{
}


MainGame16::~MainGame16()
{
}

HRESULT MainGame16::Init()
{
	GameNode::Init();

	return S_OK;
}

void MainGame16::Release()
{
	GameNode::Release();
}

void MainGame16::Update()
{
	GameNode::Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame16::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	//=================================================

	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
