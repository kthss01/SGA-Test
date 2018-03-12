#pragma once

#include "GameNode.h"

#define WIDTH 20	// rect 너비 그냥 갯수로 쓸거 row
#define HEIGHT 20	// rect 높이 그냥 갯수로 쓸거 col
#define MINE 80		// 지뢰 갯수

struct tagPuzzle {
	RECT box;		// 지뢰가 있던지 없던지간에 위치할 Rect
	bool choice;
	bool flag;

	// 지뢰도 idNumber 갖고 있고 puzzle과 비교해서 마인 있는지 확인
	int idNumber;	

	// 주변에 있는 마인 갯수 구분 enum으로 해도 됨
	bool purple;
	bool red;
	bool orange;
	bool yellow;
	bool green;
	bool blue;
};

struct tagLandMine {
	RECT mine;
	bool stop;	// mine을 선택했으면 종료해야되기 때문에
	int idNumber;
};

class MineGame : public GameNode
{
private:
	tagPuzzle m_box[WIDTH][HEIGHT];
	tagPuzzle m_shuffleBox[WIDTH * HEIGHT];
	tagLandMine m_mine[MINE];

	HBRUSH m_brush;
	int m_downX, m_downY;	// 현재 내가 클릭한 녀석의 번호

	bool m_win, m_lose;		// 이겻냐 졋냐에 따라 씬 변경하면 됨
	char m_winner[64];
	int m_color;			// 몇개에 따라 색상 바꿀거
	int m_count;			// color와 비슷한 용도

public:
	MineGame();
	~MineGame();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	// destX, destY, downX, downY 들어갈꺼
	void MineCheck(int destX, int destY);
};

