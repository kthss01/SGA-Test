#include "stdafx.h"
#include "MainGame16.h"


MainGame16::MainGame16()
{
}


MainGame16::~MainGame16()
{
}

HRESULT MainGame16::Init()
{
	GameNode::Init();

	m_bg = new Image;
	m_bg->Init("images/background.bmp", WINSIZEX, WINSIZEY);

	m_player = new Image;
	// 선생님은 5개 짜리 스프라이트 이미지 쓰심
	m_player->Init("images/wario.bmp",
		100, 120, true, RGB(182, 185, 183));

	m_computer = new Image;
	m_computer->Init("images/mario.bmp",
		100, 120, true, RGB(182, 185, 183));

	m_circle = new Image;
	m_circle->Init("images/speedometer.bmp", 
		120, 120, true, RGB(182, 185, 183));

	for (int i = 0; i < 5; i++) {
		m_rcComputer[i] = RectMake(200 + 100 * i,
			-100 - RND->GetInt(5) * 100, 120, 120);
	}

	m_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 100, 120);

	// 계기판 좌표
	m_carX = WINSIZEX - 100; 
	m_carY = WINSIZEY - 100;

	m_speed = 0.0f;
	m_isStart = false;
	m_loopCount = 0.0f;

	return S_OK;
}

void MainGame16::Release()
{
	GameNode::Release();

	SAFE_DELETE(m_computer);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_bg);
	SAFE_DELETE(m_circle);
}

void MainGame16::Update()
{
	GameNode::Update();

	this->PlayerMove();
	this->ComputerMove();

	// 계기판
	m_endX = m_carX + cos((180 + m_speed) * PI / 180) * 50.0f;
	m_endY = m_carY + sin((180 + m_speed) * PI / 180) * 50.0f;

	if (INPUT->GetKey(VK_UP) && m_speed < 180)
	{
		m_speed++;
		if (!m_isStart) {
			m_isStart = true;
		}
	}

	m_loopCount -= m_speed / 10;

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame16::Render(HDC hdc)
{
	HDC memDC = GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		RECT temp = { 0, 0, WINSIZEX, WINSIZEY };
		//m_bg->Render(memDC);
		m_bg->LoopRender(memDC, &temp, 0, m_loopCount);
		for (int i = 0; i < 5; i++) {
			m_computer->Render(memDC, 
				m_rcComputer[i].left, m_rcComputer[i].top);
		}
		m_player->Render(memDC, m_rcPlayer.left, m_rcPlayer.top);
		//m_player->LoopRender(memDC, &temp, 0, 0);
		m_circle->Render(memDC,
			m_carX - m_circle->GetWidth() / 2,
			m_carY - m_circle->GetHeight() / 2);
		LineMake(memDC, m_carX, m_carY, m_endX, m_endY);
	}
	//==================   Debug   ====================
	if (isDebug)
	{

	}
	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame16::PlayerMove()
{
}

void MainGame16::ComputerMove()
{
	for (int i = 0; i < 5; i++) {
		m_rcComputer[i].top += m_speed / 10;
		m_rcComputer[i].bottom += m_speed / 10;

		if (m_rcComputer[i].top > WINSIZEY) {
			m_rcComputer[i] = RectMake(200 + 100 * i,
				-100 - RND->GetInt(5) * 100, 100, 100);
		}
		RECT temp;

		if (IntersectRect(&temp, &m_rcPlayer, &m_rcComputer[i])) {
			m_rcComputer[i] = RectMake(200 + 100 * i,
				-100 - RND->GetInt(5) * 100, 100, 100);
			m_speed -= 10;
			if (m_speed < 10 && m_isStart == true) {
				// 게임 종료
				PostQuitMessage(0);
			}
		}
	}
}
