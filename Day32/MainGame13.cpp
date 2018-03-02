#include "stdafx.h"
#include "MainGame13.h"


MainGame13::MainGame13()
{
}


MainGame13::~MainGame13()
{
}

HRESULT MainGame13::Init()
{
	GameNode::Init();

	return S_OK;
}

void MainGame13::Release()
{
	GameNode::Release();
}

void MainGame13::Update()
{
	GameNode::Update();
}

void MainGame13::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===============================================
	
	//===============================================
	this->GetBackBuffer()->Render(hdc);
}
