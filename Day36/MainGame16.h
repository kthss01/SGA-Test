#pragma once

#include "GameNode.h"
#include "Image.h"

class MainGame16 : public GameNode
{
private:
	bool isDebug;

	// 레이싱 게임

	float m_speed; // 계기판 , 배경이미지, 컴퓨터 차량
	float m_carX;
	float m_carY;
	int m_endX, m_endY;	// 계기판에서 쓰는 라인에 끝점

	Image* m_bg;
	Image* m_computer;
	Image* m_player;
	Image* m_circle;

	RECT m_rcPlayer;
	RECT m_rcComputer[5];
	float m_loopCount;

	bool m_isStart;
public:
	MainGame16();
	~MainGame16();

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void PlayerMove();
	void ComputerMove();
};

/*
	api 도 jpg png 출력 가능
	gdiPlus 이용해서 하는거라 좀 힘듬

	이미지 로드 속도 부분
	API win32API -> bmp 기본 사용 가능 -> CPU 랜더링
										-> FPS (초당 몇 프레임을 출력하느냐)
										-> 기본 60 프레임

	GDI+ (GDI의 확장 버전)
	웬만한 이미지는 다 가능 -> bmp, jpg, png-> CPU 랜더링
										-> 프레임 많이 떨어짐

	Direct2D -> bmp, jpg, png, dds-> GPU 랜더링 ->
									gdi+ 더 빠름

	속도
	GDI+ < API < Direct2D

	코드 (난이도)
	API < GDI+ < Direct2D

	Direct2D 장점
	imageLoad 편함 (어떤 포맷이든 읽어올 수 있음)
	이미지 변경이 쉬움
	 -> 하나의 이미지로 이미지 조절해서 애니메이션 표현 가능
	쉐이더 - 색상 관련있는 효과라고 생각하면 됨
	Direct2D 단점
	코드량이 많음 
	초기화 할때도 코드 많이 필요
	개념 부분이 조금 힘듬
	기하학 Vector 를 기본적을 사용하게 되서
	행렬 

	렌더링 파이프 라인
	-> 기본형 9가지
	1. 고정 파이프 라인
	2. cordinable 파이프 라인
	(쉐이더 만들어서 적용 시킬 때)
	vertex 쉐이더, pixel 쉐이더 ( hlsl 언어)
	-> 11가지로 바뀌게 됨

	3D 가면 공부해야할 꺼
	Directx -> 함수 변수 용어 
	float + Vector + matrix;
	3D 좌표 개념
*/