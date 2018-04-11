#pragma once

#include "GameNode.h"

// ����â�� ����µ� �ʿ��� ���
#include <commdlg.h>
#include "TileMap.h"

//// ���� ȭ�� 640 * 640
//#define TILESIZE 32
//#define TILEX 20
//#define TILEY 20
//
//#define TILESIZEX TILEX * TILESIZE
//#define TILESIZEY TILEY * TILESIZE
//
//// ���� �Ӽ�
//// ���� �� ���� ���� �ϰų�, 
//// �̵��� �� ���� ����, 
//// Ÿ�Ͽ� ���� �ӵ� ���� ���� �� �� ���
//
//enum TERRAIN {
//	TR_CEMENT,
//	TR_GROUND,
//	TR_GRASS,
//	TR_WATER,
//	TR_END
//};
//
//// ���� ���ʿ� ��ġ
//// �����̰ų� �μ����ų� �ϴ� �͵� (����, ĳ���� �̷� ��ȭ�� �� �� �ִ� ��ü)
//enum OBJECT {
//	OBJ_BLOCK1,
//	OBJ_BLOCK2,
//	OBJ_BLOCK3,
//	OBJ_TANK1,
//	OBJ_TANK2,
//	OBJ_FLAG1,		// ��� �¸� ����
//	OBJ_FLAG2,
//	OBJ_NONE
//};
//
//// ��ġ ��ǥ
//enum POS {
//	POS_FLAG1,
//	POS_FLAG2,
//	POS_TANK1,
//	POS_TANK2
//};
//
//// Ÿ�� ����ü
//struct tagTile {
//	TERRAIN terrain;
//	OBJECT obj;
//	RECT rc;
//	int terrainFrameX;
//	int terrainFrameY;
//	int objFrameX;
//	int objFrameY;
//};

class MainGame : public GameNode
{
private:
	bool isDebug;
	bool isStart;

	POINT imageFrame;
	tagTile _tiles[TILEX*TILEY];

	int _pos[2];

	CTRL _currentCTRL;

	char str[128];
public:
	MainGame();
	~MainGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void MapToolSetup();
	void SetMap();

	TERRAIN TerrainSelect(int frameX, int frameY);
	OBJECT ObjSelect(int frameX, int frameY);

	void Save();
	void Load();
};

/*
	����
	�� ��������
	�Ķ��� Ÿ���� �� ������ ������ Ÿ�Ͽ��� �Ķ��� Ÿ��
*/

/*
	���� -> �ʿ� ������Ʈ ��ġ
	�����̽� �ٸ� ������ ������ �߰�
	���� ���� ���� �������� ������Ʈ ������ �ֱ�
	1,2,3 ������Ʈ (1��,2��,3�� ������Ʈ) ��ġ ����� �ϰ� ������ ����
	3��¥���� 2��¥���� �ٲ�� 1��¥�� ������ ����
	������ �� ������������ �� �տ�����
	������Ʈ�� �˾ƺ��� ���� �ǹ� ȸ���� 3�� �ʷϻ� 2�� �Ķ��� 1������
	�̹��� ����� �ؼ�
*/