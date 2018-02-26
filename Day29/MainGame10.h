#pragma once

#include "GameNode.h"

// 지렁이게임 풀이
// 과제 해결 방법 조금 잘못되었었음
// 각도도 넘겨줘야했고 꼬리들이 겹치지 않았어야함
// 확실히 비교해보니 선생님 방법이 신기함

#define BEADMAX 100

struct tagBead {
	float x, y;
	float angle;
	float speed;
	float radius;
};

// 원 사각형 충돌

// 시간 복잡도, 공간 복잡도
/*
	코드에 대한 정답은 없지만 효율적인 정도는 있음
*/

class MainGame10 : public GameNode
{
private:
	tagBead _bead[BEADMAX];


	RECT m_rc; // 사각형
	RECT m_el; // 원

	POINT m_ptSave;
	POINT m_elCenter;	// 원의 중심점
	float m_radius;

	bool m_touch;		// 원하고 마우스 클릭했는지

	RECT m_block[20];
public:
	MainGame10();
	~MainGame10();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void BeadMove();

	bool RectInCircle(RECT* rect, POINT circleCenter, float radius);
};

/*
	과제
	벽돌 깨기
	그 때 영상 보여줬던 벽돌 깨기처럼 구현해보기
*/