#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
{
	isDebug = false;

	test = new Image;
	test->Init("images/오른쪽걷기1.bmp", 100, 100, false,
		RGB(255,0,255));

	sour = 0;

	return S_OK;
}

void TestScene::Release()
{
	SAFE_DELETE(test);
}

void TestScene::Update()
{
	if (INPUT->GetKey('Q')) { sour += 1; }

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void TestScene::Render()
{
	//test->Render(GetMemDC());
	// 0.5 0.5 이미지의 정중앙으로 회전
	test->RotateRender(GetMemDC(), sour, 300, 200, 0.5, 0.5);

	//=================================================
	{

	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
}
