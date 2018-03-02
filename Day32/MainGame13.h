#pragma once

#include "GameNode.h"

class MainGame13 : public GameNode
{
private:
	Image * m_rockman;	// 록맨 프레임 이미지
	int m_indexX;
	int m_indexY;
	bool m_isLeft;

	// DWORD 4바이트로 되어있는 설정이 안된 변수
	// int, float char 다 넣을 수 있음 음수는 안됨
	// DWORD 사용 하는 경우 
	// Color값 넣을 때 많이 씀 RGBA 값
	// 순서 지정하려 할때 index
	// 시간 넣을 때
	DWORD prevTime;		
	DWORD curTime;

	int posX, posY;	// 위치 값
public:
	MainGame13();
	~MainGame13();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

};

/*
	과제
	점프 및 벽잡기
	위치에 닿으면 벽잡는거
	점프도 가능하고 위로 누르면 올라가는

	함수 채워오기
	Image 클래스에 작성해 줄 껀데 이거에 대한 함수만 채워오기

	// 예시
	// Get, Set 함수들 다 만들어 오기 
	// 이미지의 좌표 X
	inline float GetX() { return m_imageInfo->x; }
*/

