#include "stdafx.h"
#include "MainGame12.h"


MainGame12::MainGame12()
{
}


MainGame12::~MainGame12()
{
}

HRESULT MainGame12::Init()
{
	GameNode::Init();

	return S_OK;
}

void MainGame12::Release()
{
	GameNode::Release();
}

void MainGame12::Update()
{
	GameNode::Update();
}

void MainGame12::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}
