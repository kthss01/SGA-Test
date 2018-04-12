#include "stdafx.h"
#include "TankMap.h"


TankMap::TankMap()
{
}


TankMap::~TankMap()
{
}

HRESULT TankMap::Init()
{
	Load();

	return S_OK;
}

void TankMap::Release()
{
}

void TankMap::Update()
{
}

void TankMap::Render()
{
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
}

void TankMap::Load()
{
	// api�� �������ִ� save �Լ� ���
	// ����ü�� ���� ���� �ְ�
	// ���������� �迭�ε� ���� �� ����
	HANDLE file;
	DWORD read;

	// CreateFile Binary �������� ��
	// Binary 16���� ������ �������� ��
	// Binary �ѱ� �������� ������ �־���
	// binary�� �Ϲ����� fopen ���� ���� ��� ���ٷ� �� ����
	file = CreateFile(
		"save/tileMap.map",	// ������ ���� �Ǵ� �ε��� ������ �̸�
		GENERIC_READ, /// ����	// �����̳� ��ġ�� ����ų� ������ ����
		0,				// ���� ���� ��� �Է�
		NULL,			// ���� �Ǵ� ��ġ�� �� �� ���� �� Ư��
						// �׻� ó������ �ۼ��ϰڴٴ°� �� �����
						// ���� �ٲ��ָ� ���κ��� ���� �� ����
		OPEN_EXISTING, /// ����	// �����̳� ��ġ�� �� �� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,	// ����, ��ġ�� �� ��, ���� �� ���� Ư��
		NULL			// ������� ������ ���� �� Ư�� etc ����Ǵ� �ڵ�
	);

	// �������� ���� ���� �� ���Ƿ� ������� �����ؼ� �о�;���
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	CloseHandle(file);

	ZeroMemory(_attributes, sizeof(DWORD)*TILEX*TILEY);
	for (int i = 0; i < TILEX*TILEY; i++) {
		if (_tiles[i].terrain == TR_WATER) _attributes[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK1) _attributes[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK2) _attributes[i] = ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_BLOCK3) _attributes[i] = ATTR_UNMOVE;
	}
}

POINT TankMap::GetOBJECTFrame(OBJECT obj)
{
	POINT pos = {};

	switch (obj)
	{
	case OBJ_BLOCK1:
		pos = { 4,17 };
		break;
	case OBJ_BLOCK2:
		pos = { 4,14 };
		break;
	case OBJ_BLOCK3:
		pos = { 5,17 };
		break;
	}

	return pos;
}
