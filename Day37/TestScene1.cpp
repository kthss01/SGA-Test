#include "stdafx.h"
#include "TestScene1.h"


TestScene1::TestScene1()
{
}


TestScene1::~TestScene1()
{
}

HRESULT TestScene1::Init()
{
	bg = new Image();
	bg->Init("images/mountain.bmp", WINSIZEX, WINSIZEY, true);
	return S_OK;
}

void TestScene1::Release()
{
	SAFE_DELETE(bg);
}

void TestScene1::Update()
{
	if (INPUT->GetKeyDown(VK_RETURN)) {
		SCENE->ChangeScene("Test2");
	}
}

void TestScene1::Render()
{
	bg->Render(GetMemDC());
}
