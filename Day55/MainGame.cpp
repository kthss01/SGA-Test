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
	SOUND->AddSound("Test", "sounds/����3.wav", true, true);

	SCENE->ChangeScene("Test");

	vector<string> str;

	str.push_back("������ ������ : ");
	str.push_back("SAVE ");
	str.push_back("LOAD ");
	str.push_back("�ϲ���..." );
	str.push_back("� �༮�� ");
	str.push_back("���̺� ");
	str.push_back("�ε� �ұ�???");
	str.push_back("Add Test");

	// ������ ��������� ����
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
	
		// ���� ����
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
