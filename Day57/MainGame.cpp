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
	
	// Day58 �ߺ�
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

	// �̰� ���� ���� �ذ��� ã�ƺ���
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
			//OFN.Flags = OFN_NOCHANGEDIR;
			if (GetOpenFileName(&OFN) != 0) {
				strcpy_s(filePath, OFN.lpstrFile);
				
				// �� â�� �������� ������ ����
				MessageBox(g_hWnd, filePath, "����", MB_OK);
				
				//bg->Init(filePath, WINSIZEX, WINSIZEY);
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

		for (int i = 0; i < TILEX * TILEY; i++) {
			// ����
			IMAGE->FrameRender("tileMap", GetMemDC(),
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

			// ������Ʈ
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

	// ó�� ��� �ִ� Ÿ��
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
	
	// static�̶� �ϳ��� �־ Ŭ������ ���� �� �� ����
	// �̱��� �Ⱦ���
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

				// object�� �������Ѵٸ� ���� �����ָ� �� �����Ӱ��ϱ�
				break;
			}
		}
	}
}

TERRAIN MainGame::TerrainSelect(int frameX, int frameY)
{
	// �ø�Ʈ Ÿ��
	if (frameX == 7 && frameY == 1) return TR_CEMENT;
	// �� Ÿ��
	if (frameX == 7 && frameY == 2) return TR_GROUND;
	// Ǯ Ÿ��
	if (frameX == 7 && frameY == 3) return TR_GRASS;
	// �� Ÿ��
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
