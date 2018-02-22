#include "stdafx.h"
#include "MainGame9.h"


MainGame9::MainGame9()
{
}


MainGame9::~MainGame9()
{
}

HRESULT MainGame9::Init()
{
	GameNode4::Init();
	// 종으로 만들꺼
	m_coat[0] = RectMakeCenter(
		WINSIZEX / 2, WINSIZEY / 2 + WINSIZEY / 4,
		WINSIZEX, WINSIZEY / 2);
	m_coat[1] = RectMakeCenter(
		WINSIZEX / 2, WINSIZEY / 4,
		WINSIZEX, WINSIZEY / 2);
	m_goal[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY, WINSIZEX / 3, 10);
	m_goal[1] = RectMakeCenter(WINSIZEX / 2, 0, WINSIZEX / 3, 10);

	// ball 초기화
	m_ball.speed = 0.0f;
	m_ball.smash = false;
	m_ball.radius = 15;
	m_ball.x = WINSIZEX / 2;
	m_ball.y = WINSIZEY / 2;

	// racket 초기화
	m_racket[0].radius = 20;
	m_racket[0].x = WINSIZEX / 2;
	m_racket[0].y = WINSIZEY / 2 + WINSIZEY / 4;

	m_racket[1].radius = 20;
	m_racket[1].x = WINSIZEX / 2;
	m_racket[1].y = WINSIZEY / 4;

	// score 초기화
	m_score[0] = 0;
	m_score[1] = 0;

	return S_OK;
}

void MainGame9::Release()
{
	GameNode4::Release();
}

void MainGame9::Update()
{
	GameNode4::Update();

	// 1p
	if (INPUT->GetKey(VK_LEFT))	m_racket[0].x -= RACKET_SPEED;
	if (INPUT->GetKey(VK_RIGHT))m_racket[0].x += RACKET_SPEED;
	if (INPUT->GetKey(VK_UP))	m_racket[0].y -= RACKET_SPEED;
	if (INPUT->GetKey(VK_DOWN))	m_racket[0].y += RACKET_SPEED;

	// 2p
	if (INPUT->GetKey('A')) m_racket[1].x -= RACKET_SPEED;
	if (INPUT->GetKey('D')) m_racket[1].x += RACKET_SPEED;
	if (INPUT->GetKey('W')) m_racket[1].y -= RACKET_SPEED;
	if (INPUT->GetKey('S')) m_racket[1].y += RACKET_SPEED;

	for (int i = 0; i < 2; i++) {
		// 왼쪽
		if (m_racket[i].x - m_racket[i].radius < 0)
			m_racket[i].x = 0 + m_racket[i].radius;
		// 오른쪽
		if (m_racket[i].x + m_racket[i].radius > WINSIZEX)
			m_racket[i].x = WINSIZEX - m_racket[i].radius;
		// 위
		if (m_racket[i].y - m_racket[i].radius < m_coat[i].top)
			m_racket[i].y = m_coat[i].top + m_racket[i].radius;
		// 아래
		if (m_racket[i].y + m_racket[i].radius > m_coat[i].bottom)
			m_racket[i].y = m_coat[i].bottom - m_racket[i].radius;
	}
	Smash();

	BallMove();

	// 1번 골대에 골 넣었을 때
	if (m_goal[1].bottom >= m_ball.y - m_ball.radius &&
		m_goal[1].left <= m_ball.x &&
		m_goal[1].right >= m_ball.x) {
		m_score[0]++;

		// 초기화
		m_ball.x = WINSIZEX / 2;
		m_ball.y = WINSIZEY / 2;

		m_racket[0].x = WINSIZEX / 2;
		m_racket[0].y = WINSIZEY / 2 + WINSIZEY / 4;
		
		m_racket[1].x = WINSIZEX / 2;
		m_racket[1].y = WINSIZEY / 4;

		m_ball.smash = false;
	}

	// 0번 골대도 마찬가지
}

// 코드 짤 때 만들어야 할 꺼 많으면
// 하나 만들고 하나 그리는 식으로 하기

void MainGame9::Render(HDC hdc)
{
	HDC memDC = this->GetBackBuffer()->GetMemDC();
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================

	for (int i = 0; i < 2; i++) {
		RectangleMake(memDC, m_coat[i]);
		RectangleMake(memDC, m_goal[i]);
	}

	Ellipse(memDC, m_ball.x - m_ball.radius, m_ball.y - m_ball.radius,
		m_ball.x + m_ball.radius, m_ball.y + m_ball.radius);

	for (int i = 0; i < 2; i++) {
		Ellipse(memDC, 
			m_racket[i].x - m_racket[i].radius, 
			m_racket[i].y - m_racket[i].radius,
			m_racket[i].x + m_racket[i].radius, 
			m_racket[i].y + m_racket[i].radius);
	}

	//=================================================
	this->GetBackBuffer()->Render(hdc);
}

void MainGame9::BallMove()
{
	if (m_ball.smash == true) {
		m_ball.x += cosf(m_ball.angle) * m_ball.speed;
		m_ball.y += -sinf(m_ball.angle) * m_ball.speed;

		m_ball.speed -= 0.03f;

		// 벽 충돌

		// 왼쪽 방향
		if (m_ball.x - m_ball.radius < 0) {
			m_ball.x = 0 + m_ball.radius;
			m_ball.angle = PI - m_ball.angle;
		}
		// 오른쪽 방향
		if (m_ball.x - m_ball.radius > WINSIZEX) {
			m_ball.x = WINSIZEX - m_ball.radius;
			m_ball.angle = PI - m_ball.angle;
		}
		// 위 방향
		if (m_ball.y - m_ball.radius < 0) {
			m_ball.y = 0 + m_ball.radius;
			m_ball.angle = 2 * PI - m_ball.angle;
		}		
		// 아래 방향
		if (m_ball.y + m_ball.radius > WINSIZEY) {
			m_ball.y = WINSIZEY - m_ball.radius;
			m_ball.angle = 2 * PI - m_ball.angle;
		}
		if (m_ball.speed <= 0) m_ball.smash = false;
	}
}

void MainGame9::Smash()
{
	for (int i = 0; i < 2; i++) {
		float length = GetDistance(
			m_ball.x, m_ball.y, m_racket[i].x, m_racket[i].y);

		// 충돌이 되지 않는 조건
		if (m_racket[i].radius + m_ball.radius < length) continue;

		m_ball.angle = GetAngle(
			m_racket[i].x, m_racket[i].y, m_ball.x, m_ball.y);

		m_ball.speed = 10;
		m_ball.smash = true;
	}
}

