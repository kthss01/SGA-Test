#pragma once

#include "GameNode.h"

#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40
// 충분히 큰 F 값 (초기값 설정, 지나갈 수 없는 길 가중치 크게 줄때)
#define BIGNUM 5000	

// 타일 속성
/*
	몬스터일 경우 몬스터 위치 start 내 위치가 end
	키보드일 경우는 AStar 적용하기 조금 힘듬 방향 때문에
	내가 마우스 이동일 경우 내 위치 start 마우스 클릭한 타일이 end
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
	// AStar가 실행할 수 잇는 상태라고 보면 됨 (start end 위치 설정된)
	ASTAR_STATE_END		
};

// F 총 비용
// F = G + H
// G -> 직선 10, 대각선 14 비율만 맞게 하면 됨
// H -> 검색 지점에서 END까지의 직선 거리 

struct aStarTile {
	RECT rc;
	COLORREF color;
	bool walkable;		// 타일 위로 지나갈 수 있는지 확인
	// openList에 추가되어있는지 중복검사 회피하기위해서 bool 값 준거
	// vector 따로 있음
	bool listOn;
	int i, j;			// 배열의 인덱스 start, end 부분 설정을 위해서 필요
	int F, G, H;
	char str[128];

	aStarTile* parent;	// 부모 타일 속성
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

	// 이 두가지만 변하면됨
	int _startX, _startY;	// 시작지점 i,j 인덱스
	int _endX, _endY;		// 도착지점 i,j 인덱스
	//

	int _lastIndex;			// 가장 나중에 추가된 클로즈 리스트 인덱스

	// start, end 둘다 있어야만 해서
	bool _startPointSet;	// 스타트가 지정되어있는지
	bool _endPointSet;		// 엔드가 지정되어있는지 

	int Ci;					// 마지막 클로즈 리스트 i
	int Cj;					// 마지막 클로즈 리스트 j
	int Cg;					// 마지막 클로즈 리스트 g

public:
	AStar();
	~AStar();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// A Star 시작 전까지 필요한 함수들
	void TileComposition();	 // 타일 배치

	// A Star 시작 후 필요한 함수들
	void TileInitializing(); // 타일 배치 후 초기화 시작 후 한번만 실행

	void AddOpenList();		// 오픈 리스트에 추가
	void CalculateH();		// H 값 계산
	void CalculateF();		// F 값 계산
	void AddCloseList();	// 클로즈 리스트에 추가
	void CheckArrive();		// 도착 여부

	void ShowWay(aStarTile* tile);
};

