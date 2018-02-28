#pragma once

#include "GameNode.h"


#define BEADMAX 100

struct tagBead {
	float x, y;
	float angle;
	float speed;
	float radius;
};

class MainGame12 : public GameNode
{
private:
	Image * image[3];
	Image * bg;

	tagBead _bead[BEADMAX];

	int x, y;
	BYTE alpha;
public:
	MainGame12();
	~MainGame12();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void BeadMove();
};

/*
	과제
	
	1. 콘솔에서 슬라이드 퍼즐 만들었음
	이번에는 슬라이드 퍼즐 이미지 넣어서 만들기
	3x3 이상

	맞추고 나면 전체 이미지 (원래 이미지) 뜨게 끔 
	
	이미지 줄꺼임
	마리오랑 (움직이는 모션) 타일 이미지 (하나) 줄꺼
	
	바닥에서 뛰는거랑 점프
	벽 통과 왼쪽으로 가면 오른쪽으로 나오는거

	마리오 캐릭터 이동(왼쪽, 오른쪽) 뛰는 이미지
	점프했을 때 뛰고 떨어지면 바닥에서 멈추게
	이단 점프 금지 (한번 점프하면 끝나게)
	벽통과 왼->오 오->왼 
	벽통과시 떨어지거나 점프한 각도로 갈 수 있어야함

	512 픽셀이면 나누기 하면 딱 떨어짐
	너비 8로 나누고
	높이 4

	64 x 82 크기 정도라고 보면됨

	회전
	patlt
	SetWorldTransform 

	winapi에서는 굳이 어렵게 할 필요는 없음
	다이렉트에서는 쉽게 할 수 있음
*/

/*
	타일 하나로 하는 이유
	맵을 사용하기 쉽다는 장점도 있고
	한정된 자원으로 만들기 쉽고
	a* 알고리즘에서 사용하는 이유
	이동할 수 잇을지 없는지 같은 걸 정하기 편하기 위해서
*/

/*
	컴퓨터 언어
	0000 0000 

	byte 8bit만 담음
	0 ~ 255

	계속해서 숫자 증가시
	255
	  1111 1111
	255 + 1
	1 0000 0000
	앞에 1 날라가므로 0이 됨

	그래서 컴퓨터 시계 몇십 년 후면 다시 초기화 될꺼
	이에 대한 수정 할꺼라고 함
*/