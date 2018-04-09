#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

MainGame::MainGame()
{
	SUBWIN->Init();
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	isDebug = false;

	TestScene * test = new TestScene;
	SCENE->AddScene("Test", test);

	SOUND->Init();
	SOUND->AddSound("Test", "sounds/����3.wav", true, true);

	SUBWIN->SetScene(test);

	SCENE->ChangeScene("Test");

	bg = IMAGE->AddImage("tileMap", "images/tilemap.bmp", 0, 0,
		256, 640, 8, 20, false, RGB(0, 0, 0));

	ZeroMemory(&OFN, sizeof(OPENFILENAME));

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
}

void MainGame::Update()
{
	GameNode::Update();
	SUBWIN->Update();
	SCENE->Update();

	if (g_ptMouse.x > 0 && g_ptMouse.x < WINSIZEX) {
		if (g_ptMouse.y > 0 && g_ptMouse.y < WINSIZEY) {
			if (INPUT->GetKeyDown(VK_LBUTTON)) {
				RenderImage temp;
				temp.position = g_ptMouse;
				temp.frame = SUBWIN->GetFramePoint();

				images.push_back(temp);
			}
		}
	}

	// �ּ� ���� /�̰͵� ������ \\ �̰� ���⵵��

	if (INPUT->GetKey(VK_LCONTROL)) {
		if(INPUT->GetKeyDown('S')) {
			ZeroMemory(&OFN, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = g_hWnd;
			// ���� ������ �� Ȯ�� �����ϴ°� ����
			OFN.lpstrFilter =
				// Every File�� ������ �̸� \0\0�� ���� ����Ȯ���
				// \0���� �����ϴ°�
				"Every file(*.*)\0*.*\0Text File(*.txt)\0*.txt\0PNG file(*.png)\0*.png\0";
			// ���� ���� �� ���Ͽ� ���� �ּҰ��� ���� ��
			OFN.lpstrFile = filePath;
			// �̷����ص� �ȴٰ� �� �Ʒ��� �ϸ� ũ�� ������
			//OFN.lpstrFile = (char*)"";
			// ���� ���� �� �ִ� �ִ� ��� ������
			OFN.nMaxFile = MAX_PATH;
			// ���� �� �� ��𼭺��� ���� ���� ���� �����ִ°�
			char str[128];
			GetCurrentDirectory(128, str);
			OFN.lpstrInitialDir = str;
			if (GetOpenFileName(&OFN) != 0) {
				strcpy_s(filePath, OFN.lpstrFile);
				
				// �� â�� �������� ������ ����
				MessageBox(g_hWnd, filePath, "����", MB_OK);
				
				bg->Init(filePath, WINSIZEX, WINSIZEY);
			}

			// ������ OpenFileName�� �ɼ� �߿� �ϳ� �մٰ� ��
		}
	}

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
		SUBWIN->Render();

		bg->Render(GetMemDC());

		for (int i = 0; i < images.size(); i++) {
			IMAGE->FrameRender("tileMap", GetMemDC(),
				images[i].position.x,
				images[i].position.y,
				images[i].frame.x, images[i].frame.y);
		}

		IMAGE->FrameRender("tileMap", GetMemDC(),
			g_ptMouse.x, g_ptMouse.y,
			SUBWIN->GetFramePoint().x, SUBWIN->GetFramePoint().y, 128);
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		char str[128];
		sprintf_s(str, "%d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 0, 80, str, strlen(str));

		sprintf_s(str, "%d %d", SUBWIN->GetMousePos().x, SUBWIN->GetMousePos().y);
		TextOut(GetMemDC(), 0, 100, str, strlen(str));
	}
	//=================================================
	FRAME->Render(GetMemDC());
	this->SetBackBuffer()->Render(GetHDC());
}
