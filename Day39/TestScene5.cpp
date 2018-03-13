#include "stdafx.h"
#include "TestScene5.h"


TestScene5::TestScene5()
{
}


TestScene5::~TestScene5()
{
}

HRESULT TestScene5::Init()
{
	charactor = IMAGE->AddImage("Test", "images/·Ï¸Ç.bmp", WINSIZEX / 2, WINSIZEY / 2,
		480, 100, 10, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void TestScene5::Release()
{
}

void TestScene5::Update()
{
}

void TestScene5::Render()
{
	IMAGE->FrameRender("Test", GetMemDC(),
		IMAGE->FindImage("Test")->GetX(),
		IMAGE->FindImage("Test")->GetY(),
		2, 0);

	charactor->FrameRender(GetMemDC(),
		charactor->GetX(),
		charactor->GetY(),
		2, 0);

}
