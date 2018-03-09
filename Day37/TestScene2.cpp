#include "stdafx.h"
#include "TestScene2.h"


TestScene2::TestScene2()
{
}


TestScene2::~TestScene2()
{
}

HRESULT TestScene2::Init()
{
	bg = new Image();
	bg->Init("images/메가맨배경.bmp", WINSIZEX, WINSIZEY, true);
	return S_OK;
}

void TestScene2::Release()
{
	SAFE_DELETE(bg);
}

void TestScene2::Update()
{
	if (INPUT->GetKeyDown(VK_RETURN)) {
		SCENE->ChangeScene("Test1");
	}
}

void TestScene2::Render()
{
	bg->Render(GetMemDC());
}
