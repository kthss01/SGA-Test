#include "stdafx.h"
#include "TestScene4.h"
#include "TestScene3.h"

TestScene4::TestScene4()
{
}


TestScene4::~TestScene4()
{
}

HRESULT TestScene4::Init()
{
	data = test->GetData();

	return S_OK;
}

void TestScene4::Release()
{
}

void TestScene4::Update()
{
}

void TestScene4::Render()
{
	char str[128];
	sprintf_s(str, "%d", data);
	TextOut(GetMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
}
