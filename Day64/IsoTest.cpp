#include "stdafx.h"
#include "IsoTest.h"


IsoTest::IsoTest()
{
}


IsoTest::~IsoTest()
{
}

HRESULT IsoTest::Init()
{
	_isoX = 0;
	_isoY = 0;
	_center = 0;
	memset(_tileMap, 0, sizeof(_tileMap));

	_startX = INIT_X;
	_startY = INIT_Y;

	IMAGE->AddImage("IsoTile", "images/tile_grass.bmp", 0, 0,
		CELL_WIDTH, CELL_HEIGHT + 15, true, RGB(255, 0, 255));

	ZeroMemory(_tiles, sizeof(IsoTile) * TILE_COUNT_X * TILE_COUNT_Y);
	for (int i = 0; i < TILE_COUNT_X; i++) {
		for (int j = 0; j < TILE_COUNT_Y; j++) {
			// frameRender �Ҷ� ���°�
			_tiles[i][j].frameIndex.push_back(PointMake(3,0));
			_tiles[i][j].height = 15;
		}
	}

	for (int i = 0; i < 3; i++) {
		_tiles[0][0].frameIndex.push_back(PointMake(3, 0));
	}

	return S_OK;
}

void IsoTest::Release()
{
}

void IsoTest::Update()
{
	if (INPUT->GetKey('W')) { _startY += 5; }
	if (INPUT->GetKey('S')) { _startY -= 5; }
	if (INPUT->GetKey('A')) { _startX += 5; }
	if (INPUT->GetKey('D')) { _startX -= 5; }

	if (INPUT->GetKey(VK_LBUTTON)) {
		// �ε��� ��ȣ ����� ��
		float cellX = (float)(g_ptMouse.x - _startX);

		// iso Ÿ���� ���������� -,+�� �ΰ��� �����Ǽ� �̷��� ó���Ѱ�
		// - +�� �ٲ㼭 �ε��� ���
		if (cellX < 0) {
			cellX = (cellX - CELL_WIDTH) / (float)CELL_WIDTH;
		}
		else {
			cellX = cellX / (float)CELL_WIDTH;
		}

		// y�� ����̱⸸ �ؼ� �̷��� �Ѱ�
		int cellY = abs(g_ptMouse.y - _startY) / CELL_HEIGHT;

		// ���������� ���� �϶�
		cellY = (g_ptMouse.y < _startY) ? cellY * -1 : cellY;

		int isoX = (int)cellX + (int)cellY;
		int isoY = (int)cellY - (int)cellX;

		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y) {
			// 1�и��̸� [x-1][y] left top
			// 2�и��̸� [x][y-1] right top
			// 3�и��̸� [x][y+1] left bottom
			// 4�и��̸� [x+1][y] right bottom

			int corner = GetCornerIndex(isoX, isoY);

			// ������ �ȿ� ������
			if (IsInRhombus(corner, isoX, isoY)) {
				corner = 0;
			}

			switch (corner)
			{
			case 1:
				isoX = isoX - 1;
				break;
			case 2:
				isoY = isoY - 1;
				break;
			case 3:
				isoY = isoY + 1;
				break;
			case 4:
				isoX = isoX + 1;
				break;
			}
			_tileMap[isoX][isoY] = 1;

			_center = corner;
			_isoX = isoX;
			_isoY = isoY;
		}
	}
}

void IsoTest::Render()
{
	sprintf_s(str, "isoX : %d, isoY : %d, corner : %d",
		_isoX, _isoY, _center);
	TextOut(GetMemDC(), 700, 20, str, strlen(str));

	DrawTileMap();
}

void IsoTest::DrawTileMap()
{
	for (int i = 0; i < TILE_COUNT_X; i++) {
		for (int j = 0; j < TILE_COUNT_Y; j++) {
			int left = _startX + (i * RADIUS_WIDTH) - (j * RADIUS_WIDTH);
			int top = _startY + (i * RADIUS_HEIGHT) + (j * RADIUS_HEIGHT);

			_tiles[i][j].left = left;
			_tiles[i][j].top = top;

			if (left + CELL_WIDTH < 0 || left > WINSIZEX
				|| top + CELL_HEIGHT < 0 || top > WINSIZEY) 
				continue;

			// Ŭ���ϸ� �� ����
			if (_tileMap[i][j] == 1) {
				// �⺻ �β��� 1
				// PS_SOLID ���ǹ� ������ �� ��� ���� �� �� ����
				HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
				HPEN oldPen = (HPEN)SelectObject(GetMemDC(), myPen);
				DrawRhombus(left, top);
				DeleteObject(SelectObject(GetMemDC(), oldPen));
			}
			else {
				DrawRhombus(left, top);
			}

			//IMAGE->Render("IsoTile", GetMemDC(), 
			//	_tiles[i][j].left, 
			//	_tiles[i][j].top);
			//// frame render�� �ش� frameIndex[0].x y ��


			// z 1������ ������ ������ �̹��� ���� �ؾߵǼ�
			for (int z = 0; z < _tiles[i][j].frameIndex.size(); z++) {
				IMAGE->Render("IsoTile", GetMemDC(),
					_tiles[i][j].left,
					_tiles[i][j].top - _tiles[i][j].height * z);
				// frame Render�� �ش� frameIndex[z].x,y ��
			}

			SetTextColor(GetMemDC(), RGB(0, 0, 0));
			sprintf_s(str, "(%d,%d)", i, j);
			TextOut(GetMemDC(), left + 30, top + 15, str, strlen(str));
		}
	}
}

void IsoTest::DrawRhombus(int left, int top)
{
	int centerX = left + RADIUS_WIDTH;
	int centerY = top + RADIUS_HEIGHT;

	// �簢�� ������ ���鶧 ���� 4������ 5���� ���� �׸��� ����
	// �ݺ�������
	// ������ �������� ������
	POINT p[5];
	p[0].x = centerX;
	p[0].y = centerY - RADIUS_HEIGHT;

	p[1].x = centerX + RADIUS_WIDTH;
	p[1].y = centerY;

	p[2].x = centerX;
	p[2].y = centerY + RADIUS_HEIGHT;

	p[3].x = centerX - RADIUS_WIDTH;
	p[3].y = centerY;

	p[4].x = centerX;
	p[4].y = centerY - RADIUS_HEIGHT;

	//IMAGE->Render("IsoTile", GetMemDC(), left, top);

	// 4���� ������ �� 0~3 ���� or 1~4 ����
	for (int i = 1; i < 5; i++) {
		LineMake(GetMemDC(), p[i - 1], p[i]);
	}
}

int IsoTest::GetCornerIndex(int isoX, int isoY)
{
	int left = _startX + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = _startY + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

	// ��ȯ�� ����
	// left top		1 
	// right top	2
	// left bottom	3
	// right bottom	4

	// ������
	float dx = (g_ptMouse.x - left) / (float)CELL_WIDTH;
	float dy = (g_ptMouse.y - top) / (float)CELL_HEIGHT;

	if (dx < 0.5f && dy < 0.5f) return 1;
	if (dx >= 0.5f && dy < 0.5f) return 2;
	if (dx < 0.5f && dy >= 0.5f) return 3;
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	// ������ ���� ������ ���� ��� �߸��Ѱ�
	return 0;
}

bool IsoTest::IsInRhombus(int corner, int isoX, int isoY)
{
	// ���� ������� ���������� ����
	// 1 ��и� lefttop
	if (corner == 1) {
		int left = _startX + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = _startY + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		// ������
		float dx = (float)(g_ptMouse.x - left) / RADIUS_WIDTH;
		float dy = (float)(g_ptMouse.y - top) / RADIUS_HEIGHT;

		if ((1.0f - dy) <= dx) return true;
		else return false;
	}
	// 2 ��и� righttop
	else if (corner == 2) {
		int left = _startX + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = _startY + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		left += RADIUS_WIDTH;

		// ������
		float dx = (float)(g_ptMouse.x - left) / RADIUS_WIDTH;
		float dy = (float)(g_ptMouse.y - top) / RADIUS_HEIGHT;

		if (dy >= dx) return true;
		else return false;
	}
	// 3 ��и� leftbottom
	else if (corner == 3) {
		int left = _startX + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = _startY + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		top += RADIUS_HEIGHT;

		// ������
		float dx = (float)(g_ptMouse.x - left) / RADIUS_WIDTH;
		float dy = (float)(g_ptMouse.y - top) / RADIUS_HEIGHT;

		if (dy <= dx) return true;
		else return false;
	}
	// 4 ��и� rightbottom
	else if (corner == 4) {
		int left = _startX + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = _startY + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		left += RADIUS_WIDTH;
		top += RADIUS_HEIGHT;

		// ������
		float dx = (float)(g_ptMouse.x - left) / RADIUS_WIDTH;
		float dy = (float)(g_ptMouse.y - top) / RADIUS_HEIGHT;

		if ((1.0f - dy) >= dx) return true;
		else return false;
	}
	return false;
}
