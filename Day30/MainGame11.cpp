#include "stdafx.h"
#include "MainGame11.h"


MainGame11::MainGame11()
{
}


MainGame11::~MainGame11()
{
}

HRESULT MainGame11::Init()
{
	GameNode::Init();

	bg = new Image;
	apple = new Image;
	apple2 = new Image;

	bg->Init(
		"images/배경 화면.bmp",		// 파일 경로 + 파일 이름 + 확장자 명 (시작지점은 프로젝트)
		WINSIZEX,
		WINSIZEY
	);

	// 크기 줄이면 사과 크기도 작아짐
	apple->Init("images/apple.bmp", 124, 162, true, RGB(255, 0, 255));

	/*
		정리
		우선 원래 비트맵 크기로 그리면 255,255,255 시 문제가 생기지 않음
		width를 일정크기 늘려도 문제가 되지 않음
		문제는 height를 1이라도 늘리는 순간 마젠타값이 아니라 254,0,254 로 해야하고
		height 쪽이 아니라 width 쪽이 일정값이상 커지면 254,0,254 해야되는거 같음
		-> 정리 둘다 원래 크기 넘어갈 때 문제 발생함
		왼쪽과 아래쪽에 약간의 마젠타값의 라인이 남게되어
		그 부분을 위해 두번 GdiTransparentBlt 해줘야 하는듯
	*/

	apple2->Init("images/apple.bmp", 125, 163, true, RGB(255, 0, 255));

	isDraw = false;


	m_player.cannon = 80.0f;
	m_player.angle = PI / 4;
	m_player.center.x = 0;
	m_player.center.y = WINSIZEY;

	// 구조체 메모리 0으로 초기화 되는거
	memset(m_bullet, 0, sizeof(m_bullet));

	for (int i = 0; i < BULLETMAX; i++) {
		m_bullet[i].fire = false;
		m_bullet[i].radius = 20.0f;
	}

	return S_OK;
}

void MainGame11::Release()
{
	GameNode::Release();
}

void MainGame11::Update()
{
	GameNode::Update();

	if (INPUT->GetKeyDown(VK_SPACE))
		isDraw = false;

	if (INPUT->GetKey(VK_LEFT) && m_player.angle < PI / 2) 
		m_player.angle += 0.04f;
	if (INPUT->GetKey(VK_RIGHT) && m_player.angle > 0.1f)
		m_player.angle -= 0.04f;

	if (INPUT->GetKeyDown(VK_SPACE)) {
		m_player.power = 1.0f;
	}
	if (INPUT->GetKey(VK_SPACE)) {
		m_player.power += 0.1f;
	}
	if (INPUT->GetKeyUp(VK_SPACE)) {
		Fire();
	}

	MoveBullet();

	m_player.cannonEnd.x = 
		cosf(m_player.angle) * m_player.cannon + m_player.center.x;
	m_player.cannonEnd.y = 
		-sinf(m_player.angle) * m_player.cannon + m_player.center.y;
}

void MainGame11::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		bg->Render(memDC);

		//if (isDraw) {
		//	for (int i = 0; i < 10; i++) {
		//		// 여러개 하나띄우고 여러번 렌더 하면 됨
		//		apple->Render(memDC,
		//			RND->GetFromInto(100, WINSIZEX - 100),
		//			RND->GetFromInto(100, WINSIZEY - 100));
		//		isDraw = true;
		//	}
		//}

		apple->Render(memDC, 300, 300);
		apple2->Render(memDC,100, 100);

		EllipseMakeCenter(
			memDC, m_player.center.x, m_player.center.y, 50);
		LineMake(memDC, m_player.center, m_player.cannonEnd);
		for (int i = 0; i < BULLETMAX; i++) {
			if (!m_bullet[i].fire) continue;
			EllipseMakeCenter(
				memDC, m_bullet[i].x, m_bullet[i].y, m_bullet[i].radius);
		}
	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame11::Fire()
{
	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].fire == true) continue;

		m_bullet[i].fire = true;
		m_bullet[i].x = 
			cosf(m_player.angle) * (m_player.cannon + 10) + m_player.center.x;
		m_bullet[i].y =
			-sinf(m_player.angle) * (m_player.cannon + 10) + m_player.center.y;
		m_bullet[i].speed = m_player.power;
		m_bullet[i].angle = m_player.angle;
		break;
	}
}

void MainGame11::MoveBullet()
{
	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].fire == false) continue;

		m_bullet[i].x += cosf(m_bullet[i].angle) * m_bullet[i].speed;
		m_bullet[i].y += -sinf(m_bullet[i].angle) * m_bullet[i].speed;
	}
}

