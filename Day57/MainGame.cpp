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
	
	// Day58 중복
	IMAGE->AddImage("tileMap", "images/tilemap.bmp", 0, 0,
			256, 640, 8, 20, false, RGB(0, 0, 0));

	imageFrame = { 7, 2 };

	MapToolSetup();

	_currentCTRL = CTRL_TERRAINDRAW;

	////////////////////////////////////////////
	// Day57
	//bg = IMAGE->AddImage("tileMap", "images/tilemap.bmp", 0, 0,
	//	256, 640, 8, 20, false, RGB(0, 0, 0));
	//
	//ZeroMemory(&OFN, sizeof(OPENFILENAME));

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

	// 이거 문제 있음 해결방안 찾아보자
	if (g_ptMouse.x > 0 && g_ptMouse.x < WINSIZEX) {
		if (g_ptMouse.y > 0 && g_ptMouse.y < WINSIZEY) {
			if (INPUT->GetKey(VK_LBUTTON)) {
				SetMap();
			}
		}
	}

	///////////////////////////////////////////////////
	// Day57
	//if (g_ptMouse.x > 0 && g_ptMouse.x < WINSIZEX) {
	//	if (g_ptMouse.y > 0 && g_ptMouse.y < WINSIZEY) {
	//		if (INPUT->GetKeyDown(VK_LBUTTON)) {
	//			RenderImage temp;
	//			temp.position = g_ptMouse;
	//			temp.frame = SUBWIN->GetFramePoint();
	//
	//			images.push_back(temp);
	//		}
	//	}
	//}
	//
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
			//OFN.Flags = OFN_NOCHANGEDIR;
			if (GetOpenFileName(&OFN) != 0) {
				strcpy_s(filePath, OFN.lpstrFile);
				
				// 이 창이 켜졌을때 프레임 멈춤
				MessageBox(g_hWnd, filePath, "성공", MB_OK);
				
				//bg->Init(filePath, WINSIZEX, WINSIZEY);
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

		for (int i = 0; i < TILEX * TILEY; i++) {
			// 지형
			IMAGE->FrameRender("tileMap", GetMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			// 오브젝트
			if (_tiles[i].obj == OBJ_NONE) continue;
			IMAGE->FrameRender("tileMap", GetMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].objFrameX, _tiles[i].objFrameY);
		}

		//bg->Render(GetMemDC());
		//
		//for (int i = 0; i < images.size(); i++) {
		//	IMAGE->FrameRender("tileMap", GetMemDC(),
		//		images[i].position.x,
		//		images[i].position.y,
		//		images[i].frame.x, images[i].frame.y);
		//}
		//
		//IMAGE->FrameRender("tileMap", GetMemDC(),
		//	g_ptMouse.x, g_ptMouse.y,
		//	SUBWIN->GetFramePoint().x, SUBWIN->GetFramePoint().y, 128);
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

void MainGame::MapToolSetup()
{
	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,				// left
				i * TILESIZE,				// top
				j * TILESIZE + TILESIZE,	// right
				i * TILESIZE + TILESIZE);	// bottom
				
		}
	}

	// 처음 깔려 있는 타일
	for (int i = 0; i < TILEX * TILEY; i++) {
		_tiles[i].terrainFrameX = 7;
		_tiles[i].terrainFrameY = 2;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

		_tiles[i].terrain = 
			TerrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		_tiles[i].obj = OBJ_NONE;
	}
}

void MainGame::SetMap()
{
	imageFrame = SUBWIN->GetFramePoint();
	
	// static이라 하나만 있어서 클래스로 가져 올 수 있음
	// 싱글턴 안쓰고도
	_currentCTRL = Window::GetCTRL();

	for (int i = 0; i < TILEX*TILEY; i++) {
		if (PtInRect(&_tiles[i].rc, g_ptMouse)) {
			if (_currentCTRL == CTRL_TERRAINDRAW) {
				_tiles[i].terrainFrameX = imageFrame.x;
				_tiles[i].terrainFrameY = imageFrame.y;

				_tiles[i].terrain = TerrainSelect(imageFrame.x, imageFrame.y);
				break;
			}
			if (_currentCTRL == CTRL_OBJECTDRAW) {
				_tiles[i].objFrameX = imageFrame.x;
				_tiles[i].objFrameY = imageFrame.y;

				_tiles[i].obj = ObjSelect(imageFrame.x, imageFrame.y);

				// test
				_tiles[i].objFrameX = imageFrame.y;
				_tiles[i].objFrameY = imageFrame.x;

				_tiles[i].obj = ObjSelect(imageFrame.y, imageFrame.x);
				break;
			}

			if (_currentCTRL == CTRL_ERASER) {
				_tiles[i].terrainFrameX = 7;
				_tiles[i].terrainFrameY = 2;

				_tiles[i].terrain = TerrainSelect(7, 2);

				// object도 지워야한다면 같이 지워주면 됨 자유롭게하기
				break;
			}
		}
	}
}

TERRAIN MainGame::TerrainSelect(int frameX, int frameY)
{
	// 시멘트 타일
	if (frameX == 7 && frameY == 1) return TR_CEMENT;
	// 흙 타일
	if (frameX == 7 && frameY == 2) return TR_GROUND;
	// 풀 타일
	if (frameX == 7 && frameY == 3) return TR_GRASS;
	// 물 타일
	if (frameX == 7 && frameY == 4) return TR_WATER;
}

OBJECT MainGame::ObjSelect(int frameX, int frameY)
{
	return OBJECT();
}

void MainGame::Save()
{
}

void MainGame::Load()
{
}
