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
	SOUND->AddSound("Test", "sounds/영전3.wav", true, true);

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

	// 주소 지정 /이것도 하지만 \\ 이거 쓰기도함

	if (INPUT->GetKey(VK_LCONTROL)) {
		if(INPUT->GetKeyDown('S')) {
			ZeroMemory(&OFN, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = g_hWnd;
			// 파일 열었을 때 확장 선택하는걸 필터
			OFN.lpstrFilter =
				// Every File이 필터의 이름 \0\0이 실제 파일확장명
				// \0으로 구분하는거
				"Every file(*.*)\0*.*\0Text File(*.txt)\0*.txt\0PNG file(*.png)\0*.png\0";
			// 파일 열면 그 파일에 대한 주소값이 들어가는 거
			OFN.lpstrFile = filePath;
			// 이렇게해도 된다고 함 아래로 하면 크기 때문에
			//OFN.lpstrFile = (char*)"";
			// 내가 담을 수 있는 최대 경로 사이즈
			OFN.nMaxFile = MAX_PATH;
			// 파일 열 때 어디서부터 열지 시작 지점 정해주는거
			char str[128];
			GetCurrentDirectory(128, str);
			OFN.lpstrInitialDir = str;
			if (GetOpenFileName(&OFN) != 0) {
				strcpy_s(filePath, OFN.lpstrFile);
				
				// 이 창이 켜졌을때 프레임 멈춤
				MessageBox(g_hWnd, filePath, "성공", MB_OK);
				
				bg->Init(filePath, WINSIZEX, WINSIZEY);
			}

			// 저장은 OpenFileName의 옵션 중에 하나 잇다고 함
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
