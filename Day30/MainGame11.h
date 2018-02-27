#pragma once

#include "GameNode.h"
#include "Image.h"

// 총알 각도에 따른 발사
#define BULLETMAX 50

struct tagBullet {
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	bool fire;
};

struct tagPlayer {
	POINT center;		// 플레이어 시작 지점
	POINT cannonEnd;	// 포신 끝점 (발사 지점)
	float angle;
	float cannon;		// 포신의 길이
	float raduis;
	float power;
};

class MainGame11 : public GameNode
{
private:
	tagPlayer m_player;
	tagBullet m_bullet[BULLETMAX];


	Image* bg;
	Image* apple;
	Image* apple2;

	bool isDraw;
public:
	MainGame11();
	~MainGame11();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Fire();			// 총알 발사
	void MoveBullet();		// 총알 무브
};

/*
	과제 지렁이 게임

	이미지 씌어오기

	머리 몸통 꼬리
	
	100 0 머리 99 꼬리 1 ~ 98 몸통 이미지 넣기

	// 추가 옵션
	내가 가는 방향에 따라 머리의 이미지 회전까지 해보기 -> 쉽지는 않음
	함수는 있는데 이해하기 쉽진 않을꺼라고 하심

	마젠타 값 안지워질 때 문제

	비트맵 그림 오른쪽 속성 보면
	비트수준 32 64 이렇게 있음
	최근에 OS 버전 올렸는데 문제가 될 수 있음
	
	윈도우 10 24 비트맵 색상 255, 0, 255
	마젠타 값				 255, 0, 255
	윈도우 10 32 비트맵 색상 255, 0, 255 로 되어있기도함
							 254, 0, 254

	윈도우 7				 255, 0, 255
*/

/*
	이미지 회전
	SetWorldTransform (행렬 계산)

	3D 
	D3DXVECTOR3(x, y, z)

	D3DXMATRIX16 -> 4 x 4

	이 둘로 만들면 API에서도 3D로 만들 수 있음

	// API에서 만들려면 
	이미지 회전이랑 픽셀 계산도 해줘야함

	3D 사용하려면
	#include <d3d9.h> 필요함
*/