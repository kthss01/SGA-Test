#pragma once

#include "GameNode.h"

// 미니맵은 단순히 현재 맵에서 비율별로 출력한다고 생각하면됨
/*
	화면전체값 1 / 10 으로 줄여서
*/

enum playerState {
	PS_IDLE,
	PS_RUN
};

class MiniMap : public GameNode
{
private:
	Image * _megaman;
	int _alpha;
	int _camera;	// 캐릭터 움직이면 카메라의 위치 바꿔줄꺼
	int _index;	// 애니메이션 프레임을 돌릴 녀석
	bool _isLeft;
	playerState _ps;
public:
	MiniMap();
	~MiniMap();

	HRESULT Init();
	void Release();
	void Update();
	void Render();
};

