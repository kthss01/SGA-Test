#include "stdafx.h"
#include "MainGame13.h"


MainGame13::MainGame13()
{
}


MainGame13::~MainGame13()
{
}

HRESULT MainGame13::Init()
{
	GameNode::Init();

	// 록맨 위치 좌표 초기화
	posX = WINSIZEX / 2;
	posY = WINSIZEY / 2;

	// 록맨 이미지 초기화
	m_rockman = new Image;
	// 960 x 200 이 록맨 이미지 크기 사이즈 쯤 됨
	m_rockman->Init("images/록맨.bmp", posX, posY, 480, 100,
		10, 2, true, RGB(255, 0, 255));

	/*
		여러장 초기화
	*/
	//char str[256];
	//for (int i = 1; i < 11; i++) {
	//	sprintf_s(str, "images/왼쪽 걷기%d.bmp", i);
	//	m_rockman->Init(str, posX, posY, 480, 100,
	//		10, 2, true, RGB(255, 0, 255));
	//}

	// 프레임 돌릴 변수들 초기화
	m_isLeft = false;
	m_indexX = m_indexY = 0;

	// os를 부팅하고나서부터 현재까지의 시간
	prevTime = GetTickCount();

	return S_OK;
}

void MainGame13::Release()
{
	GameNode::Release();
	SAFE_DELETE(m_rockman);
}

void MainGame13::Update()
{
	GameNode::Update();

	curTime = GetTickCount();

	/*
		반걸치면 나오게 하는거
		
		사라진 부분만큼 따로 그리게 함 (렌더링 두번) 

		이미지를 잘라 부분만 반대쪽에 그리게 함 (렌더링 한번) - 이방법 많이 씀
	*/

	if (INPUT->GetKey('A')) {
		posX -= 5;
		m_isLeft = true;
		// 한 프레임의 가로 너비 보다 작으면
		if (posX < 0 - 48) {
			posX = WINSIZEX;
		}
	}
	if (INPUT->GetKey('D')) {
		posX += 5;
		m_isLeft = false;
		if (posX > WINSIZEX) {
			// 0이 아니라 48 한 이유는 화면 밖에서 들어오게 할 수 있게
			posX = -48;
		}
	}

	// 지금 코드는 방향 변경되면 중간에 강탈되는 방식임
	// 어떤 이미지는 자연스럽지 않을 수 있음

	// 왼쪽을 바라보고 있으면
	if (m_isLeft) {
		m_indexY = 1;
		if (curTime - prevTime > 50)
		{
			m_indexX--;
			if (m_indexX < 0)
			{
				// index 10은 안그려진 부분
				// 안끊기게 하고 싶으면 9로 변경
				m_indexX = 9;
			}
			prevTime = GetTickCount();
		}
	}
	// 오른쪽을 바라보고 있으면
	else {
		m_indexY = 0;
		if (curTime - prevTime > 50)
		{
			m_indexX++;
			if (m_indexX > 10)
			{
				m_indexX = 0;
			}
			prevTime = GetTickCount();
		}
	}
}

void MainGame13::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===============================================
	{
		m_rockman->FrameRender(memDC, posX, posY,
			m_indexX, m_indexY);
	}
	//===============================================
	this->GetBackBuffer()->Render(hdc);
}
