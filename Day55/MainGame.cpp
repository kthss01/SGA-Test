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
	//TXTDATA->TxTSave((char*)"texts/TxTSave.txt", str);

	TXTDATA->CreateWriteTextDataHandle((char*)"texts/TxTSave2.txt");

	for (int i = 0; i < 3; i++) {
		TXTDATA->TextWrite(str);
	}

	TXTDATA->CloseTextDataHandle();

	INIDATA->AddData("Test", "KeyTest", "1000");
	INIDATA->AddData("Test", "KeyTest2", "3.141592f");
	INIDATA->AddData("Test2", "KeyTest3", "1234");
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
	
		//// ���� ���� -> �ذ�
		//vector<string> str = TXTDATA->TxTLoad((char*)"texts/TxTSave.txt");
		//for (int i = 0; i < str.size(); i++) {
		//	TextOut(GetMemDC(), WINSIZEX / 2, i * 20, 
		//		str[i].c_str(), strlen(str[i].c_str()));
		//}
		
		TXTDATA->CreateReadTextDataHandle((char*)"texts/TxTSave2.txt");
		vector< vector<string> > sstr = TXTDATA->TextRead();
		for (int i = 0; i < sstr.size(); i++) {
			for (int j = 0; j < sstr[i].size(); j++) {
				TextOut(GetMemDC(), 200 + i * 150, j * 20,
					sstr[i][j].c_str(), strlen(sstr[i][j].c_str()));
			}
		}
		TXTDATA->CloseTextDataHandle();

		//char str[128];
		//// ������ �������� �ʰų� �߸��� ���� ��� 0�� ����
		//sprintf_s(str, "%d", 
		//	INIDATA->LoadDataInteger("IniSave", "Test3", "KeyTest4"));
		//TextOut(GetMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));

		//float data = atof(INIDATA->LoadDataString("IniSave", "Test", "KeyTest2"));
		//sprintf_s(str, "%f", data);
		//TextOut(GetMemDC(), WINSIZEX / 2, WINSIZEY / 2 + 50, str, strlen(str));
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	FRAME->Render(GetMemDC());
	this->SetBackBuffer()->Render(GetHDC());
}
