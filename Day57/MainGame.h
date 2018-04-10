#pragma once

#include "GameNode.h"

// 선택창을 만드는데 필요한 헤더
#include <commdlg.h>

// 메인 화면 640 * 640
#define TILESIZE 32
#define TILEX 20
#define TILEY 20

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

// 지형 속성
// 밟을 때 사운드 나게 하거나, 
// 이동할 수 없는 지역, 
// 타일에 따른 속도 변경 설정 할 때 사용

enum TERRAIN {
	TR_CEMENT,
	TR_GROUND,
	TR_GRASS,
	TR_WATER,
	TR_END
};

// 지형 위쪽에 배치
// 움직이거나 부서지거나 하는 것들 (몬스터, 캐릭터 이런 변화를 줄 수 있는 물체)
enum OBJECT {
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_BLOCK3,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_FLAG1,		// 깃발 승리 조건
	OBJ_FLAG2,
	OBJ_NONE
};

// 위치 좌표
enum POS {
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};

// 타일 구조체
struct tagTile {
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

class MainGame : public GameNode
{
private:
	bool isDebug;

	POINT imageFrame;
	tagTile _tiles[TILEX*TILEY];

	int _pos[2];

	CTRL _currentCTRL;

//////////////////////////////////////////
	// Day 57
	//struct RenderImage{
	//	POINT position;
	//	POINT frame;
	//};
	//vector<RenderImage> images;
	//Image * bg;
	//
	//OPENFILENAME OFN;
	//char filePath[MAX_PATH];	// 최대 경로 길이
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

	// 내일 오늘 만든걸로 타일 충돌 할꺼
	// 타일 번호 7,4 충돌되서 이동할 수 없는 타일로 할꺼
	// 이 타일이 포함된 맵 만들어서 로드해오기
	//.................//
	void Save();
	void Load();
};

/*
	과제
	맵 만들어오기
	파란색 타일이 꼭 들어가야함 마지막 타일에서 파란색 타일
*/
