#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

MainGame::MainGame()
{
	// 이거 때문에 한동안 MainGame의 Render가 안된거 같음
	//SUBWIN->Init();
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	SOUND->Init();
	SUBWIN->Init();

	isDebug = false;

	SUBWIN->SetMainGame(this);

	TestScene * test = new TestScene;
	SCENE->AddScene("Test", test);

	SOUND->AddSound("Test", "sounds/영전3.wav", true, true);

	SUBWIN->SetScene(test);

	SCENE->ChangeScene("Test");

	IMAGE->AddImage("tileMap", "images/tilemap.bmp", 0, 0,
			256, 640, 8, 20, false, RGB(0, 0, 0));

	imageFrame = { 7, 2 };

	MapToolSetup();

	_currentCTRL = CTRL_TERRAINDRAW;

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
	// 마우스 움직이는 윈도우 위치에 따라 active 값 바꾸게했음
	if (SUBWIN->GetIsActive() == false) {
		if (INPUT->GetKey(VK_LBUTTON)) {
			SetMap();
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
		//SCENE->Render();
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
	for (int i = 0; i < TILEX*TILEY; i++) {
		sprintf_s(str, "tile %d", i);
		INIDATA->AddData(str, "obj", to_string(_tiles[i].obj).c_str());
		INIDATA->AddData(str, "objFrameX", to_string(_tiles[i].objFrameX).c_str());
		INIDATA->AddData(str, "objFrameY", to_string(_tiles[i].objFrameY).c_str());
		INIDATA->AddData(str, "terrain", to_string(_tiles[i].terrain).c_str());
		INIDATA->AddData(str, "terrainFrameX", to_string(_tiles[i].terrainFrameX).c_str());
		INIDATA->AddData(str, "terrainFrameY", to_string(_tiles[i].terrainFrameY).c_str());
	}
	INIDATA->SaveData("TilesInfo");
}

void MainGame::Load()
{
	for (int i = 0; i < TILEX*TILEY; i++) {
		sprintf_s(str, "tile %d", i);
		_tiles[i].obj = (OBJECT)INIDATA->LoadDataInteger("TilesInfo", str, "obj");
		_tiles[i].objFrameX = INIDATA->LoadDataInteger("TilesInfo", str, "objFrameX");
		_tiles[i].objFrameY = INIDATA->LoadDataInteger("TilesInfo", str, "objFrameY");
		_tiles[i].terrain = (TERRAIN)INIDATA->LoadDataInteger("TilesInfo", str, "terrain");
		_tiles[i].terrainFrameX = INIDATA->LoadDataInteger("TilesInfo", str, "terrainFrameX");
		_tiles[i].terrainFrameY = INIDATA->LoadDataInteger("TilesInfo", str, "terrainFrameY");
	}
}
