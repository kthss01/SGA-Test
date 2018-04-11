#pragma once

// ���� ȭ�� 640 * 640
#define TILESIZE 32
#define TILEX 20
#define TILEY 20

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

// 16���� 0 8���ε� 0 2�� �� 1byte�� �����
// ��Ʈ���� �Ϸ��� ���Ŷ�� �Ͻ�
// �Ӽ� �߰��Ϸ��� *2 �ϴ½ķ� �ϸ� �� �������� 4
// 3d ���ԵǸ� �� �̰ɷ� �ؾߵǴ��� �� �� ����
#define ATTR_UNMOVE 0x00000001	// ������ �� ���°�
#define ATTR_POSTION 0x00000002 // 

// ���� �Ӽ�
// ���� �� ���� ���� �ϰų�, 
// �̵��� �� ���� ����, 
// Ÿ�Ͽ� ���� �ӵ� ���� ���� �� �� ���

enum TERRAIN {
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

// ���� ���ʿ� ��ġ
// �����̰ų� �μ����ų� �ϴ� �͵� (����, ĳ���� �̷� ��ȭ�� �� �� �ִ� ��ü)
enum OBJECT {
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_BLOCK3,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_FLAG1,		// ��� �¸� ����
	OBJ_FLAG2,
	OBJ_NONE
};

// ��ġ ��ǥ
enum POS {
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

// Ÿ�� ����ü
struct tagTile {
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};