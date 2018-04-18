#pragma once

#include "GameNode.h"

#define CELL_WIDTH 100
#define CELL_HEIGHT 50

#define RADIUS_WIDTH CELL_WIDTH / 2
#define RADIUS_HEIGHT CELL_HEIGHT / 2

// �ʱ� ��ǥ
#define INIT_X 400
#define INIT_Y 20

#define TILE_COUNT_X 100
#define TILE_COUNT_Y 100

class IsoTest : public GameNode
{
private:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;	// Ÿ�Ͽ� ���� �ε��� ��ȣ
	// ����� Ŭ���ߴ��� Ȯ���������(�̰� ��Ʈ �� Ÿ��) 
	// �𼭸� Ŭ���ϸ� �ٸ� Ÿ����
	int _center;	
	char str[128];
	
	int _startX;
	int _startY;
public:
	IsoTest();
	~IsoTest();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// Ÿ�� �� ���� 
	// ���� �̾ �׷��ٲ�
	void DrawTileMap();	
	// ������ �׷��ִ� �Լ�
	// �簢���� �������� �׷��ٲ� �׷��� left, top �ʿ�
	void DrawRhombus(int left, int top);	// ������ == rhombus
	// �ڳ� ����
	int GetCornerIndex(int isoX, int isoY);
	// �ڳ� �ȿ� �ִ��� ����
	bool IsInRhombus(int corner, int isoX, int isoY);
};

