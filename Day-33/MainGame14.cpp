#include "stdafx.h"
#include "MainGame14.h"


MainGame14::MainGame14()
{
}


MainGame14::~MainGame14()
{
}

HRESULT MainGame14::Init()
{
	GameNode::Init();

	return S_OK;
}

void MainGame14::Release()
{
	GameNode::Release();
}

void MainGame14::Update()
{
	GameNode::Update();
}

void MainGame14::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
