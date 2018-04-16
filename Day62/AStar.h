#pragma once

#include "GameNode.h"

#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40
// ����� ū F �� (�ʱⰪ ����, ������ �� ���� �� ����ġ ũ�� �ٶ�)
#define BIGNUM 5000	

// Ÿ�� �Ӽ�
/*
	������ ��� ���� ��ġ start �� ��ġ�� end
	Ű������ ���� AStar �����ϱ� ���� ���� ���� ������
	���� ���콺 �̵��� ��� �� ��ġ start ���콺 Ŭ���� Ÿ���� end
*/
enum TILE_TYPE {
	TILE_TYPE_EMPTY,
	TILE_TYPE_START,
	TILE_TYPE_END,
	TILE_TYPE_WALL,
};

enum ASTAR_STATE {
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	// AStar�� ������ �� �մ� ���¶�� ���� �� (start end ��ġ ������)
	ASTAR_STATE_END		
};

// F �� ���
// F = G + H
// G -> ���� 10, �밢�� 14 ������ �°� �ϸ� ��
// H -> �˻� �������� END������ ���� �Ÿ� 

struct aStarTile {
	RECT rc;
	COLORREF color;
	bool walkable;		// Ÿ�� ���� ������ �� �ִ��� Ȯ��
	// openList�� �߰��Ǿ��ִ��� �ߺ��˻� ȸ���ϱ����ؼ� bool �� �ذ�
	// vector ���� ����
	bool listOn;
	int i, j;			// �迭�� �ε��� start, end �κ� ������ ���ؼ� �ʿ�
	int F, G, H;
	char str[128];

	aStarTile* parent;	// �θ� Ÿ�� �Ӽ�
	TILE_TYPE type;
};

class AStar : public GameNode
{
private:
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState;
	TILE_TYPE _selectedType;
	COLORREF _selectedTypeColor;

	// �� �ΰ����� ���ϸ��
	int _startX, _startY;	// �������� i,j �ε���
	int _endX, _endY;		// �������� i,j �ε���
	//

	int _lastIndex;			// ���� ���߿� �߰��� Ŭ���� ����Ʈ �ε���

	// start, end �Ѵ� �־�߸� �ؼ�
	bool _startPointSet;	// ��ŸƮ�� �����Ǿ��ִ���
	bool _endPointSet;		// ���尡 �����Ǿ��ִ��� 

	int Ci;					// ������ Ŭ���� ����Ʈ i
	int Cj;					// ������ Ŭ���� ����Ʈ j
	int Cg;					// ������ Ŭ���� ����Ʈ g

public:
	AStar();
	~AStar();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// A Star ���� ������ �ʿ��� �Լ���
	void TileComposition();	 // Ÿ�� ��ġ

	// A Star ���� �� �ʿ��� �Լ���
	void TileInitializing(); // Ÿ�� ��ġ �� �ʱ�ȭ ���� �� �ѹ��� ����

	void AddOpenList();		// ���� ����Ʈ�� �߰�
	void CalculateH();		// H �� ���
	void CalculateF();		// F �� ���
	void AddCloseList();	// Ŭ���� ����Ʈ�� �߰�
	void CheckArrive();		// ���� ����

	void ShowWay(aStarTile* tile);
};

