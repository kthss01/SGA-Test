#include "stdafx.h"
#include "TestScene3.h"


TestScene3::TestScene3()
{
}


TestScene3::~TestScene3()
{
}

HRESULT TestScene3::Init()
{
	return S_OK;
}

void TestScene3::Release()
{
}

void TestScene3::Update()
{
	if (INPUT->GetKeyDown(VK_SPACE)) {
		SCENE->ChangeScene("Test2");
	}
}

void TestScene3::Render()
{
}
