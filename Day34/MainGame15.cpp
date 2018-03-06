#include "stdafx.h"
#include "MainGame15.h"


MainGame15::MainGame15()
{
}


MainGame15::~MainGame15()
{
}

HRESULT MainGame15::Init()
{
	GameNode::Init();

	return S_OK;
}

void MainGame15::Release()
{
	GameNode::Release();
}

void MainGame15::Update()
{
	GameNode::Update();
}

void MainGame15::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
