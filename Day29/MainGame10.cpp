#include "stdafx.h"
#include "MainGame10.h"


MainGame10::MainGame10()
{
}


MainGame10::~MainGame10()
{
}

HRESULT MainGame10::Init()
{
	GameNode::Init();
	m_coat[0] = RectMakeCenter(
		WINSIZEX / 2, WINSIZEY / 2 + WINSIZEY / 4,
		WINSIZEX, WINSIZEY / 2);
	m_coat[1] = RectMakeCenter(
		WINSIZEX / 2, WINSIZEY / 4,
		WINSIZEX, WINSIZEY / 2);
	m_goal[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY, WINSIZEX / 3, 10);
	m_goal[1] = RectMakeCenter(WINSIZEX / 2, 0, WINSIZEX / 3, 10);

	// ball 
	m_ball.speed = 0.0f;
	m_ball.smash = false;
	m_ball.radius = 15;
	m_ball.x = WINSIZEX / 2;
	m_ball.y = WINSIZEY / 2;

	// racket
	m_racket[0].radius = 20;
	m_racket[0].x = WINSIZEX / 2;
	m_racket[0].y = WINSIZEY / 2 + WINSIZEY / 4;

	m_racket[1].radius = 20;
	m_racket[1].x = WINSIZEX / 2;
	m_racket[1].y = WINSIZEY / 4;

	// score
	m_score[0] = 0;
	m_score[1] = 0;

	return S_OK;
}

void MainGame10::Release()
{
	GameNode::Release();
}

void MainGame10::Update()
{
	GameNode::Update();

	// 1p
	if (INPUT->GetKey(VK_LEFT)) m_racket[0].x -= RACKET_SPEED;
	if (INPUT->GetKey(VK_RIGHT)) m_racket[0].x += RACKET_SPEED;
	if (INPUT->GetKey(VK_UP)) m_racket[0].y -= RACKET_SPEED;
	if (INPUT->GetKey(VK_DOWN)) m_racket[0].y += RACKET_SPEED;
	
	// 2p
	if (INPUT->GetKey('A')) m_racket[1].x -= RACKET_SPEED;
	if (INPUT->GetKey('D')) m_racket[1].x += RACKET_SPEED;
	if (INPUT->GetKey('W')) m_racket[1].y -= RACKET_SPEED;
	if (INPUT->GetKey('S')) m_racket[1].y += RACKET_SPEED;

	for (int i = 0; i < 2; i++) {
		// left
		if (m_racket[i].x - m_racket[i].radius < 0)
			m_racket[i].x = 0 + m_racket[i].radius;
		// right
		if (m_racket[i].x + m_racket[i].radius > WINSIZEX)
			m_racket[i].x = WINSIZEX - m_racket[i].radius;
		// up
		if (m_racket[i].y - m_racket[i].radius < m_coat[i].top)
			m_racket[i].y = m_coat[i].top + m_racket[i].radius;
		// down
		if (m_racket[i].y + m_racket[i].radius > m_coat[i].bottom) {
			m_racket[i].y = m_coat[i].bottom - m_racket[i].radius;
		}
	}
	Smash();

	BallMove();

	// 1번 골대에 골 넣었을 때
	if (m_goal[1].bottom >= m_ball.y - m_ball.radius &&
		m_goal[1].left <= m_ball.x &&
		m_goal[1].right >= m_ball.x) {
		m_score[0]++;

		// init
		m_ball.x = WINSIZEX / 2;
		m_ball.y = WINSIZEY / 2;

		m_racket[0].x = WINSIZEX / 2;
		m_racket[0].y = WINSIZEY / 2 + WINSIZEY / 4;
		
		m_racket[1].x = WINSIZEX / 2;
		m_racket[1].y = WINSIZEY / 4;

		m_ball.smash = false;
	}
}

void MainGame10::Render(HDC hdc)
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

void MainGame10::BallMove()
{
	if (m_ball.smash == true) {
		m_ball.x += cosf(m_ball.angle) * m_ball.speed;
		m_ball.y += -sinf(m_ball.angle) * m_ball.speed;

		m_ball.speed -= 0.03f;

		// border collision
		//left
		if (m_ball.x - m_ball.radius < 0) {
			m_ball.x = 0 + m_ball.radius;
			m_ball.angle = PI - m_ball.angle;
		}
		// right
		if (m_ball.x + m_ball.radius > WINSIZEX) {
			m_ball.x = WINSIZEX - m_ball.radius;
			m_ball.angle = PI - m_ball.angle;
		}
		// up
		if (m_ball.y - m_ball.radius < 0) {
			m_ball.y = 0 + m_ball.radius;
			m_ball.angle = 2 * PI - m_ball.angle;
		}
		// down
		if (m_ball.y + m_ball.radius > WINSIZEY) {
			m_ball.y = WINSIZEY - m_ball.radius;
			m_ball.angle = 2 * PI - m_ball.angle;
		}
		if (m_ball.speed <= 0) m_ball.smash = false;
	}
}

void MainGame10::Smash()
{
	for (int i = 0; i < 2; i++) {
		float length = GetDistance(
			m_ball.x, m_ball.y, m_racket[i].x, m_racket[i].y);

		// 충돌되지 않을 조건
		if (m_racket[i].radius + m_ball.radius < length) continue;

		m_ball.angle = GetAngle(
			m_racket[i].x, m_racket[i].y, m_ball.x, m_ball.y);

		m_ball.speed = 10;
		m_ball.smash = true;
	}
}
