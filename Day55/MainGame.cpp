#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	isDebug = false;

	SCENE->AddScene("Test", new TestScene);

	SOUND->Init();
	SOUND->AddSound("Test", "sounds/영전3.wav", true, true);

	SCENE->ChangeScene("Test");

	vector<string> str;

	str.push_back("오늘의 숙제는 : ");
	str.push_back("SAVE ");
	str.push_back("LOAD ");
	str.push_back("일껀데..." );
	str.push_back("어떤 녀석을 ");
	str.push_back("세이브 ");
	str.push_back("로드 할까???");
	str.push_back("Add Test");

	// 폴더는 만들어지지 않음
	TXTDATA->TxTSave((char*)"texts/TxTSave.txt", str);

	INIDATA->AddData("Test", "KeyTest", "1000");
	INIDATA->AddData("Test", "KeyTest2", "1000");
	INIDATA->AddData("Test2", "KeyTest3", "1000");
	INIDATA->AddData("Test3", "KeyTest4", "1000");
	INIDATA->AddData("Test", "KeyTest5", "1000");
	INIDATA->SaveData("IniSave");

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
}

void MainGame::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame::Render()
{
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		SCENE->Render();
	
		// 문제 있음
		vector<string> str = TXTDATA->TxTLoad((char*)"texts/TxTSave.txt");
		for (int i = 0; i < str.size(); i++) {
			TextOut(GetMemDC(), WINSIZEX / 2, i * 20, 
				str[i].c_str(), strlen(str[i].c_str()));
		}

	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	FRAME->Render(GetMemDC());
	this->SetBackBuffer()->Render(GetHDC());
}
