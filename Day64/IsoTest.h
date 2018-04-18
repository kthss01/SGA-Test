#pragma once

#include "GameNode.h"

#define CELL_WIDTH 100
#define CELL_HEIGHT 50

#define RADIUS_WIDTH CELL_WIDTH / 2
#define RADIUS_HEIGHT CELL_HEIGHT / 2

// 초기 좌표
#define INIT_X 400
#define INIT_Y 20

#define TILE_COUNT_X 100
#define TILE_COUNT_Y 100

class IsoTest : public GameNode
{
private:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;	// 타일에 대한 인덱스 번호
	// 가운데를 클릭했는지 확인해줘야함(이게 렉트 안 타일) 
	// 모서리 클릭하면 다른 타일임
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

	// 타일 맵 랜더 
	// 선을 이어서 그려줄꺼
	void DrawTileMap();	
	// 마름모를 그려주는 함수
	// 사각형을 기준으로 그려줄꺼 그래서 left, top 필요
	void DrawRhombus(int left, int top);	// 마름모 == rhombus
	// 코너 검출
	int GetCornerIndex(int isoX, int isoY);
	// 코너 안에 있는지 검출
	bool IsInRhombus(int corner, int isoX, int isoY);
};

