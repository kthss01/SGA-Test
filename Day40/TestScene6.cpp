#include "stdafx.h"
#include "TestScene6.h"


TestScene6::TestScene6()
{
}


TestScene6::~TestScene6()
{
}

HRESULT TestScene6::Init()
{
	charactor = IMAGE->AddImage("Test", "images/·Ï¸Ç.bmp", WINSIZEX / 2, WINSIZEY / 2,
		480, 100, 10, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void TestScene6::Release()
{
}

void TestScene6::Update()
{
}

void TestScene6::Render()
{
	IMAGE->FrameRender("Test", GetMemDC(),
		IMAGE->FindImage("Test")->GetX(),
		IMAGE->FindImage("Test")->GetY(),
		2, 0);
}
