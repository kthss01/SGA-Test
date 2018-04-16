#include "stdafx.h"
#include "AStar.h"


AStar::AStar()
{
}


AStar::~AStar()
{
}

HRESULT AStar::Init()
{
	_aStarState = ASTAR_STATE_END;

	_selectedType = TILE_TYPE_EMPTY;
	_selectedTypeColor = RGB(255, 255, 255);

	_startPointSet = false;
	_endPointSet = false;

	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			_tile[i][j].type = TILE_TYPE_EMPTY;
			_tile[i][j].color = RGB(255, 255, 255);
			_tile[i][j].parent = NULL;
			_tile[i][j].F = BIGNUM;
			_tile[i][j].H = 0;
			_tile[i][j].i = i;
			_tile[i][j].j = j;
			_tile[i][j].rc =
				// Ÿ�� ����µ� ������ �������� �ؼ� �������� ���鲨
				// �̷��� ����� ������ ���� ������ ������ �ַ��� �ϴ°�
				RectMake(
					WINSIZEX - (TILE_X + 1) *  WIDTH + WIDTH * j,
					WINSIZEY / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT * i,
					WIDTH, HEIGHT);
		}
	}

	return S_OK;
}

void AStar::Release()
{
}

void AStar::Update()
{
	if (_aStarState == ASTAR_STATE_END) {
		// Ÿ�� ����( start, end, wall empty)
		TileComposition();
	}

	if(INPUT->GetKeyDown(VK_SPACE) && 
		_startPointSet && _endPointSet 
		&& _aStarState == ASTAR_STATE_END) {
		// star, end, wall, empty ���� ���־���ϴ� �κ� �ʱ�ȭ
		TileInitializing();
	}

	// ���ᰡ �Ǿ��� ��
	if (_aStarState == ASTAR_STATE_END ||
		_aStarState == ASTAR_STATE_FOUND ||
		_aStarState == ASTAR_STATE_NOWAY) return;

	AddOpenList();
	CalculateH();
	CalculateF();
	AddCloseList();
	CheckArrive();
}

void AStar::Render()
{
	// �ѹ� �� ������� �ʱ�ȭ �����ִ°� ��� ���Ÿ� �ּ�ó��
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	SetTextColor(GetMemDC(), RGB(0, 0, 0));

	TextOut(GetMemDC(), 10, 80,  "1 : EMPTY", strlen("1 : EMPTY"));
	TextOut(GetMemDC(), 10, 100, "2 : START", strlen("2 : START"));
	TextOut(GetMemDC(), 10, 120, "3 : END",   strlen("3 : END"));
	TextOut(GetMemDC(), 10, 140, "4 : WALL",  strlen("4 : WALL"));

	char str[128];
	if (_aStarState == ASTAR_STATE_END)
		sprintf_s(str, "Press Space to Start");
	else if (_aStarState == ASTAR_STATE_FOUND)
		sprintf_s(str, "Way Found!");
	else if (_aStarState == ASTAR_STATE_NOWAY)
		sprintf_s(str, "No Way!");
	else if (_aStarState == ASTAR_STATE_SEARCHING)
		sprintf_s(str, "Now Searching...");

	TextOut(GetMemDC(), 15, 160, str, strlen(str));

	HBRUSH newBrush, oldBrush;
	HFONT newFont, oldFont;

	newFont = CreateFont(
		9, 0, 0, 0,		// �ʺ� 0���� �ص� ���̶� �ʺ��� ū ������ �������ִ°� ����
		FW_NORMAL,
		false,			// ���� ���ϰ� ����
		false,			// ���� ���� ����
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH,	// �ʺ�� ���� �߿��� ū�༮ �������� ���� �����ִ°�
		FF_SWISS,
		"����"			// ����ü
	);
	oldFont = (HFONT)SelectObject(GetMemDC(), newFont);

	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			newBrush = CreateSolidBrush(_tile[i][j].color);
			oldBrush = (HBRUSH)SelectObject(GetMemDC(), newBrush);

			Rectangle(GetMemDC(),
				_tile[i][j].rc.left, _tile[i][j].rc.top,
				_tile[i][j].rc.right, _tile[i][j].rc.bottom);

			SelectObject(GetMemDC(), oldBrush);
			DeleteObject(newBrush);

			// F ���� ���Ǿ� ��������
			if (_tile[i][j].F < BIGNUM) {
				// ���� �����ϰ�
				SetBkMode(GetMemDC(), TRANSPARENT);
				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].F);
				TextOut(GetMemDC(),
					_tile[i][j].rc.left + 2,
					_tile[i][j].rc.top + 2,
					_tile[i][j].str, strlen(_tile[i][j].str));

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].G);
				TextOut(GetMemDC(),
					_tile[i][j].rc.left + 2,
					_tile[i][j].rc.top + 22,
					_tile[i][j].str, strlen(_tile[i][j].str));

				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].H);
				TextOut(GetMemDC(),
					_tile[i][j].rc.left + 22,
					_tile[i][j].rc.top + 22,
					_tile[i][j].str, strlen(_tile[i][j].str));
			} // end of if(F < BIGNUM)
		} // end of for(j)
	} // end of for(i)

	SelectObject(GetMemDC(), oldFont);
	DeleteObject(newFont);
}

void AStar::TileComposition()
{
	if (INPUT->GetKeyDown('1')) {
		_selectedType = TILE_TYPE_EMPTY;
		_selectedTypeColor = RGB(255, 255, 255);
	}
	else if (INPUT->GetKeyDown('2')) {
		_selectedType = TILE_TYPE_START;
		_selectedTypeColor = RGB(100, 255, 100);
	}
	if (INPUT->GetKeyDown('3')) {
		_selectedType = TILE_TYPE_END;
		_selectedTypeColor = RGB(255, 100, 100);
	}
	if (INPUT->GetKeyDown('4')) {
		_selectedType = TILE_TYPE_WALL;
		_selectedTypeColor = RGB(100, 100, 255);
	}

	if (INPUT->GetKey(VK_LBUTTON)) {
		for (int i = 0; i < TILE_Y; i++) {
			for (int j = 0; j < TILE_X; j++) {
				if (PtInRect(&_tile[i][j].rc, g_ptMouse)) {
					// Ŭ�� ��ÿ� start, end �����Ǿ������� false�� ����� �ش� Ÿ�� �����ؾߵǼ�
					if (_tile[i][j].type == TILE_TYPE_START) _startPointSet = false;
					if (_tile[i][j].type == TILE_TYPE_END) _endPointSet = false;

					_tile[i][j].type = _selectedType;
					_tile[i][j].color = _selectedTypeColor;

					if (_selectedType == TILE_TYPE_START) {
						if (_startPointSet) {
							_tile[_startY][_startX].type = TILE_TYPE_EMPTY;
							_tile[_startY][_startX].color = RGB(255,255,255);
						}
						_startPointSet = true;
						_startX = j;
						_startY = i;
					}

					if (_selectedType == TILE_TYPE_END) {
						if (_endPointSet) {
							_tile[_endY][_endX].type = TILE_TYPE_EMPTY;
							_tile[_endY][_endX].color = RGB(255, 255, 255);
						}
						_endPointSet = true;
						_endX = j;
						_endY = i;
					}

				} // end of if(PtInRect)
			} // end of for(j)
		} // end of for(i)
	} // end of if(INPUT->VK_LBUTTON)
}

void AStar::TileInitializing()
{
	for (int i = 0; i < TILE_Y; i++) {
		for (int j = 0; j < TILE_X; j++) {
			if (_tile[i][j].type == TILE_TYPE_EMPTY) {
				_tile[i][j].listOn = false;
				_tile[i][j].walkable = true;
			}
			else if (_tile[i][j].type == TILE_TYPE_WALL) {
				_tile[i][j].listOn = false;	// �޴ٰ� �ص� �Ǳ���
				_tile[i][j].walkable = false;
			}
			else if (_tile[i][j].type == TILE_TYPE_START) {
				// ���������� ����Ʈ�� �� �־����
				_tile[i][j].listOn = true;
				_tile[i][j].walkable = true;
				_closeList.push_back(&_tile[i][j]);
			}
			else if (_tile[i][j].type == TILE_TYPE_END) {
				_endX = j;
				_endY = i;

				_tile[i][j].listOn = false;
				_tile[i][j].walkable = true;
			}
		}
	}

	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void AStar::AddOpenList()
{
}

void AStar::CalculateH()
{
	for (int i = 0; i < _openList.size(); i++) {
		int vertical = (_endX - _openList[i]->j) * 10;
		int horizontal = (_endY - _openList[i]->i) * 10;

		// ������ �ݴ�� �Ѿ�� ���
		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;
	}
}

void AStar::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++) {
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void AStar::AddCloseList()
{
}

void AStar::CheckArrive()
{
}

void AStar::ShowWay(aStarTile * tile)
{
}
